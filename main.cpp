#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "SOIL/SOIL.h"
#include "TBB/tbb/tbb.h"
#include "shader.h"
#include "camera.h"
#include "particle.h"
#include "compute.h"

void SendParticlesToBuffer(GLuint vbo, Particle* p, int N);
void UpdateDelta();
void MoveCamera();
void ShowFPS(GLFWwindow* window);
void KeyHandler(GLFWwindow* window, int key, int code, int action, int mods);
void MouseHandler(GLFWwindow* window, double x_pos, double y_pos);
void ScrollHandler(GLFWwindow* window, double x_offset, double y_offset);
GLFWwindow* InitGLFW();
void InitGLEW();
void InitOpenGL();
void PrintInfo();
void PrintScreenAndExit(GLFWwindow* window);

// parameters
int win_width = 800;
int win_height = 600;
bool fullscreen = false;
int N = 600; // number of particles
int compute_mode = 1; // tbb_outer
int initial_location_mode = 0; // sphere
float mass = 0.01f; // mass of each particle
glm::vec3 color(1.0f, 0.3f, 0.1f); // color of each particle

// delta time
GLfloat delta_time = 0.0f; // time between current frame and last frame
GLfloat last_frame = 0.0f; // time of last frame

// FPS
int frame_count = 0;
double previous_time = 0.0f;
double average_fps_sum = 0.0f;
double average_fps_count = 0;

// camera
Camera camera;
bool keys[1024];
GLfloat last_x = win_width / 2, last_y = win_height / 2;
bool first_mouse = true;

Particle* particles;

int main(int argc, char* argv[])
{

	// ==================================================================================================
	// parameters

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-n") == 0)
			N = atoi(argv[++i]);
		else if (strcmp(argv[i], "-m") == 0)
			mass = atof(argv[++i]);
		else if (strcmp(argv[i], "-r") == 0)
		{
			color.r = atof(argv[++i]);
			color.g = atof(argv[++i]);
			color.b = atof(argv[++i]);
		}
		else if (strcmp(argv[i], "-l") == 0)
			initial_location_mode = atoi(argv[++i]);
		else if (strcmp(argv[i], "-c") == 0)
			compute_mode = atoi(argv[++i]);
		else if (strcmp(argv[i], "-d") == 0)
		{
			win_width = atoi(argv[++i]);
			win_height = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-f") == 0)
			fullscreen = true;
		else if (strcmp(argv[i], "-h") == 0)
		{
			std::cout << "\t-n [count] : number of particles; default = 600"
					"\n\t-m [mass] : mass of each particle; default = 0.001"
                    "\n\t-r [r] [g] [b] : color of each particle; default = 1.0 0.3 0.1"
					"\n\t-l [initial location mode] : initial location mode (0-2); default = 0"
					"\n\t-c [compute mode] : compute mode (0-1); default = 1"
					"\n\t-d [width] [height] : window width and height; default = 800 600"
					"\n\t-f : fullscreen mode"
					"\n\t-h : show this help\n";
			return 0;
		}

	}

	// ==================================================================================================
	// settings

	GLFWwindow* window = InitGLFW();
	InitGLEW();
	InitOpenGL();
	Shader shader("vertex.glsl", "fragment.glsl");
	glUseProgram(shader.program);

	printf("Version: %s\nVendor: %s\nRenderer: %s\n", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));

	// ==================================================================================================
	// init

	particles = new Particle[N];
	for(int i=0; i<N; i++)
		particles[i] = Particle(mass, initial_location_mode);
	glUniform3fv(glGetUniformLocation(shader.program, "color"), 1, glm::value_ptr(color));


	// set buffers and data
	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	SendParticlesToBuffer(vbo, particles, N);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	// texture
	int width, height;
	unsigned char* image = SOIL_load_image("Data/particle.png", &width, &height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);


	// ==================================================================================================
	// loop

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //glfwWaitEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateDelta();
		ShowFPS(window);
		MoveCamera();

		switch(compute_mode)
		{
			case 0:
				ComputeNextPositions(vbo, particles, N, delta_time); break;
			case 1:
				ComputeNextPositions_TBB_Outer(vbo, particles, N, delta_time); break;
			case 2:
				ComputeNextPositions_TBB_Both(vbo, particles, N, delta_time); break;
			case 3:
				ComputeNextPositions_TBB_BlockedRange(vbo, particles, N, delta_time); break;
		}

		SendParticlesToBuffer(vbo, particles, N);

		glm::mat4 model;
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov) , (float)win_width / (float)win_height, 0.01f, 1000.f);

		// compute mvp and send it
		glm::mat4 mvp = projection * view * model;
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

		// draw
		glDrawArrays(GL_POINTS, 0, N);
		glfwSwapBuffers(window);

	}

	// ==================================================================================================
	// end

	glfwTerminate();
    delete [] particles;
	return 0;
}

void SendParticlesToBuffer(GLuint vbo, Particle* p, int N)
{
	GLfloat* all_floats = new GLfloat[N * 3];

	for (int i = 0, j = 0; i < N; i++)
	{
		all_floats[j] = p[i].location.x; j++;
		all_floats[j] = p[i].location.y; j++;
		all_floats[j] = p[i].location.z; j++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * N * sizeof(GLfloat), all_floats, GL_STATIC_DRAW);
}

void ShowFPS(GLFWwindow* window)
{
	double current_time = glfwGetTime();
	frame_count++;

	double time_interval = current_time - previous_time;
	if (time_interval > 1.0f)
	{
		double fps = frame_count / (time_interval);
		previous_time = current_time;

		char title[256];
		title[255] = '\0';
		snprintf(title, 255, "%.2f", fps);
		glfwSetWindowTitle(window, title);
		frame_count = 0;
        if(current_time > 10.0f)
		{
			average_fps_sum += fps;
			average_fps_count += 1;
		}
	}
}

void UpdateDelta()
{
	GLfloat current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
}

void MoveCamera()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, delta_time);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, delta_time);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, delta_time);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, delta_time);
}

void KeyHandler(GLFWwindow* window, int key, int code, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        initial_location_mode = 0;
	else if (key == GLFW_KEY_X && action == GLFW_PRESS)
		initial_location_mode = 1;
	else if (key == GLFW_KEY_C && action == GLFW_PRESS)
		initial_location_mode = 2;
	else if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		compute_mode = 0;
	else if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
		compute_mode = 1;
	else if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
		compute_mode = 2;
	else if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
		compute_mode = 3;
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        for(int i=0; i<N; i++)
            particles[i].mass /= 2;
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
		for(int i=0; i<N; i++)
			particles[i].mass *= 2;
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		for(int i=0; i<N; i++)
			particles[i] = Particle(mass, initial_location_mode);
	else if (key == GLFW_KEY_I && action == GLFW_PRESS)
        PrintInfo();
	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		PrintScreenAndExit(window);

	// ALL keys
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void MouseHandler(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	GLfloat xoffset = x_pos - last_x;
	GLfloat yoffset = last_y - y_pos;  // Reversed since y-coordinates go from bottom to left

	last_x = x_pos;
	last_y = y_pos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void ScrollHandler(GLFWwindow* window, double x_offset, double y_offset)
{
	camera.ProcessMouseScroll(y_offset);
}

void InitOpenGL()
{
	glViewport(0, 0, win_width, win_height);
	glClearColor(0, 0, 0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

GLFWwindow* InitGLFW()
{
	// context and window init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window;
	
	if(fullscreen)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		win_width = mode->width;
		win_height = mode->height;
		window = glfwCreateWindow(win_width, win_height, "OpenGL", glfwGetPrimaryMonitor(), nullptr);
	}
	else
		window = glfwCreateWindow(win_width, win_height, "OpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyHandler); // set function that handle keys
	glfwSetCursorPosCallback(window, MouseHandler);
	glfwSetScrollCallback(window, ScrollHandler);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//export vblank_mode=0

	return window;
}

void InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		std::cout << "Failed to initialize GLEW" << std::endl;
}

void PrintInfo()
{
	printf("Simulation info:\n");
	printf("\tTime: %0.2fs\n", glfwGetTime());
	printf("\tAverage FPS: %0.2f\n", average_fps_sum/average_fps_count);
	printf("\tCamera position: [%.2f, %.2f, %.2f]\n", camera.position.x, camera.position.y, camera.position.z);
	printf("\tField of view: %f\n", camera.fov);
	printf("\tNumber of particles %d\n", N);
	printf("\tMass of each particle: %f\n", mass);
	printf("\tColor: [%.2f, %.2f, %.2f]\n", color.r, color.g, color.b);
	printf("\tInitial location: %d\n", initial_location_mode);
	printf("\tCompute mode: %d\n", compute_mode);
}

void PrintScreenAndExit(GLFWwindow* window)
{
	PrintInfo();
	system("shutter -f");
	sleep(1);
	glfwSetWindowShouldClose(window, GL_TRUE);
}

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

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
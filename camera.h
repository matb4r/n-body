#pragma once
#include "GLM/glm.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum DIRECTION { FORWARD, BACKWARD, LEFT, RIGHT };

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
struct Camera
{
	// Camera Attributes
	glm::vec3 world_up;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;
	// Camera options
	GLfloat movement_speed;
	GLfloat mouse_sensitivity;
	GLfloat fov;

	// Constructor with vectors
	Camera()
	{
		this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->position = glm::vec3(0.0f, 0.0f, 3.0f);
		this->yaw = 0.0f;
		this->pitch = 0.0f;
		this->fov = 60.0f;
		this->movement_speed = 3.0f;
		this->mouse_sensitivity = 0.05f;

		this->UpdateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->front, this->up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(DIRECTION direction, GLfloat delta_time)
	{
		GLfloat distance = this->movement_speed * delta_time;

		switch(direction)
		{
			case FORWARD:
				this->position += this->front * distance; break;
			case BACKWARD:
				this->position -= this->front * distance; break;
			case LEFT:
				this->position -= this->right * distance; break;
			case RIGHT:
				this->position += this->right * distance; break;
		}
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat x_offset, GLfloat y_offset)
	{
		x_offset *= this->mouse_sensitivity;
		y_offset *= this->mouse_sensitivity;

		this->yaw += x_offset;
		this->pitch += y_offset;

        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;

		// update front, right and up Vectors using the updated Eular angles
		this->UpdateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat y_offset)
	{
		if (this->fov >= 1.0f && this->fov <= 120.0f)
			this->fov -= y_offset * 5;
		if (this->fov <= 1.0f)
			this->fov = 1.0f;
		if (this->fov >= 120.0f)
			this->fov = 120.0f;
	}

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors()
	{
		// Calculate the new front vector
		glm::vec3 temp;
		temp.x = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		temp.y = sin(glm::radians(this->pitch));
		temp.z = -cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front = glm::normalize(temp);
		// Also re-calculate the right and up vector
		this->right = glm::normalize(glm::cross(this->front, this->world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};

struct Camera
{
	glm::vec3 world_up;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movement_speed;
	GLfloat mouse_sensitivity;
	GLfloat fov;

	Camera();

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(DIRECTION direction, GLfloat delta_time);

	void ProcessMouseMovement(GLfloat x_offset, GLfloat y_offset);

	void ProcessMouseScroll(GLfloat y_offset);

	void UpdateCameraVectors();
};
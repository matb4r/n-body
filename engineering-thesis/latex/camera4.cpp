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

	this->UpdateCameraVectors();
}
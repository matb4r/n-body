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
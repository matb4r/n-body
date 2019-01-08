void UpdateCameraVectors()
{
	glm::vec3 temp;
	temp.x = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	temp.y = sin(glm::radians(this->pitch));
	temp.z = -cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(temp);
	this->right = glm::normalize(glm::cross(this->front, this->world_up));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
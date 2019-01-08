glm::mat4 GetViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}
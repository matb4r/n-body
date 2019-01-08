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
void MouseHandler(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	GLfloat xoffset = x_pos - last_x;
	GLfloat yoffset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
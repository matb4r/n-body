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
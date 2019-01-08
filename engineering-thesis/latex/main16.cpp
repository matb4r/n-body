void ShowFPS(GLFWwindow* window)
{
	double current_time = glfwGetTime();
	frame_count++;

	double time_interval = current_time - previous_time;
	if (time_interval > 1.0f)
	{
		double fps = frame_count / (time_interval);
		previous_time = current_time;

		char title[256];
		title[255] = '\0';
		snprintf(title, 255, "%.2f", fps);
		glfwSetWindowTitle(window, title);
		frame_count = 0;
		if(current_time > 10.0f)
		{
			average_fps_sum += fps;
			average_fps_count += 1;
		}
	}
}
void InitOpenGL()
{
	glViewport(0, 0, win_width, win_height);
	glClearColor(0, 0, 0, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);
}
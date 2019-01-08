void InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		std::cout << "Failed to initialize GLEW" << std::endl;
}
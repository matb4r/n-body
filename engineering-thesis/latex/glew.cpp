GLenum err = glewInit();

if (GLEW_OK != err)
{
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
}
fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
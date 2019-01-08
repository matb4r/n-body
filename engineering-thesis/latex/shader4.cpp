this->program = glCreateProgram();
glAttachShader(this->program, vertex);
glAttachShader(this->program, fragment);
glLinkProgram(this->program);

glGetProgramiv(this->program, GL_LINK_STATUS, &success);
if (!success)
{
	glGetProgramInfoLog(this->program, 512, NULL, info_log);
	std::cout << "ERROR - shader link failed:\n" << info_log << std::endl;
}
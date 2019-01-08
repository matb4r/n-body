GLuint vertex, fragment;
GLint success;
GLchar info_log[512];

vertex = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex, 1, &vertex_code_chars, NULL);
glCompileShader(vertex);

glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
if (!success)
{
	glGetShaderInfoLog(vertex, 512, NULL, info_log);
	std::cout << "ERROR - vertex shader compilation failed:\n" << info_log << std::endl;
}

fragment = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment, 1, &fragment_code_chars, NULL);
glCompileShader(fragment);

glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
if (!success)
{
	glGetShaderInfoLog(fragment, 512, NULL, info_log);
	std::cout << "ERROR - fragment shader compilation failed:\n" << info_log << std::endl;
}
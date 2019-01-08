std::string vertex_code;
std::string fragment_code;
std::ifstream vertex_file;
std::ifstream fragment_file;

vertex_file.exceptions(std::ifstream::badbit);
fragment_file.exceptions(std::ifstream::badbit);
try
{
	vertex_file.open(vertex_path);
	fragment_file.open(fragment_path);
	std::stringstream vertex_stream, fragment_stream;
	
	vertex_stream << vertex_file.rdbuf();
	fragment_stream << fragment_file.rdbuf();

	vertex_file.close();
	fragment_file.close();

	vertex_code = vertex_stream.str();
	fragment_code = fragment_stream.str();
}
catch (std::ifstream::failure e)
{
	std::cout << "ERROR - read file failed" << std::endl;
}

const GLchar* vertex_code_chars = vertex_code.c_str();
const GLchar* fragment_code_chars = fragment_code.c_str();
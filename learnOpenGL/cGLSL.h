#pragma
#include <string>
using namespace std;

const char* vertexShaderSrc = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main() \n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;"
"}\n";

const char* fragmentShaderSrc = "#version 330 core\n"
"out vec4 fragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"fragColor = vec4(ourColor, 1.0f);\n"
"}\n";


//check the shader is success compile
void checkShader(unsigned int shader) 
{
	int success = false;
	char infoLog[512] = { 0 };
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void checkLinks(unsigned int linkProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(linkProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(linkProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}
#pragma

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
using namespace std;

float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

float verticesQuard[] =
{
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

unsigned int indices[] =
{
	0, 1, 3,
	/*1, 2, 3*/
};

const char* vertexShaderSrc = "#version 330 core\n "
"layout (location = 0) in vec3 aPos;//位置变量的属性位置值为0\n"
"out vec4 vertexColor; // 为片段着色器指定颜色输出\n "
"void main() \n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\n";

const char* fragmentShaderSrc = "#version 330 core\n"
"in vec4 vertexColor;//从顶点着色器传来的输入变量\n "
"uniform vec4 ourColor;\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"	fragColor = ourColor;\n"
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

//link shader program and delete shader
void glLink(vector<unsigned int> shader, unsigned int program)
{
	for (unsigned int cell : shader)
	{
		glAttachShader(program, cell);
	}
	glLinkProgram(program);
	checkLinks(program);

	for (unsigned int cell : shader)
	{
		glDeleteShader(cell);
	}
}

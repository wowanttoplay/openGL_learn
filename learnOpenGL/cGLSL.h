#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>


using namespace std;

float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

float verticesQuard[] =
{
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		2.0f, 2.0f,
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,		2.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,		0.0f, 2.0f
};

unsigned int indices[] =
{
	0, 1, 3,
	1, 2, 3
};

const char* vertexShaderSrc =
"#version 330 core\n"

"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"

"void main() \n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = aTexCoord;\n"
"}\n";

const char* fragmentShaderSrc =
"#version 330 core\n"

"out vec4 fragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

//"uniform sampler2D ourTexture;\n" 
"uniform sampler2D texture0;\n"
"uniform sampler2D texture1;\n"

"void main()\n"
"{\n"
//"fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
"fragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);\n"
"}\n";


//check the shader is success compile
//void checkShader(unsigned int shader) 
//{
//	int success = false;
//	char infoLog[512] = { 0 };
//	glCompileShader(shader);
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//}

//void checkLinks(unsigned int linkProgram)
//{
//	int success;
//	char infoLog[512];
//	glGetProgramiv(linkProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(linkProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//}

//link shader program and delete shader
//void glLink(vector<unsigned int> shader, unsigned int program)
//{
//	for (unsigned int cell : shader)
//	{
//		glAttachShader(program, cell);
//	}
//	glLinkProgram(program);
//	checkLinks(program);
//
//	for (unsigned int cell : shader)
//	{
//		glDeleteShader(cell);
//	}
//}

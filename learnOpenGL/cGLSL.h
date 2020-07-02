#pragma
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//vertic point
float vertices[] =
{
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f
};

float textureCoors[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f
};
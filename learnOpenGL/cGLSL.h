#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>


using namespace std;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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

"uniform mat4 transform;"

"void main() \n"
"{\n"
"gl_Position = transform * vec4(aPos, 1.0);\n"
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




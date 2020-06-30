#include "shader.h"

shader::shader(string vertexPath, string fragmentPath)
{
    //1. 读取文件内容
    const char* vertexCode = getShaderCode(vertexPath).c_str();
    const char* fragementCode = getShaderCode(fragmentPath).c_str();
    // 2. 建立着色程序
	shader(vertexCode, fragementCode);
}

shader::shader(const char* vertexCode, const char* fragmentCode)
{
	//1. 编译着色器
	unsigned int vertexId, fragmentId;
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexCode, NULL);
	glCompileShader(vertexId);
	checkShader(vertexId);

	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentCode, NULL);
	glCompileShader(fragmentId);
	checkShader(fragmentId);

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexId);
	glAttachShader(m_id, fragmentId);
	glLinkProgram(m_id);
	checkLinks(m_id);
	//2. delete the shader 
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void shader::use()
{
    glUseProgram(m_id);
}

unsigned int shader::getID()
{
    return m_id;
}

void shader::setBool(const string& name, bool value) const
{
    int pos = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(pos, (int)value);
}

void shader::setInt(const string& name, int value) const
{
	int pos = glGetUniformLocation(m_id, name.c_str());
	glUniform1i(pos, (int)value);
}

void shader::setFloat(const string& name, float value) const
{
	int pos = glGetUniformLocation(m_id, name.c_str());
	glUniform1f(pos, value);
}

string shader::getShaderCode(const string& shaderFilePath)
{
    ifstream in(shaderFilePath);
    if (!in.is_open())
    {
        printf("open file fail");
        return string();
    }
    ostringstream buf;
    buf << in.rdbuf();
    string shaderCode(buf.str());
    in.close();
    return shaderCode;
}

void shader::checkShader(const unsigned int& shaderId)
{
	int success = false;
	char infoLog[512] = { 0 };
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void shader::checkLinks(const unsigned int& program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

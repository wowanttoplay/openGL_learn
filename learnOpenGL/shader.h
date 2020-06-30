#pragma once

#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
class shader
{
public:
	shader(string vertexPath, string fragmentPath);
	shader(const char* vertexCode, const char* fragmentCode);
	void use();
	unsigned int getID();
	//uniform tool
	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value)const;
	void setFloat(const string& name, float value)const;
private:
	unsigned int m_id;
	string getShaderCode(const string& shaderFilePath);
	void checkShader(const unsigned int& shaderId);
	void checkLinks(const unsigned int& program);
};


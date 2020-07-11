#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	void setMate4(const string& name, glm::mat4& trans);
private:
	unsigned int m_id;
	string getShaderCode(const string& shaderFilePath);
	void checkShader(const unsigned int& shaderId);
	void checkLinks(const unsigned int& program);
};

#pragma once
#include <string>
class Texture
{
public:
	Texture(const std::string& iconPath);
	unsigned int getId() { return m_id; }
	void bindTexture();
private:
	unsigned int m_id;
};


#include "Texture.h"
#include "Icon.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

Texture::Texture(const string& iconPath)
{
	Icon iconObject(iconPath);
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	
	//set the texture wrapping parameters（repeat, mirrored_repeat, clamp_to_edge, clamp_to_border）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//set the filtering parameters (liner, nearest, linear_mipmap_linear)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载并生成纹理
	if (iconObject.getData() != nullptr)
	{
		int color = iconObject.getChannel() - 3;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB +color, iconObject.getWidth(), iconObject.getHeight(), 0, GL_RGB + color , GL_UNSIGNED_BYTE, iconObject.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("[Texture] Failed to load texture\n");
	}
}

void Texture::bindTexture()
{
	 glBindTexture(GL_TEXTURE_2D, m_id);
}

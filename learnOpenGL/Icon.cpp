#include "Icon.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <string>
using namespace std;
Icon::Icon(const string& iconPath)
{
	loadIcon(iconPath);
}

void Icon::loadIcon(const string& iconPath)
{
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(iconPath.c_str(), &m_wdith, &m_height, &m_channel, 0);
}

Icon::~Icon()
{
	clear();
}

void Icon::clear()
{
	stbi_image_free(m_data);
	m_data = nullptr;
}

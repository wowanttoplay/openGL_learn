#pragma once
#include <string>

class Icon
{
public:
	Icon() {};
	Icon(const std::string& iconPath);
	~Icon();

	void loadIcon(const std::string& iconPath);
	unsigned char* getData() { return m_data; }
	int getWidth() { return m_wdith; }
	int getHeight() { return m_height; }
	int getChannel() { return m_channel; }
private:
	void clear();
	unsigned char* m_data = nullptr;
	int m_wdith = 0;
	int m_height = 0;
	int m_channel = 0;
};


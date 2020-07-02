#pragma once
#include "cGLSL.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class Texture
{
public:
	Texture() {}
	Texture(string iconPath);
	void loadIcon(string iconPath);

	string getData() { return data; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getChannel() { return channel; }
private:
	string data = "";
	int width = 0;
	int height = 0;
	int channel = 0;
};


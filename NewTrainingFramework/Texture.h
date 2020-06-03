#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
class Texture
{
public:
	GLuint		textureID;
	char*		imageData;
	int			width, height, bpp;
	Texture();
	~Texture();
	void InitTexture(char* filename);
};


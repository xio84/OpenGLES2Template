#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
class Texture
{
public:
	GLuint		textureID;
	char*		imageData = 0;
	int			width, height, bpp;
	Texture();
	virtual ~Texture();
	virtual void InitTexture(char* filename);
	virtual void ActivateTexture();
};


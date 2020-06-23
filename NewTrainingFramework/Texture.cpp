#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	// Generate the texture
	glGenTextures(1, &textureID);
}

Texture::~Texture()
{
	if (imageData) delete imageData;
}

void Texture::InitTexture(char* filename)
{
	// Bind and load Texture data
	imageData = LoadTGA(filename, &width, &height, &bpp);
}

void Texture::ActivateTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

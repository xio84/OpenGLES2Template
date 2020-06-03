#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	// Generate the texture
	glGenTextures(1, &textureID);
}

Texture::~Texture()
{
	delete imageData;
}

void Texture::InitTexture(char* filename)
{
	// Bind and load Texture data
	glBindTexture(GL_TEXTURE_2D, textureID);
	imageData = LoadTGA(filename, &width, &height, &bpp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, imageData);
}

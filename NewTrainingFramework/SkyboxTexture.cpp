#include "stdafx.h"
#include "SkyboxTexture.h"

SkyboxTexture::~SkyboxTexture()
{
	delete[] imageData;
}

void SkyboxTexture::InitTexture(char* TR, char* TL, char* TT, char* TBt, char* TF, char* TBck)
{
	char* filenames[6] = { TR, TL, TT, TBt, TF, TBck };
	// Bind and load Texture data
	for (int i = 0; i < 6; i++) {
		skyboxData[i] = LoadTGA(filenames[i], &width, &height, &bpp);
	}
}

void SkyboxTexture::ActivateTexture()
{
	// Bind buffers
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// Set parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Write to buffer
	for (int i=0; i<6; i++)
	glTexImage2D(textureCubeMapPos[i], 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, skyboxData[i]);
}

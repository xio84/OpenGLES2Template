#pragma once
#include "Texture.h"
class SkyboxTexture :
    public Texture
{
    GLenum textureCubeMapPos[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X , GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y , GL_TEXTURE_CUBE_MAP_NEGATIVE_Y , GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
    char* skyboxData[6];
public:
    virtual ~SkyboxTexture();
    void InitTexture(char* TR, char* TL, char* TT, char* TBt, char* TF, char* TBck);
    void ActivateTexture();
};


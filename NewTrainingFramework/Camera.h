#pragma once
#include <vector>
#include "Globals.h"
#include "Object3D.h"
#include "SkyboxShaders.h"
#include "SkyboxTexture.h"
class Camera :
    public Object3D
{
private:
    SkyboxShaders* m_pSkyboxShaders = 0;
    SkyboxTexture* m_pSkyboxTexture = 0;
    Model* m_pSkyboxModel = 0;
public:
    float fovY = 1.0; // Radians
    float aspectRatio = (float) Globals::screenWidth / (float) Globals::screenHeight;
    float nearPlane = 0.001;
    float farPlane = 500;

    std::vector<Object3D*> objectsToDraw;
    
    // Constructors
    Camera(Shaders* targetShader);

    Matrix getViewMatrix();
    Matrix getSkyViewMatrix();
    Matrix getProjectionMatrix();
    Object3D* addObjectsToDraw(char* tgaFile, char* nfgFile);

    void setSkybox(SkyboxShaders* targetSShaders, SkyboxTexture* targetSTexture, char* filename);
    void drawAllObject();
    void move(float x, float y, float z);
    void moveX(float delta);
    void moveY(float delta);
    void moveZ(float delta);
    void rotate(float x, float y, float z);
};


#pragma once
#include <vector>
#include "Globals.h"
#include "Object3D.h"
class Camera :
    public Object3D
{
public:
    float fovY = 1.0; // Radians
    float aspectRatio = (float) Globals::screenWidth / (float) Globals::screenHeight;
    float nearPlane = 0.001;
    float farPlane = 500;

    std::vector<Object3D*> objectsToDraw;
    
    // Constructors
    Camera(Shaders* targetShader);

    Matrix getViewMatrix();
    Matrix getProjectionMatrix();
    Object3D* addObjectsToDraw(char* tgaFile, char* nfgFile);

    void drawAllObject();
};


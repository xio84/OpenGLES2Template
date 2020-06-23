// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Object3D.h"
#include "Camera.h"

Shaders		myShaders;
SkyboxShaders	skyboxShaders;
SkyboxTexture	skyboxTexture;
Camera* cam;
Object3D* woman1;
Object3D* woman2;
bool keys[8]; // Condition of keys (pressed or not)

int Init(ESContext* esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//creation of shaders and program 
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	skyboxShaders.Init("../Resources/Shaders/SkyboxShaderVS.vs", "../Resources/Shaders/SkyboxShaderFS.fs");

	//creation of skybox texture
	skyboxTexture.InitTexture("../Resources/Textures/Skybox_Right.tga", "../Resources/Textures/Skybox_Left.tga",
		"../Resources/Textures/Skybox_Top.tga", "../Resources/Textures/Skybox_Bottom.tga",
		"../Resources/Textures/Skybox_Front.tga", "../Resources/Textures/Skybox_Back.tga");



	// Creation of camera and objects
	cam = new Camera(&myShaders);
	cam->setSkybox(&skyboxShaders, &skyboxTexture, "../Resources/Models/SkyBox.nfg");
	woman1 = cam->addObjectsToDraw("../Resources/Textures/Woman1.tga", "../Resources/Models/Woman1.nfg");
	woman2 = cam->addObjectsToDraw("../Resources/Textures/Woman2.tga", "../Resources/Models/Woman2.nfg");
	//woman1 = new Object3D("../Resources/Textures/Woman1.tga", "../Resources/Models/Woman1.nfg", &myShaders);

	// Moving the objects
	woman1->translateX(-0.1);
	woman2->translateX(0.1);

	woman1->translateZ(0.5);
	woman2->translateZ(-0.5);

	// Scaling the objects
	woman1->uniformScale(0.5);
	woman2->uniformScale(0.35);

	return 0;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cam->drawAllObject();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update( ESContext *esContext, float deltaTime )
{
	int slow = 1;
	float w1rotation = woman1->getRotation().y + (deltaTime / slow);
	woman1->rotateY(w1rotation);
	float w2rotation = woman2->getRotation().z + (deltaTime / slow);
	woman2->rotateZ(w2rotation);

	if (keys[0] && !keys[1])
		cam->moveZ(deltaTime);
	if (!keys[0] && keys[1])
		cam->moveZ(-deltaTime);
	if (keys[2] && !keys[3])
		cam->moveX(-deltaTime);
	if (!keys[2] && keys[3])
		cam->moveX(deltaTime);
	if (keys[4] && !keys[5])
		cam->rotateY(cam->getRotation().y + deltaTime);
	if (!keys[4] && keys[5])
		cam->rotateY(cam->getRotation().y - deltaTime);
	if (keys[6] && !keys[7])
		cam->rotateX(cam->getRotation().x + deltaTime);
	if (!keys[6] && keys[7])
		cam->rotateX(cam->getRotation().x - deltaTime);
	/*float w2rotationx = woman2->getRotation().x + (deltaTime / slow);
	woman2->rotateX(w2rotationx);*/
}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{
	printf("%c is pressed\n", key);
	if (bIsPressed) {
		switch (key) {
		case 'S':
			keys[0] = true;
			break;
		case 'W':
			keys[1] = true;
			break;
		case 'A':
			keys[2] = true;
			break;
		case 'D':
			keys[3] = true;
			break;
		case 'Q':
			keys[4] = true;
			break;
		case 'E':
			keys[5] = true;
			break;
		case 'U':
			keys[6] = true;
			break;
		case 'I':
			keys[7] = true;
			break;
		}
	}
	else {
		switch (key) {
		case 'S':
			keys[0] = false;
			break;
		case 'W':
			keys[1] = false;
			break;
		case 'A':
			keys[2] = false;
			break;
		case 'D':
			keys[3] = false;
			break;
		case 'Q':
			keys[4] = false;
			break;
		case 'E':
			keys[5] = false;
			break;
		case 'U':
			keys[6] = false;
			break;
		case 'I':
			keys[7] = false;
			break;
		}
	}
}

void CleanUp()
{
	//Cleaning up the buffers
	
	//glDeleteBuffers( 1, &vboId );
	//glDeleteBuffers( 1, &iboId );
	if (cam) delete cam;
	if (woman1) delete woman1;
	if (woman2) delete woman2;
}

int _tmain( int argc, _TCHAR* argv[] )
{
	ESContext esContext;

	esInitContext( &esContext );

	esCreateWindow( &esContext, "Hello OpenGLES 2", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

	if( Init( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc( &esContext, Draw );
	esRegisterUpdateFunc( &esContext, Update );
	esRegisterKeyFunc( &esContext, Key );

	esMainLoop( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf( "Press any key...\n" );
	_getch();

	return 0;
}


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
Camera* cam;
Object3D* woman1;
Object3D* woman2;

int Init(ESContext* esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//creation of shaders and program 
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	// Creation of camera and objects
	cam = new Camera(&myShaders);
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

	glUseProgram(myShaders.GetProgram());

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
	/*float w2rotationx = woman2->getRotation().x + (deltaTime / slow);
	woman2->rotateX(w2rotationx);*/
}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{
	printf("%c is pressed\n", key);
	if (bIsPressed) {
		switch (key) {
		case 'S':
			cam->translateZ(cam->getPosition().z + 0.01);
			break;
		case 'W':
			cam->translateZ(cam->getPosition().z - 0.01);
			break;
		case 'A':
			cam->translateX(cam->getPosition().x - 0.01);
			break;
		case 'D':
			cam->translateX(cam->getPosition().x + 0.01);
			break;
		case 'Q':
			cam->rotateY(cam->getRotation().y + 0.01);
			break;
		case 'E':
			cam->rotateY(cam->getRotation().y - 0.01);
			break;
		case 'U':
			cam->rotateX(cam->getRotation().x + 0.01);
			break;
		case 'I':
			cam->rotateX(cam->getRotation().x - 0.01);
			break;
		}
	}
}

void CleanUp()
{
	//Cleaning up the buffers
	
	//glDeleteBuffers( 1, &vboId );
	//glDeleteBuffers( 1, &iboId );
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


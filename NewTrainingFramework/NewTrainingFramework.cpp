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

Shaders		myShaders;
Vertex		*verticesData;
Model		*targetModel;
Model* targetModel2;
Texture		*targetTexture;
Texture* targetTexture2;
int iTextureLoc;
Object3D* woman1;
Object3D* woman2;

int Init(ESContext* esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//triangle data
	/*verticesData[0].pos = Vector3(0.5,  0.5,  0.0);
	verticesData[1].pos = Vector3( -0.5, 0.5,  0.0 );
	verticesData[2].pos = Vector3(  -0.5, -0.5,  0.0 );
	verticesData[3].pos = Vector3(0.5, -0.5, 0.0);

	verticesData[0].color = Vector4(0.0, 1.0, 0.0, 0.5);
	verticesData[1].color = Vector4(1.0, 0.0, 0.0, 0.5);
	verticesData[2].color = Vector4(1.0, 1.0, 1.0, 0.5);
	verticesData[3].color = Vector4(0.0, 0.0, 1.0, 0.5);

	pindices[0] = 1;
	pindices[1] = 2;
	pindices[2] = 3;
	pindices[3] = 0;
	pindices[4] = 1;
	pindices[5] = 3;*/

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//// Setup Texture
	//targetTexture = new Texture;
	//targetTexture->InitTexture("../Resources/Textures/Woman1.tga");
	//targetTexture2 = new Texture;
	//targetTexture2->InitTexture("../Resources/Textures/Woman2.tga");

	//// Reading data
	//targetModel = new Model;
	//targetModel->offsetPos.x = -0.7;
	//targetModel->InitModel("../Resources/Models/Woman1.nfg");
	//targetModel2 = new Model;
	//targetModel2->offsetPos.x = 0.7;
	//targetModel2->InitModel("../Resources/Models/Woman2.nfg");

	//creation of shaders and program 
	myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	woman1 = new Object3D("../Resources/Textures/Woman1.tga", "../Resources/Models/Woman1.nfg", &myShaders);
	woman2 = new Object3D("../Resources/Textures/Woman2.tga", "../Resources/Models/Woman2.nfg", &myShaders);
	return 0;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.GetProgram());

	woman1->draw();
	woman2->draw();

	//// Setting texture uniform
	////glBindTexture(GL_TEXTURE_2D, targetTexture->textureID);
	//targetTexture2->ActivateTexture();
	//// Setting texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//iTextureLoc = glGetUniformLocation(myShaders.GetProgram(), "u_texture");
	//glUniform1i(iTextureLoc, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, targetModel2->m_VBO);

	//if (myShaders.GetAttributes().position != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.GetAttributes().position);
	//	glVertexAttribPointer(myShaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//}

	//if (myShaders.GetAttributes().uv != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.GetAttributes().uv);
	//	glVertexAttribPointer(myShaders.GetAttributes().uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + (sizeof(Vector3) * 4));
	//}
	//else {
	//	printf("No Color!\n");
	//}


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, targetModel2->m_IBO);
	//if (targetModel2->m_indicesCount) glDrawElements(GL_TRIANGLES, targetModel2->m_indicesCount, GL_UNSIGNED_INT, 0);

	////glDrawArrays( GL_TRIANGLES, 0, 3 );

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update( ESContext *esContext, float deltaTime )
{

}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{

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


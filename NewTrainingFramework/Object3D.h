#pragma once
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"

struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

class Object3D
{
protected:
	Model* m_pModel;
	Texture* m_pTexture;
	Shaders* m_pShaders;
	
	Transform m_transform;
public:
	// Constructors
	Object3D(Shaders* targetShader);
	Object3D(char* tgaFile, char* nfgFile, Shaders* targetShader);
	virtual ~Object3D();

	// Setters
	void setModel(char* nfgFile);
	void setTexture(char* tgaFile);

	void setPosition(float x, float y, float z);
	void translateX(float t);
	void translateY(float t);
	void translateZ(float t);

	void setRotation(float x, float y, float z);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);

	void setScale(float x, float y, float z);
	void uniformScale(float m);

	// Getters
	Vector3 getPosition();
	Vector3 getRotation();
	Vector3 getScale();
	Matrix getWorldMatrix();

	// Others
	void draw();
	void draw(Matrix &proj, Matrix &view);
};


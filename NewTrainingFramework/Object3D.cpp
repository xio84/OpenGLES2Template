#include "stdafx.h"
#include "Object3D.h"

Object3D::Object3D(Shaders* targetShader)
{
	m_pShaders = targetShader;
	m_pModel = new Model;
	m_pTexture = new Texture;
	uniformScale(1);
}

Object3D::Object3D(char* tgaFile, char* nfgFile, Shaders* targetShader)
{
	m_pShaders = targetShader;
	m_pModel = new Model;
	m_pModel->InitModel(nfgFile);
	m_pTexture = new Texture;
	m_pTexture->InitTexture(tgaFile);
	uniformScale(1);
}

void Object3D::setModel(char* nfgFile)
{
	m_pModel = new Model;
	m_pModel->InitModel(nfgFile);
}

void Object3D::setTexture(char* tgaFile)
{
	m_pTexture = new Texture;
	m_pTexture->InitTexture(tgaFile);
}

void Object3D::setPosition(float x, float y, float z)
{
	m_transform.position.x = x;
	m_transform.position.y = y;
	m_transform.position.z = z;
}

void Object3D::translateX(float t)
{
	m_transform.position.x = t;
}

void Object3D::translateY(float t)
{
	m_transform.position.y = t;
}

void Object3D::translateZ(float t)
{
	m_transform.position.z = t;
}

void Object3D::setRotation(float x, float y, float z)
{
	rotateX(x);
	rotateY(y);
	rotateZ(z);
}

void Object3D::rotateX(float degrees)
{
	m_transform.rotation.x = degrees;
}

void Object3D::rotateY(float degrees)
{
	m_transform.rotation.y = degrees;
	//printf("yrot is: %f\n", m_transform.rotation.y);
}

void Object3D::rotateZ(float degrees)
{
	m_transform.rotation.z = degrees;
}

void Object3D::setScale(float x, float y, float z)
{
	m_transform.scale.x = x;
	m_transform.scale.y = y;
	m_transform.scale.z = z;
}

void Object3D::uniformScale(float m)
{
	setScale(m, m, m);
}

Vector3 Object3D::getPosition()
{
	return m_transform.position;
}

Vector3 Object3D::getRotation()
{
	return m_transform.rotation;
}

Vector3 Object3D::getScale()
{
	return m_transform.scale;
}

Matrix Object3D::getWorldMatrix()
{
	Matrix world, scale, rotX, rotY, rotZ, translate;
	// Set as identity matrices
	world.SetIdentity(); scale.SetIdentity(); rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity(); translate.SetIdentity();

	// Set matrices as appropriate
	scale.SetScale(m_transform.scale);
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);
	translate.SetTranslation(m_transform.position);

	/*Matrix w = rotY;

	printf("wm is: \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f\n",
		w.m[0][0], w.m[0][1], w.m[0][2], w.m[0][3],
		w.m[1][0], w.m[1][1], w.m[1][2], w.m[1][3],
		w.m[2][0], w.m[2][1], w.m[2][2], w.m[2][3],
		w.m[3][0], w.m[3][1], w.m[3][2], w.m[3][3]);*/

	// Set world as appropriate
	world = world * scale * rotZ * rotX * rotY * translate;
	return world;
}

void Object3D::draw()
{
	Matrix proj, view;
	proj.SetIdentity(); view.SetIdentity();
	draw(proj, view);
}

void Object3D::draw(Matrix& proj, Matrix& view)
{
	// Setting texture uniform
	m_pTexture->ActivateTexture();
	// Setting texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glUniform1i(m_pShaders->GetUniforms().texture, 0);

	/*Matrix w = GetWorldMatrix();

	printf("wm is: \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f\n",
		w.m[0][0], w.m[0][1], w.m[0][2], w.m[0][3],
		w.m[1][0], w.m[1][1], w.m[1][2], w.m[1][3],
		w.m[2][0], w.m[2][1], w.m[2][2], w.m[2][3],
		w.m[3][0], w.m[3][1], w.m[3][2], w.m[3][3]);*/

	//glUniformMatrix4fv(m_pShaders->GetUniforms().world, 1, false, getWorldMatrix().m[0]);

	Matrix wvp;
	wvp.SetIdentity();
	wvp = getWorldMatrix() * view * proj;
	/*Matrix w = wvp;

	printf("wvp is: \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f\n",
		w.m[0][0], w.m[0][1], w.m[0][2], w.m[0][3],
		w.m[1][0], w.m[1][1], w.m[1][2], w.m[1][3],
		w.m[2][0], w.m[2][1], w.m[2][2], w.m[2][3],
		w.m[3][0], w.m[3][1], w.m[3][2], w.m[3][3]);*/
	glUniformMatrix4fv(m_pShaders->GetUniforms().wvp, 1, false, wvp.m[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_VBO);

	if (m_pShaders->GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(m_pShaders->GetAttributes().position);
		glVertexAttribPointer(m_pShaders->GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (m_pShaders->GetAttributes().uv != -1)
	{
		glEnableVertexAttribArray(m_pShaders->GetAttributes().uv);
		glVertexAttribPointer(m_pShaders->GetAttributes().uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + (sizeof(Vector3) * 4));
	}
	else {
		printf("No Color!\n");
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_IBO);
	if (m_pModel->m_indicesCount) glDrawElements(GL_TRIANGLES, m_pModel->m_indicesCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

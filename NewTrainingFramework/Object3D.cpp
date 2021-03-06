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

Object3D::~Object3D()
{
	if (m_pModel) delete m_pModel;
	if (m_pTexture) delete m_pTexture;
}

void Object3D::setModel(char* nfgFile)
{
	if (m_pModel) delete m_pModel;
	m_pModel = new Model;
	m_pModel->InitModel(nfgFile);
}

void Object3D::setTexture(char* tgaFile)
{
	if (m_pTexture) delete m_pTexture;
	m_pTexture = new Texture;
	m_pTexture->InitTexture(tgaFile);
}

void Object3D::setShininess(float S)
{
	m_shininess = S;
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
	draw(proj, view, 0);
}

void Object3D::draw(Matrix& proj, Matrix& view, SkyboxTexture* SkyText)
{
	glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
	// Setting texture uniform
	m_pTexture->ActivateTexture();
	// Setting texture parameters
	glUniform1i(m_pShaders->GetUniforms().texture, 0);

	if (SkyText != 0 && m_pShaders->GetUniforms().envi != -1) {
		glActiveTexture(GL_TEXTURE0 + 1); // Texture unit 1
		// Setting texture uniform
		SkyText->ActivateTexture();
		// Setting texture parameters
		glUniform1i(m_pShaders->GetUniforms().envi, 1);
	}
	else {
		printf("No envi!");
	}

	if (m_pShaders->GetUniforms().shininess != -1) {
		glUniform1f(m_pShaders->GetUniforms().shininess, m_shininess);
	}
	else {
		printf("No shininess!");
	}

	// Drawing Vertices
	Matrix wvp;
	Matrix world = getWorldMatrix();
	wvp.SetIdentity();
	wvp = world * view * proj;
	if (m_pShaders->GetUniforms().wvp != 1) {
		glUniformMatrix4fv(m_pShaders->GetUniforms().wvp, 1, false, wvp.m[0]);
	}
	else {
		printf("No wvp uniform!");
	}
	if (m_pShaders->GetUniforms().world != 1) {
		glUniformMatrix4fv(m_pShaders->GetUniforms().world, 1, false, world.m[0]);
	}
	else {
		printf("No world uniform!");
	}


	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->m_VBO);

	if (m_pShaders->GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(m_pShaders->GetAttributes().position);
		glVertexAttribPointer(m_pShaders->GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		printf("No Position!");
	}

	if (m_pShaders->GetAttributes().uv != -1)
	{
		glEnableVertexAttribArray(m_pShaders->GetAttributes().uv);
		glVertexAttribPointer(m_pShaders->GetAttributes().uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + (sizeof(Vector3) * 4));
	}
	else {
		printf("No UV!\n");
	}

	if (m_pShaders->GetAttributes().norm != -1)
	{
		glEnableVertexAttribArray(m_pShaders->GetAttributes().norm);
		glVertexAttribPointer(m_pShaders->GetAttributes().norm, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + (sizeof(Vector3) * 1));
	}
	else {
		printf("No Norm!\n");
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->m_IBO);
	if (m_pModel->m_indicesCount) glDrawElements(GL_TRIANGLES, m_pModel->m_indicesCount, GL_UNSIGNED_INT, 0);

	// Clear buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (SkyText != 0) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

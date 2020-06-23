#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Shaders* targetShader) : Object3D(targetShader)
{
	translateZ(1);
}

Camera::~Camera()
{
	if (m_pSkyboxModel) delete m_pSkyboxModel;
}

Matrix Camera::getViewMatrix()
{
	Matrix view, rotX, rotY, rotZ, translate;
	view.SetIdentity(); rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity(); translate.SetIdentity();
	rotX.SetRotationX(-1 * m_transform.rotation.x);
	rotY.SetRotationY(-1 * m_transform.rotation.y);
	rotZ.SetRotationZ(-1 * m_transform.rotation.z);
	translate.SetTranslation(m_transform.position * -1);
	view = view * translate * rotY * rotX * rotZ;
	return view;
}

Matrix Camera::getSkyViewMatrix()
{
	Matrix view, rotX, rotY, rotZ, translate;
	view.SetIdentity(); rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity(); translate.SetIdentity();
	rotX.SetRotationX(-1 * m_transform.rotation.x);
	rotY.SetRotationY(-1 * m_transform.rotation.y);
	rotZ.SetRotationZ(-1 * m_transform.rotation.z);
	view = view * rotY * rotX * rotZ;
	return view;
}

Matrix Camera::getProjectionMatrix()
{
	Matrix proj;
	proj.SetIdentity();
	proj.SetPerspective(fovY, aspectRatio, nearPlane, farPlane);
	return proj;
}

Object3D* Camera::addObjectsToDraw(char* tgaFile, char* nfgFile)
{
	Object3D* target = new Object3D(tgaFile, nfgFile, m_pShaders);
	objectsToDraw.push_back(target);
	return target;
}

void Camera::setSkybox(SkyboxShaders* targetSShaders, SkyboxTexture* targetSTexture, char* filename)
{
	m_pSkyboxShaders = targetSShaders;
	m_pSkyboxTexture = targetSTexture;
	m_pSkyboxModel = new Model();
	m_pSkyboxModel->InitModel(filename);
}

void Camera::drawAllObject()
{
	glDisable(GL_DEPTH_TEST);

	if (m_pSkyboxShaders != 0 && m_pSkyboxModel != 0 && m_pSkyboxTexture != 0) {
		// skybox
		m_pSkyboxTexture->ActivateTexture();

		glUseProgram(m_pSkyboxShaders->GetProgram());

		glUniform1i(m_pSkyboxShaders->GetUniforms().texture, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_pSkyboxModel->m_VBO);

		Matrix MVPMatrix3 = getSkyViewMatrix() * getProjectionMatrix();
		if (m_pSkyboxShaders->GetUniforms().wvp != -1) {
			glUniformMatrix4fv(m_pSkyboxShaders->GetUniforms().wvp, 1, GL_FALSE, MVPMatrix3.m[0]);
		}
		else {
			printf("no sky wvp matrix!");
		}

		if (m_pSkyboxShaders->GetAttributes().position != -1)
		{
			glEnableVertexAttribArray(m_pSkyboxShaders->GetAttributes().position);
			glVertexAttribPointer(m_pSkyboxShaders->GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}
		else {
			printf("no sky pos matrix!");
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pSkyboxModel->m_IBO);

		glDrawElements(GL_TRIANGLES, m_pSkyboxModel->m_indicesCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	else {
		printf("skybox error!");
	}
	glEnable(GL_DEPTH_TEST);
	glUseProgram(m_pShaders->GetProgram());
	for (std::vector<Object3D*>::iterator it = objectsToDraw.begin();
		it != objectsToDraw.end(); it++) {
		Object3D* targetObj = *it;
		targetObj->draw(getProjectionMatrix(), getViewMatrix());
	}
}

void Camera::move(float x, float y, float z)
{
	Matrix rotX, rotY, rotZ;
	Vector4 movementVector;
	movementVector.x = x; movementVector.y = y; movementVector.z = z;
	movementVector.w = 1; rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity();
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);

	movementVector = movementVector * rotZ * rotX * rotY;
	setPosition(m_transform.position.x + movementVector.x,
		m_transform.position.y + movementVector.y,
		m_transform.position.z + movementVector.z);
}

void Camera::moveX(float delta)
{
	move(delta, 0, 0);
}

void Camera::moveY(float delta)
{
	move(0, delta, 0);
}

void Camera::moveZ(float delta)
{
	move(0, 0, delta);
}

void Camera::rotate(float x, float y, float z)
{
	Matrix rotX, rotY, rotZ;
	Vector4 rotationVector;
	rotationVector.x = x; rotationVector.y = y; rotationVector.z = z;
	rotationVector.w = 1; rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity();
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);

	rotationVector = rotationVector * rotZ * rotX * rotY;
	setRotation(m_transform.rotation.x + rotationVector.x,
		m_transform.rotation.y + rotationVector.y,
		m_transform.rotation.z + rotationVector.z);
}

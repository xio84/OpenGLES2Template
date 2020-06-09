#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Shaders* targetShader) : Object3D(targetShader)
{
	translateZ(1);
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

void Camera::drawAllObject()
{
	for (std::vector<Object3D*>::iterator it = objectsToDraw.begin();
		it != objectsToDraw.end(); it++) {
		Object3D* targetObj = *it;
		targetObj->draw(getProjectionMatrix(), getViewMatrix());
	}
}

void Camera::moveX(float delta)
{
	Matrix rotX, rotY, rotZ;
	Vector4 movementVector;
	movementVector.x = delta; movementVector.w = 1; rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity();
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);

	movementVector = movementVector * rotZ * rotX * rotY;
	setPosition(m_transform.position.x + movementVector.x, 
		m_transform.position.y + movementVector.y, 
		m_transform.position.z + movementVector.z);
}

void Camera::moveY(float delta)
{
	Matrix rotX, rotY, rotZ;
	Vector4 movementVector;
	movementVector.y = delta; movementVector.w = 1; rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity();
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);

	movementVector = movementVector * rotZ * rotX * rotY;
	setPosition(m_transform.position.x + movementVector.x,
		m_transform.position.y + movementVector.y,
		m_transform.position.z + movementVector.z);
}

void Camera::moveZ(float delta)
{
	Matrix rotX, rotY, rotZ;
	Vector4 movementVector;
	movementVector.z = delta; movementVector.w = 1; rotX.SetIdentity();
	rotY.SetIdentity(); rotZ.SetIdentity();
	rotX.SetRotationX(m_transform.rotation.x);
	rotY.SetRotationY(m_transform.rotation.y);
	rotZ.SetRotationZ(m_transform.rotation.z);

	movementVector = movementVector * rotZ * rotX * rotY;
	setPosition(m_transform.position.x + movementVector.x,
		m_transform.position.y + movementVector.y,
		m_transform.position.z + movementVector.z);
}

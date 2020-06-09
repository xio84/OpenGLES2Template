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
	Matrix w = view;

	printf("view is: \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f\n",
		w.m[0][0], w.m[0][1], w.m[0][2], w.m[0][3],
		w.m[1][0], w.m[1][1], w.m[1][2], w.m[1][3],
		w.m[2][0], w.m[2][1], w.m[2][2], w.m[2][3],
		w.m[3][0], w.m[3][1], w.m[3][2], w.m[3][3]);
	return view;
}

Matrix Camera::getProjectionMatrix()
{
	Matrix proj;
	proj.SetIdentity();
	proj.SetPerspective(fovY, aspectRatio, nearPlane, farPlane);
	Matrix w = proj;

	printf("perspective is: \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f, \n%f, %f, %f, %f\n",
		w.m[0][0], w.m[0][1], w.m[0][2], w.m[0][3],
		w.m[1][0], w.m[1][1], w.m[1][2], w.m[1][3],
		w.m[2][0], w.m[2][1], w.m[2][2], w.m[2][3],
		w.m[3][0], w.m[3][1], w.m[3][2], w.m[3][3]);
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

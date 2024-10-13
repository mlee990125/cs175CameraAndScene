#include "Camera.h"
#include <iostream>

Camera::Camera() {
	reset();
}

Camera::~Camera() {
}

void Camera::reset() {
	orientLookAt(glm::vec3(0.0f, 0.0f, DEFAULT_FOCUS_LENGTH), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	setViewAngle(VIEW_ANGLE);
	setNearPlane(NEAR_PLANE);
	setFarPlane(FAR_PLANE);
	screenWidth = screenHeight = 200;
	screenWidthRatio = 1.0f;
	rotU = rotV = rotW = 0;
}

//called by main.cpp as a part of the slider callback for controlling rotation
// the reason for computing the diff is to make sure that we are only incrementally rotating the camera
void Camera::setRotUVW(float u, float v, float w) {
	float diffU = u - rotU;
	float diffV = v - rotV;
	float diffW = w - rotW;
	rotateU(diffU);
	rotateV(diffV);
	rotateW(diffW);
	rotU = u;
	rotV = v;
	rotW = w;
}

void printMatrix(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {  // Loop through rows
        for (int j = 0; j < 4; ++j) {  // Loop through columns
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;  // Newline for each row
    }
}


void Camera::orientLookAt(glm::vec3 eyePoint, glm::vec3 lookatPoint, glm::vec3 upVec) {
		view = glm::mat4(1.0f);
		std::cout << "called orient look at\n";
	  glm::vec3 lookVec = glm::normalize(lookatPoint - eyePoint);
		glm::vec3 w = -lookVec;
		glm::vec3 u = glm::normalize(glm::cross(upVec, w));
		glm::vec3 v  = glm::cross(w, u);

		glm::mat4 trans(1.0f);
		trans[3][0] = -eyePoint.x;
		trans[3][1] = -eyePoint.y;
		trans[3][2] = -eyePoint.z;

		glm::mat4 rot(1.0f);
		rot[0][0] = u.x;
		rot[1][0] = u.y;
		rot[2][0] = u.z;
		rot[0][1] = v.x;
		rot[1][1] = v.y;
		rot[2][1] = v.z;
		rot[0][2] = w.x;
		rot[1][2] = w.y;
		rot[2][2] = w.z;

		view = rot * trans * view;
		printMatrix(view);
		

}


void Camera::orientLookVec(glm::vec3 eyePoint, glm::vec3 lookVec, glm::vec3 upVec) {
}

glm::mat4 Camera::getScaleMatrix() {
	glm::mat4 scaleMat4(1.0);
	return scaleMat4;
}

glm::mat4 Camera::getInverseScaleMatrix() {
	glm::mat4 invScaleMat4(1.0);
	return invScaleMat4;
}

glm::mat4 Camera::getUnhingeMatrix() {
	glm::mat4 unhingeMat4(1.0);
	return unhingeMat4;
}


glm::mat4 Camera::getProjectionMatrix() {
	glm::mat4 projMat4(1.0);
	return projMat4;
}

glm::mat4 Camera::getInverseModelViewMatrix() {
	glm::mat4 invModelViewMat4(1.0);
	return invModelViewMat4;
}


void Camera::setViewAngle (float _viewAngle) {
}

void Camera::setNearPlane (float _nearPlane) {
}

void Camera::setFarPlane (float _farPlane) {
}

void Camera::setScreenSize (int _screenWidth, int _screenHeight) {
}

glm::mat4 Camera::getModelViewMatrix() {
	return view;
}


void Camera::rotateV(float degrees) {
}

void Camera::rotateU(float degrees) {
}

void Camera::rotateW(float degrees) {
}

void Camera::translate(glm::vec3 v) {
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float degrees) {
}


glm::vec3 Camera::getEyePoint() {
	glm::vec3 eyeVec3(0.0f);
	return eyeVec3;
}

glm::vec3 Camera::getLookVector() {
	glm::vec3 lookVec3(0.0f, -1.0f, 0.0f);
	return lookVec3;
}

glm::vec3 Camera::getUpVector() {
	glm::vec3 upVec3(0.0, 0.0, 1.0f);
	return upVec3;
}

float Camera::getViewAngle() {
	return viewAngle;
}

float Camera::getNearPlane() {
	return nearPlane;
}

float Camera::getFarPlane() {
	return farPlane;
}

int Camera::getScreenWidth() {
	return screenWidth;
}

int Camera::getScreenHeight() {
	return screenHeight;
}

float Camera::getScreenWidthRatio() {
	return screenWidthRatio;
}

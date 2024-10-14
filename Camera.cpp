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
		
		eyePoint_ = eyePoint;
		upVec_ = upVec;
		view = glm::mat4(1.0f);
		
	  	glm::vec3 lookVec = glm::normalize(lookatPoint - eyePoint);

		lookVec_ = lookVec;
		w = -glm::normalize(lookVec);
		u = glm::normalize(glm::cross(upVec, w));
		v = glm::cross(w, u);
	
}


void Camera::orientLookVec(glm::vec3 eyePoint, glm::vec3 lookVec, glm::vec3 upVec) {
	std::cout << "orient Look Vec\n"; 
	eyePoint_ = eyePoint;
	upVec_ = upVec;
	lookVec_ = lookVec;
	w = -glm::normalize(lookVec);
	u = glm::normalize(glm::cross(upVec, w));
	v  = glm::cross(w, u);
	std::cout << "ended orient Look vec\n";

}

glm::mat4 Camera::getScaleMatrix() {
	return scaleMat;
}

glm::mat4 Camera::getInverseScaleMatrix() {
	glm::mat4 invScaleMat4(1.0);
	return invScaleMat4;
}

glm::mat4 Camera::getUnhingeMatrix() {
	return unHingeMat;
}


glm::mat4 Camera::getProjectionMatrix() {
	std::cout << "called get ProjectionMatrix\n";
	float halfHeight = glm::tan(glm::radians(viewAngle) / 2.0f) * farPlane;
		
		float halfWidth = glm::tan(glm::radians(viewAngle * screenWidthRatio) / 2.0f) * farPlane;


		glm::mat4 scaleMat4(1.0f);

		scaleMat4[0][0] = 1 / halfWidth;
		scaleMat4[1][1] = 1 / halfHeight;
		scaleMat4[2][2] = 1 / farPlane;	

		scaleMat = scaleMat4;
		
		float c = - (nearPlane * (1.0f / farPlane));
		
		glm::mat4 unhingeMat4(1.0f);

		unhingeMat4[2][2] = -1.0f / (c+1);
		unhingeMat4[3][2] = c / (c + 1);
		unhingeMat4[3][3] = 0.0f;
		unhingeMat4[2][3] = -1.0f;

		unHingeMat = unhingeMat4;

		glm::mat4 projectionMat4(1.0f);	
		projectionMat = projectionMat4 * unhingeMat4 * scaleMat4;
	
	return projectionMat;
}

glm::mat4 Camera::getInverseModelViewMatrix() {
	glm::mat4 invModelViewMat4(1.0);
	return invModelViewMat4;
}


void Camera::setViewAngle (float _viewAngle) {
	viewAngle = _viewAngle;
}

void Camera::setNearPlane (float _nearPlane) {
	nearPlane = _nearPlane;
}

void Camera::setFarPlane (float _farPlane) {
	farPlane = _farPlane;
}

void Camera::setScreenSize (int _screenWidth, int _screenHeight) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenWidthRatio = (float)screenWidth / (float)screenHeight;
}

glm::mat4 Camera::getModelViewMatrix() {
	std::cout << "called get ViewMatrix\n";
	glm::mat4 view(1.0f);
	glm::mat4 trans(1.0f);
		trans[3][0] = -eyePoint_.x;
		trans[3][1] = -eyePoint_.y;
		trans[3][2] = -eyePoint_.z;

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
	
	return view;
}


void Camera::rotateV(float degrees) {
	// M yaw

	glm::mat4 rotateV_(1.0f);

	rotateV_[0][0] = glm::cos(glm::radians(degrees));
	rotateV_[0][2] = -glm::sin(glm::radians(degrees));
	rotateV_[2][0] = glm::sin(glm::radians(degrees));
	rotateV_[2][2] = glm::cos(glm::radians(degrees));

	u = glm::normalize(glm::vec3(rotateV_ * glm::vec4(u, 1.0f)));
	v = glm::normalize(glm::vec3(rotateV_ * glm::vec4(v, 1.0f)));
	w = glm::normalize(glm::vec3(rotateV_ * glm::vec4(w, 1.0f)));
	

	
}

void Camera::rotateU(float degrees) {
	// M pitch
	
	glm::mat4 rotateU_(1.0f);

	rotateU_[1][1] = glm::cos(glm::radians(degrees));
	rotateU_[2][1] = -glm::sin(glm::radians(degrees));
	rotateU_[1][2] = glm::sin(glm::radians(degrees));
	rotateU_[2][2] = glm::cos(glm::radians(degrees));

    u = glm::normalize(glm::vec3(rotateU_ * glm::vec4(u, 1.0f)));
    v = glm::normalize(glm::vec3(rotateU_ * glm::vec4(v, 1.0f)));
    w = glm::normalize(glm::vec3(rotateU_ * glm::vec4(w, 1.0f)));

}

void Camera::rotateW(float degrees) {
	// M roll
	
	glm::mat4 rotateW_(1.0f);

	rotateW_[0][0] = glm::cos(glm::radians(degrees));
	rotateW_[1][0] = -glm::sin(glm::radians(degrees));
	rotateW_[0][1] = glm::sin(glm::radians(degrees));
	rotateW_[1][1] = glm::cos(glm::radians(degrees));

    u = glm::normalize(glm::vec3(rotateW_ * glm::vec4(u, 1.0f)));
    v = glm::normalize(glm::vec3(rotateW_ * glm::vec4(v, 1.0f)));
    w = glm::normalize(glm::vec3(rotateW_ * glm::vec4(w, 1.0f)));

}

void Camera::translate(glm::vec3 v) {
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float degrees) {
}


glm::vec3 Camera::getEyePoint() {
	return eyePoint_;
}

glm::vec3 Camera::getLookVector() {
	return lookVec_;
}

glm::vec3 Camera::getUpVector() {
	return upVec_;
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

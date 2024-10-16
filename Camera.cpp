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
		lookAtPoint_ = lookatPoint;
		eyePoint_ = eyePoint;
		upVec_ = glm::normalize(upVec);
		
	  	glm::vec3 lookVec = glm::normalize(lookatPoint - eyePoint);  //
    lookVec_ = lookVec;

    w = -glm::normalize(lookVec); 
    u = glm::normalize(glm::cross(upVec_, w));  
    v = glm::cross(w, u);  
	
}


void Camera::orientLookVec(glm::vec3 eyePoint, glm::vec3 lookVec, glm::vec3 upVec) {
	
	lookAtPoint_ = eyePoint + glm::normalize(lookVec);
	eyePoint_ = eyePoint;
	upVec_ = glm::normalize(upVec);
	
	w = -glm::normalize(lookVec);
	lookVec_ = lookVec;
	u = glm::normalize(glm::cross(upVec, w));
	v  = glm::cross(w, u);


}

glm::mat4 Camera::getScaleMatrix() {
	return scaleMat;
}

glm::mat4 Camera::getInverseScaleMatrix() {
	glm::mat4 invScaleMat = glm::inverse(scaleMat);
	return invScaleMat;
}

glm::mat4 Camera::getUnhingeMatrix() {
	return unHingeMat;
}


glm::mat4 Camera::getProjectionMatrix() {
	// std::cout << "called get ProjectionMatrix\n";
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
	glm::mat4 invModelView = glm::inverse(view);
	return invModelView;
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
	// glm::mat4 view = glm::lookAt(eyePoint_, lookAtPoint_, upVec_);
	// return view;
}

void printVector(const std::string& name, const glm::vec3& vec) {
    std::cout << name << " = (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}


void Camera::rotateV(float degrees) {
	// M yaw

	glm::mat4 rotateV_(1.0f);

	rotateV_ = glm::rotate(rotateV_, glm::radians(degrees), v);



	u = glm::normalize(glm::vec3(rotateV_ * glm::vec4(u, 1.0f)));
    w = glm::normalize(glm::vec3(rotateV_ * glm::vec4(w, 1.0f)));

    // Correct cross-product to ensure orthogonal basis vectors
    v = glm::normalize(glm::cross(w, u));
    u = glm::normalize(glm::cross(v, w));

    // Update the look vector, ensuring it matches the negative of the w vector
    lookVec_ = -glm::normalize(w);
}

void Camera::rotateU(float degrees) {


	glm::mat4 rotateU_ = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), u);
    v = glm::normalize(glm::vec3(rotateU_ * glm::vec4(v, 0.0f)));
    w = glm::normalize(glm::vec3(rotateU_ * glm::vec4(w, 0.0f)));


	w = glm::normalize(glm::cross(u, v)); 
    v = glm::normalize(glm::cross(w, u));
	lookVec_ = -glm::normalize(w);
}

void Camera::rotateW(float degrees) {


	glm::mat4 rotateW = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), w);
	glm::mat4 rotateW_ = glm::transpose(rotateW);

    u = glm::normalize(glm::vec3(rotateW_* glm::vec4(u, 0.0f)));
    v = glm::normalize(glm::vec3(rotateW_ * glm::vec4(v, 0.0f)));


    

	v = glm::normalize(glm::cross(w, u)); 
    u = glm::normalize(glm::cross(v, w));

		
	lookVec_ = -glm::normalize(w);
}

void Camera::translate(glm::vec3 v) {
	glm::mat4 translateMat(1.0f);
	translateMat[3][0] = -v.x;
	translateMat[3][1] = -v.y;
	translateMat[3][2] = -v.z;

	eyePoint_ = glm::vec3(translateMat * glm::vec4(eyePoint_, 1.0f));
	

}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float degrees) {
	float theta1 = glm::atan(axis.z, axis.x);
	glm::mat4 m1(1.0f);
	m1[0][0] = glm::cos(theta1);
	m1[2][0] = glm::sin(theta1);
	m1[0][2] = -glm::sin(theta1);
	m1[2][2] = glm::cos(theta1);

	float theta2 = glm::atan(axis.y, axis.x);
	glm::mat4 m2(1.0f);
	m2[0][0] = glm::cos(theta2);
	m2[1][0] = -glm::sin(theta2);
	m2[0][1] = glm::sin(theta2);
	m2[1][1] = glm::cos(theta2);

	glm::mat4 m3(1.0f);
	m3[1][1] = glm::cos(glm::radians(degrees));
	m3[2][1] = -glm::sin(glm::radians(degrees));
	m3[1][2] = glm::sin(glm::radians(degrees));
	m3[2][2] = glm::cos(glm::radians(degrees));

	glm::mat4 rotationMatrix = glm::inverse(m1) * glm::inverse(m2) * m3 * m2 * m1;
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

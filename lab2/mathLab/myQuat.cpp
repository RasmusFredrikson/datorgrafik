#include "MyQuat.h"

using namespace MyMathLab;


MyQuat::MyQuat(void) {
	this->v.x = this->v.y = this->v.z = this->w = 0;
}

MyQuat::MyQuat(float angleDeg, MyVector &axis) {
	this->v.x = axis.x;
	this->v.y = axis.y;
	this->v.z = axis.z;
	this->w = angleDeg;
}

MyQuat::MyQuat(MyPosition &point) {
	this->v.x = point.x;
	this->v.y = point.y;
	this->v.z = point.z;
	this->w = 0;
}

MyQuat MyQuat::addTo(const MyQuat &other) const {
	MyQuat result;
	result.v.x = other.v.x + this->v.x;
	result.v.y = other.v.y + this->v.y;
	result.v.z = other.v.z + this->v.z;
	result.w = other.w + this->w;
	return result;
}

MyQuat MyQuat::multiplyBy(const MyQuat &other) const {
	MyQuat result;
	result.w = this->w*other.w - this->v.x*other.v.x - this->v.y*other.v.y - this->v.z*other.v.z;
	result.v.x = this->w*other.v.x + this->v.x*other.w + this->v.y*other.v.z - this->v.z*other.v.y;
	result.v.y = this->w*other.v.y + this->v.y*other.w + this->v.z*other.v.x - this->v.x*other.v.z;
	result.v.z = this->w*other.v.z + this->v.z*other.w + this->v.x*other.v.y - this->v.y*other.v.x;
	return result;
}

float MyQuat::getMagnitude(void) const {
	float result;
	result = sqrt(pow(this->w, 2) + pow(this->v.x, 2) + pow(this->v.y, 2) + pow(this->v.z, 2));
	return result;
}

void MyQuat::normalise(void) {
	this->w = this->w / this->getMagnitude();
	this->v.x = this->v.x / this->getMagnitude();
	this->v.y = this->v.y / this->getMagnitude();
	this->v.z = this->v.z / this->getMagnitude();
}

MyQuat MyQuat::getConjugate(void) const {
	return MyQuat(this->w, MyVector(-this->v.x, -this->v.y, -this->v.z));
}

MyQuat MyQuat::getInverse(void) const {
	MyQuat result;
	result.w = getConjugate().w / getMagnitude();
	result.v.x = getConjugate().v.x / getMagnitude();
	result.v.y = getConjugate().v.y / getMagnitude();
	result.v.z = getConjugate().v.z / getMagnitude();
	return result;
}

MyMatrix MyQuat::convertToRotationMatrix(void) const {
	GLfloat rotationMatrix[16] = {
		1 - 2 * this->v.y*this->v.y - 2 * this->v.z*this->v.z, 2 * this->v.x*this->v.y - 2 * this->v.z*w, 2 * this->v.x*this->v.z + 2 * this->v.y*w, 0.0,
		2 * this->v.x*this->v.y + 2 * this->v.z*w, 1 - 2 * this->v.x*this->v.x - 2 * this->v.z*this->v.z, 2 * this->v.y*this->v.z - 2 * this->v.x*w, 0.0,
		2 * this->v.x*this->v.z - 2 * this->v.y*w, 2 * this->v.y*this->v.z + 2 * this->v.x*w, 1 - 2 * this->v.x*this->v.x - 2 * this->v.y*this->v.y, 0.0,
		0.0,0.0,0.0,1.0
	};

	glLoadMatrixf(rotationMatrix);
	MyMatrix myMatrix;
	myMatrix.getGLModelviewMatrix();
	
	return myMatrix;
}

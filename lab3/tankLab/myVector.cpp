#include "MyVector.h"

using namespace MyMathLibrary;

MyVector::MyVector(void)
{
	this->x = this->y = this->z = 0.0;
}

MyVector::MyVector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

MyVector::MyVector(MyPosition& start, MyPosition& end)
{
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

MyVector MyVector::addTo(const MyVector &other) const
{
	MyVector result;
	//your code here
	result.x = other.x + this->x;
	result.y = other.y + this->y;
	result.z = other.z + this->z;
	return result;
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
	MyVector result;
	//your code here
	result.x = other.x - this->x;
	result.y = other.y - this->y;
	result.z = other.z - this->z;
	return result;
}

float MyVector::getMagnitude(void) const
{
	float result;
	//your code here
	//square root of ( x^2 + y^2 + z^2)
	result = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	return result;
}

void MyVector::uniformScale(const float m)
{
	//your code here
	this->x = this->x * m;
	this->y = this->y * m;
	this->z = this->z * m;
}

void MyVector::normalise(void)
{
	//your code here
	this->x = this->x / this->getMagnitude();
	this->y = this->y / this->getMagnitude();
	this->z = this->z / this->getMagnitude();
}

void MyVector::setMagnitude(const float m)
{
	if (this->getMagnitude() > 0.0)
	{
		this->normalise();
		this->uniformScale(m);
	}
}

float MyVector::getDotProduct(const MyVector &other) const
{
	float result;
	//your code here
	result = this->x*other.x + this->y*other.y + this->z*other.y;
	return result;
}

MyVector MyVector::getCrossProduct(const MyVector &other) const
{
	MyVector result;
	//your code here
	//(a2b3-a3b2)-(a3b1-a1b3)+(a1b2-a2b1)
	result.x = (this->y*other.z - this->z*other.y);
	result.y = (this->z*other.x - this->x*other.z);
	result.z = (this->x*other.y - this->y*other.x);
	return result;
}

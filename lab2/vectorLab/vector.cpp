#include "vector.h"

using namespace MyOGLProg;

Vector::Vector(void)
{
	this->x = this->y = this->z = 0.0;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

Vector::Vector(Position& start, Position& end)
{
	//initialise this vector from two positions
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

Vector Vector::addTo(const Vector &other) const
{
	//add this vector to other and return the result
	Vector result;
	//your code here
	result.x = other.x + this->x;
	result.y = other.y + this->y;
	result.z = other.z + this->z;
	return result;
}

Vector Vector::subtractFrom(const Vector &other) const
{
	//subtract this vector from other and return the result
	Vector result;
	//your code here
	//code from lab instructions
	result.x = other.x - this->x;
	result.y = other.y - this->y;
	result.z = other.z - this->z;
	return result;
}
		
float Vector::getMagnitude(void) const
{
	//get the length of the vector
	float result;
	//your code here
	//square root of ( x^2 + y^2 + z^2)
	result = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	return result;
}

void Vector::setMagnitude(const float m)
{
	//set the length of the vector
	//your code here
	this->x = this->x / this->getMagnitude() * m;
	this->y = this->y / this->getMagnitude() * m;
	this->z = this->z / this->getMagnitude() * m;
}
	
float Vector::getDotProduct(const Vector &other) const
{
	//return the dot product between this vector and other
	float result;
	//your code here
	result = this->x*other.x + this->y*other.y + this->z*other.y;
	return result;
}

Vector Vector::getCrossProduct(const Vector &other) const
{
	//return the cross product between this vector and other
	Vector result;
	//your code here
	//(a2b3-a3b2)-(a3b1-a1b3)+(a1b2-a2b1)
	result.x = (this->y*other.z - this->z*other.y);
	result.y = (this->z*other.x - this->x*other.z);
	result.z = (this->x*other.y - this->y*other.x);
	return result;
}

void Vector::normalise(void)
{
	//normalise this vector (set its length to 1)
	//your code here
	this->x = this->x / this->getMagnitude();
	this->y = this->y / this->getMagnitude();
	this->z = this->z / this->getMagnitude();
}

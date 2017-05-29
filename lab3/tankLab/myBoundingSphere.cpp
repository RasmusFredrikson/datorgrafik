#include "myBoundingSphere.h"
#include <iostream>

using namespace MyMathLibrary;

MyBoundingSphere::MyBoundingSphere(void) {
	this->position.x = this->position.y = this->position.z = 0;
	this->radians = 1;
	this->pMesh = new ObjMesh;
}

MyBoundingSphere::MyBoundingSphere(ObjMesh* pMesh) {
	this->pMesh = pMesh;
	long x = 0;
	long y = 0;
	long z = 0;
	int sum = 0;

	for (int i = 0; i < pMesh->m_iNumberOfFaces; i++) {
		ObjFace *pf = &pMesh->m_aFaces[i];
		for (int j = 0; j < 3; j++) {
			int vk = pf->m_aVertexIndices[j];
			x += pMesh->m_aVertexArray[vk].x;
			y += pMesh->m_aVertexArray[vk].y;
			z += pMesh->m_aVertexArray[vk].z;
			sum++;
		}
	}
	int divide = pMesh->m_iNumberOfFaces * 3;
	std::cout << "sum: " << sum << " divide: " << divide << std::endl;
	this->position.x = x / divide;
	this->position.y = y / divide;
	this->position.z = z / divide;

	
	float d = 0;

	for (int i = 0; i < pMesh->m_iNumberOfFaces; i++) {
		ObjFace *pf = &pMesh->m_aFaces[i];
		for (int j = 0; j < 3; j++) {
			int vk = pf->m_aVertexIndices[j];
			float v = sqrt(pow(this->position.x - pMesh->m_aVertexArray[vk].x,2) + pow(this->position.y - pMesh->m_aVertexArray[vk].y,2) + pow(this->position.z - pMesh->m_aVertexArray[vk].z,2));
			if (v > d) {
				d = v;
			}
		}
	}

	std::cout << "radians: " << d << std::endl;

	this->radians = d;
}

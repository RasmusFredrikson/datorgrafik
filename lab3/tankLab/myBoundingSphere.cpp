#include "myBoundingSphere.h"

using namespace MyMathLibrary;

MyBoundingSphere::MyBoundingSphere(void) {
	this->position.x = this->position.y = this->position.z = 0;
	this->radians = 1;
	this->pMesh = new ObjMesh;
}

MyBoundingSphere::MyBoundingSphere(MyPosition position, ObjMesh* pMesh) {
	this->position = position;
	this->pMesh = pMesh;
	long x = 0;
	long y = 0;
	long z = 0;
	long avgx, avgy, avgz;
	for (int i = 0; i < pMesh->m_iNumberOfFaces*3; ++i) {
		x += pMesh->m_aVertexArray[i].x;
		y += pMesh->m_aVertexArray[i].y;
		z += pMesh->m_aVertexArray[i].z;
	}
	avgx = ((long)x) / pMesh->m_iNumberOfFaces * 3;
	avgy = ((long)y) / pMesh->m_iNumberOfFaces * 3;
	avgz = ((long)z) / pMesh->m_iNumberOfFaces * 3;

	float d = 0;

	for (int i = 0; i < pMesh->m_iNumberOfFaces * 3; ++i) {
		float v = abs(long(avgx - pMesh->m_aVertexArray[i].x)) + abs(long(avgy - pMesh->m_aVertexArray[i].y)) + abs(long(avgz - pMesh->m_aVertexArray[i].z));
		if (v > d) {
			d = v;
		}
	}

	this->radians = d;
}

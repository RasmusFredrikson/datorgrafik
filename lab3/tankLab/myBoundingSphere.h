#ifndef MYBOUNDINGSPHERE
#define MYBOUNDINGSPHERE

#include <math.h>
#include "myvector.h"
#include "mymatrix.h"
#include "objloader.h"


namespace MyMathLibrary
{

	class MyBoundingSphere {
	public:
		MyBoundingSphere(void);
		MyBoundingSphere(ObjMesh* pMesh);

		~MyBoundingSphere(void) { ; }

		MyPosition position;
		float radians;
		ObjMesh* pMesh;
	};


}

#endif
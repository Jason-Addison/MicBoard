#include "stdafx.h"
#include "Math.h"
#include <random>
#include "Vec3f.h"
#include <math.h>
#include "Matrix4f.h"
Math::Math()
{
}


Math::~Math()
{
}
/*double Math::toRadians(double degrees)
{
return degrees / 180 * 3.14159265;
}*/
float Math::toRadians(float degrees)
{
	return degrees / 180 * 3.14159265;
}

int Math::randomInt(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}

float Math::randomFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

float Math::distance(Vec3f a, Vec3f b)
{
	return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2) + pow(b.getZ() - a.getZ(), 2));
}

float Math::mag(float x, float y, float z)
{
	return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
Vec3f Math::normalize(Vec3f vector)
{
	float m = mag(vector.x, vector.y, vector.z);
	return Vec3f(vector.x / m, vector.y / m, vector.z / m);
}


Matrix4f Math::createTransformationMatrix(float x, float y, float z, float width, float height, float depth, float xRot, float yRot, float zRot)
{
	Matrix4f matrix;

	matrix.scale(width, height, depth);

	Matrix4f xRotation;
	xRotation.rotate(xRot, 1, 0, 0);

	Matrix4f yRotation;
	yRotation.rotate(yRot, 0, 1, 0);

	Matrix4f zRotation;
	zRotation.rotate(zRot, 0, 0, 1);

	matrix.multiply(xRotation);
	matrix.multiply(yRotation);
	matrix.multiply(zRotation);

	matrix.translate(x, y, z);

	return matrix;
}



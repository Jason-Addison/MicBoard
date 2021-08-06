#pragma once
#include "Vec3f.h"
#include "Matrix4f.h"
class Math
{
public:
	Math();
	~Math();
	//static double toRadians(double degrees);
	static float toRadians(float degrees);

	static int randomInt(int min, int max);

	static float randomFloat(float min, float max);

	static float distance(Vec3f a, Vec3f b);

	static Matrix4f createTransformationMatrix(float x, float y, float z, float width, float height, float depth, float xRot, float yRot, float zRot);

	static float mag(float x, float y, float z);

	static Vec3f normalize(Vec3f vector);
};


#pragma once
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"
#include <algorithm>

class Sphere
{
public:

	Sphere(Vec3 pos = Vec3(0.0, 0.0, 0.0), float rad = 1.0, ColorDBL col = ColorDBL(1.0, 1.0, 1.0));

	void Intersection(Ray& r);
	Vec3 getNormal(Vec3 pos);

private:
	Vec3 position;
	float radius;
	ColorDBL color;
};


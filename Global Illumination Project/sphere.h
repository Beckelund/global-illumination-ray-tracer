#pragma once
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"
#include <algorithm>
#include "material.h"

class Sphere
{
public:

	Sphere(Vec3 pos = Vec3(0.0, 0.0, 0.0), float rad = 1.0, Material mat = Material());

	void Intersection(Ray& r);
	Vec3 getNormal(Vec3 pos);
	
	ColorDBL getColor();

private:
	Vec3 position;
	float radius;
	Material material;
};


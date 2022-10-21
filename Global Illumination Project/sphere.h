#pragma once
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"
#include <algorithm>
#include "material.h"
#include "surface.h"

class Sphere : public Surface
{
public:

	Sphere(Vec3 pos = Vec3(0.0, 0.0, 0.0), double rad = 1.0, Material mat = Material());
	Sphere(const Sphere& copy);
	
	void Intersection(Ray& r);
	Vec3 getNormal(Ray& r);
	
	ColorDBL getColor();	//For raycast atm

	Vec3 getPosition() const { return position; };
	double getRadius() const { return radius; };

private:
	Vec3 position;
	double radius;
};


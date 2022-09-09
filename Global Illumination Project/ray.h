#pragma once
#include "vec3.h"
#include "colordbl.h"

/*TODO*/
/*
	
*/

class Ray
{
public:
	//Default
	Ray();

	Ray(Vec3 position, Vec3 direction);

	Ray(Vec3 position, Vec3 direction, Ray* previous);

	Vec3 getDirection() const;
	Vec3 getOrigin() const;
	Vec3 getPoint(double t) const;

private:
	Vec3 pos;
	Vec3 dir;

	Ray* next;
	Ray* prev;

	//ColorDBL color;
};
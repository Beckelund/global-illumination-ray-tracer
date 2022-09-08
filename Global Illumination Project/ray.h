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
	Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(1, 0, 0)) {};

	Ray(Vec3 position, Vec3 direction) : pos(position), dir(direction) {};

	Ray(Vec3 position, Vec3 direction, Ray* previous) : pos(position), dir(direction), prev(previous) {};

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
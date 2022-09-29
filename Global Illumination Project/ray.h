#pragma once
#include <limits>
#include "vec3.h"
#include "colordbl.h"

/*TODO*/
/*
	
*/

class Polygon; // pre-definition of polygon


#ifndef RAY_H
#define RAY_H
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
	ColorDBL getColor() const;
	//void setHit(double t, Polygon* obj, ColorDBL col);
	void setHit(double t, ColorDBL col);
	void setHit(double t, Vec3 hitPoint, Polygon* poygon);

private:
	Vec3 pos;
	Vec3 dir;
	Vec3 end; 
	double t;

	Ray* next;
	Ray* prev;

	Polygon* hitPolygon;

	ColorDBL color;
};
#endif

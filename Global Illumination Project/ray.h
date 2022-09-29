#pragma once
#include <limits>
#include <vector>
#include "vec3.h"
#include "object.h"
#include "colordbl.h"

/*TODO*/
/*
	
*/

class Object;
class Polygon; // pre-definition of polygon
class Sphere;// pre-definition of sphere


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
	Vec3 getEnd() const;
	ColorDBL getColor() const;
	//void setHit(double t, Polygon* obj, ColorDBL col);
	void setHit(double t, ColorDBL col);
	void setHit(double t, Polygon* polygon);
	void setHit(double t, Sphere* sphere);
	ColorDBL castRay(std::vector<Object> &objs);


private:
	Vec3 pos;
	Vec3 dir; 
	double t;

	Ray* next;
	Ray* prev;

	Polygon* hitPolygon;
	Sphere* hitSphere;

	ColorDBL color;
};
#endif

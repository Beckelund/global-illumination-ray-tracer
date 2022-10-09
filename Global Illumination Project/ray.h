#pragma once
#include <limits>
#include <vector>
//#include "object.h"
#include "vec3.h"
#include "colordbl.h"
#include <math.h>

/*TODO*/
/*
	
*/

class Object;
class Surface;
class Polygon; // pre-definition of polygon
class Sphere;// pre-definition of sphere
class AreaLight;


#ifndef RAY_H
#define RAY_H
class Ray
{
public:
	Ray();
	Ray(Vec3 position, Vec3 direction);
	Ray(Vec3 position, Vec3 direction, Ray* previous);

	~Ray();

	Vec3 getDirection() const;
	Vec3 getOrigin() const;
	Vec3 getPoint(double t) const;
	Vec3 getEnd() const;
	Surface* getStarSurface() const;
	//void setHit(double t, Polygon* obj, ColorDBL col);
	
	//Set hit
	void setHit(double t, Surface* surface);
	
	ColorDBL castRay(std::vector<Object> &objs, std::vector<AreaLight>& lights);

	int maxBounce = 3;

private:
	Vec3 pos;
	Vec3 dir; 
	double t;

	Ray* next;
	Ray* prev;

	Surface* hitSurface;
	Surface* originSurface;
};
#endif

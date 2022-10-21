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
class PhotonMap;


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
	Surface* getStartSurface() const;
	Surface* getHitSurface() const;
	//void setHit(double t, Polygon* obj, ColorDBL col);
	
	//Set hit
	void setHit(double t, Surface* surface);
	
	ColorDBL castRay(std::vector<Object> &objs, std::vector<AreaLight>& lights, PhotonMap& photonmap, bool has_hit_lambertian = true);
	ColorDBL PhotonContribution(PhotonMap& photonmap);
	ColorDBL DirectLightContribution(std::vector<Object>& objs, std::vector<AreaLight>& lights);
	
	Ray* BounceSelf(std::vector<Object>& objs);	//Used for caustics, avoid using otherwise
	
	double speed = 1.0;

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

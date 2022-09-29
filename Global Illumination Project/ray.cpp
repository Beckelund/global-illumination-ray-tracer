#include "ray.h"
#include "object.h"
#include "polygon.h"
#include "sphere.h"

Ray::Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(1, 0, 0)), next(nullptr), prev(nullptr) {
	t = DBL_MAX;
}

Ray::Ray(Vec3 position, Vec3 direction) : pos(position), dir(direction), next(nullptr), prev(nullptr){
	t = DBL_MAX;
}

Ray::Ray(Vec3 position, Vec3 direction, Ray* previous) : Ray(position, direction) {
	prev = previous;
	t = DBL_MAX;
}

Vec3 Ray::getDirection() const {
	return dir;
}

Vec3 Ray::getOrigin() const {
	return pos;
}

Vec3 Ray::getPoint(double t) const {
	return pos + dir * t;
}

Vec3 Ray::getEnd() const {
	return pos + dir * t;
}

ColorDBL Ray::getColor() const
{
	if (hitPolygon != nullptr)
	{
		return hitPolygon->getColor();
	}
	else if (hitSphere != nullptr)
	{
		return hitSphere->getColor();
	}

	return ColorDBL(0.0, 0.0, 0.0);
}

void Ray::setHit(double t1, ColorDBL col) {
	if (t1 < t) {
		t = t1;
		color = col;
	}
}

void Ray::setHit(double t, Polygon* polygon)
{
	if (t < this->t) {
		this->t = t;
		hitSphere = nullptr;
		hitPolygon = polygon;
	}
}

void Ray::setHit(double t, Sphere* sphere)
{
	if (t < this->t) {
		this->t = t;
		
		hitSphere = sphere;
		hitPolygon = nullptr;
	}
}

ColorDBL Ray::castRay(std::vector<Object>& objs)
{

	for (int i = 0; i < objs.size(); i++)
	{
		objs[i].Intersection(*this);
	}
	
	return this->getColor();
}

/*
ColorDBL Ray::castRay(std::vector<Object>& objs) {
	return ColorDBL(1, 1, 0);
}
*/

#include "ray.h"

Ray::Ray() : pos(Vec3(0, 0, 0)), dir(Vec3(1, 0, 0)), next(nullptr), prev(nullptr)
{
}

Ray::Ray(Vec3 position, Vec3 direction) : pos(position), dir(direction), next(nullptr), prev(nullptr)
{
}

Ray::Ray(Vec3 position, Vec3 direction, Ray* previous) : Ray(position, direction)
{
	prev = previous;
}

Vec3 Ray::getDirection() const {
	return dir;
}

Vec3 Ray::getOrigin() const
{
	return pos;
}

Vec3 Ray::getPoint(double t) const
{
	return pos + dir * t;
}

#include "ray.h"

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

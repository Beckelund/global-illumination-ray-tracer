#include "sphere.h"

Sphere::Sphere(Vec3 pos, float rad, ColorDBL col)
{
	position = pos;
	radius = rad;
	color = col;
}

void Sphere::Intersection(Ray& r)
{
	Vec3 L = position - r.getOrigin();
	float tca = L * r.getDirection();
	if (tca < 0) return;
	float d2 = L * L - tca * tca;
	if (d2 > radius * radius) return;
	float thc = sqrt(radius * radius - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 > t1) std::swap(t0, t1);
	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return; // both t0 and t1 are negative 
	}
	r.setHit(t0, color);
}

Vec3 Sphere::getNormal(Vec3 pos) {
	return (pos - position).normalize();
}

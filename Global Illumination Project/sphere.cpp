#include "sphere.h"

Sphere::Sphere(Vec3 pos, double rad, Material mat)
{
	position = pos;
	radius = rad;
	material = mat;
	type = Surface::Type::Sphere;
}

Sphere::Sphere(const Sphere& copy)
{
	position = copy.position;
	radius = copy.radius;
	material = copy.material;
	type = Surface::Type::Sphere;
}


void Sphere::Intersection(Ray& r)
{
	Vec3 L = position - r.getOrigin();
	double tca = L * r.getDirection();
	if (tca < 0) return;
	double d2 = L * L - tca * tca;
	if (d2 > radius * radius) return;
	double thc = sqrt(radius * radius - d2);
	double t0 = tca - thc;
	double t1 = tca + thc;
	if (t0 > t1) std::swap(t0, t1);
	if (t0 < 0.0003) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return; // both t0 and t1 are negative 
	}
	//r.setHit(t0, color);
	r.setHit(t0, this);
}

Vec3 Sphere::getNormal(Ray& r) {
	return (r.getEnd() - position).normalize();
}

ColorDBL Sphere::getColor()
{
	return material.getColor();
}

void Sphere::Move(Vec3 pos) {
	position = position + pos;
}

#include "material.h"
#include "ray.h"

Material::Material(): type(Material::Type::lambertian), color(ColorDBL(1.0,1.0,1.0)), reflectivity(0.5), IOR(1.0) {
}

Material::Material(ColorDBL col): Material() {
	color = col;
}

Material::Material(Type t, ColorDBL col): Material(col) {
	type = t;
}

Ray* Material::BRDF(Vec3 Normal, Ray& prev)
{
	Vec3 dir;
	//Ray* r;
	switch (type) {
	case Material::mirror:
		dir = prev.getDirection();
		dir = dir - Normal * (dir * Normal) * 2;
		return new Ray(prev.getEnd(), dir);
		break;
	case Material::transparent:
		break;
	case Material::lambertian:	//TODO implement correct random azimuth and inclination
		return lambertianReflector(Normal, prev);
		
		break;
	default:
		break;
	}

	return nullptr;
}

Ray* Material::lambertianReflector(Vec3 Normal, Ray& prev)
{
	if (prev.maxBounce == 0) return nullptr;
	
	double azimuth = ((double)rand() / RAND_MAX) * 2 * 3.14;
	double inclination = ((double)rand() / RAND_MAX) * 3.14;


	Vec3 cartesian = Vec3(sin(inclination) * cos(azimuth), sin(inclination) * sin(azimuth), cos(inclination));
	if (cartesian * Normal > 0)
		cartesian = cartesian * -1;

	Vec3 startPoint = prev.getEnd();

	Ray* r = new Ray(startPoint, cartesian);
	r->maxBounce = prev.maxBounce - 1;
	return r;
}
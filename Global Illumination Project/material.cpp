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
	// TODO Implement russian roulette  
	
	double azimuth = ((double)rand() / RAND_MAX) * 2 * 3.14;
	double inclination = asin(sqrt(1 - ((double)rand() / RAND_MAX)));

	Vec3 cl = Vec3(sin(inclination) * cos(azimuth), sin(inclination) * sin(azimuth), cos(inclination));

	// Local coordianta
	Vec3 zl = Normal;
	Vec3 yl = prev.getDirection();
	yl = yl - zl*(yl * zl);
	yl = (yl * (-1)).normalize();
	Vec3 xl = yl % zl;

	Vec3 direction = cl.matrixMult(xl, yl, zl);

	Vec3 startPoint = prev.getEnd();

	Ray* r = new Ray(startPoint, direction, &prev);
	r->maxBounce = prev.maxBounce - 1;
	return r;
}
#include "material.h"
#include "ray.h"

Material::Material(): type(Material::Type::lambertian), color(ColorDBL(1.0,1.0,1.0)), reflectivity(0.8), IOR(1.0) {
}

Material::Material(ColorDBL col): Material() {
	color = col;
}

Material::Material(Type t, ColorDBL col): Material(col) {
	type = t;
}

Ray* Material::BRDF(Vec3 Normal, Ray& prev) {
	double R0;
	double R;
	double cosAng;
	switch (type) {
	case Material::mirror:
		return Reflection(Normal, prev);
		break;
	case Material::transparent:
		R0 = pow((prev.speed - IOR) / (prev.speed + IOR), 2);
		if (prev.getStarSurface() == prev.getHitSurface()) {
			Normal = Normal * (-1);
			R0 = pow((IOR - prev.speed) / (prev.speed + IOR), 2);
		}
		cosAng = abs(Normal * (prev.getDirection() * (-1)));
		R = R0 + (1 - R0) * pow((1 - cosAng), 5);
		if (((double)rand() / RAND_MAX) < R)
			return Reflection(Normal, prev);
		else
			return Refraction(Normal, prev);
		break;
	case Material::lambertian:
		return lambertianReflector(Normal, prev);
		break;
	default:
		break;
	}

	return nullptr;
}

Ray* Material::Reflection(Vec3 Normal, Ray& prev) {
	Vec3 dir = prev.getDirection();
	dir = dir - Normal * (dir * Normal) * 2;
	return new Ray(prev.getEnd(), dir);
}

Ray* Material::Refraction(Vec3 Normal, Ray& prev) {
	double newSpeed = IOR;
	double R = (prev.speed / IOR);
	if (prev.getStarSurface() == prev.getHitSurface()) {
		R = IOR;
		newSpeed = 1;
	}

	Vec3 dir = prev.getDirection();
	double dirDotNorm = dir * Normal;
	dir = dir * R + Normal * (-R * (dirDotNorm)-sqrt(1 - R * R * (1 - dirDotNorm * dirDotNorm)));
	//return nullptr;
	Ray* r = new Ray(prev.getEnd(), dir, &prev);
	r->speed = newSpeed;
	return r;
}


Ray* Material::lambertianReflector(Vec3 Normal, Ray& prev) {
	//if (prev.maxBounce == 0) return nullptr;
	// TODO Implement russian roulette  
	
	// Russian roulette 
	double azimuth = ((double)rand() / RAND_MAX) * 2 * 3.14/reflectivity;
	if (azimuth > 2 * 3.14) return nullptr; // ray termination 


	double inclination = asin(sqrt(1 - ((double)rand() / RAND_MAX)));

	Vec3 cl = Vec3(sin(inclination) * cos(azimuth), sin(inclination) * sin(azimuth), cos(inclination));

	// TODO there are som black pixles showing up after this was added 
	// Local coordianta
	Vec3 zl = Normal;
	Vec3 yl = prev.getDirection();
	yl = yl - zl*(yl * zl);
	yl = (yl * (-1)).normalize();
	Vec3 xl = yl % zl;

	/*
	if (cl * Normal < 0)
		cl = cl * (-1);
	*/

	Vec3 direction = cl.matrixMult(xl, yl, zl);

	Vec3 startPoint = prev.getEnd();

	Ray* r = new Ray(startPoint, direction, &prev);
	r->maxBounce = prev.maxBounce - 1;
	return r;
}
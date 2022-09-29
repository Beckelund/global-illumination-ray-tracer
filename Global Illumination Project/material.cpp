#include "material.h"
#include "ray.h"

Material::Material(): type(Material::Type::lambertian), color(ColorDBL(1.0,1.0,1.0)),reflectance(0.5),IOR(1.0) {
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
	switch (type) {
	case Material::mirror:
		dir = prev.getDirection();
		dir = dir - Normal * (dir * Normal) * 2;
		return new Ray(prev.getEnd(), dir);
		break;
	case Material::transparent:
		break;
	case Material::lambertian:

		break;
	default:
		break;
	}

	return nullptr;
}


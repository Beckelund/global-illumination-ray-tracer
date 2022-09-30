#include "arealight.h"

AreaLight::AreaLight(Vec3 pos, Vec3 inV1, Vec3 inV2, ColorDBL col, double flux)
{
	position = pos;
	v1 = inV1;
	v2 = inV2;
	color = col;

	//calculate normal
	normal = (v1 % v2).normalize();

	//Calculate irradiance
	irradiance = flux / (v1 % v2).length();

	area = (v1 % v2).length();
}

Vec3 AreaLight::RandomPoint()
{
	double r1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	double r2 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

	return position + v1 * r1 + v2 * r2;
}
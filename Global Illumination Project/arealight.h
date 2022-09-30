#pragma once
#include "vec3.h"
#include "colordbl.h"
#include <cstdlib>	//rand()

class AreaLight
{
public:

	//Constructors
	AreaLight(Vec3 pos, Vec3 v1, Vec3 v2, ColorDBL color, double flux);
	
	//
	Vec3 RandomPoint();

	//Getters
	ColorDBL getColor() { return color; }
	double getIrradiance() { return irradiance; }
	double getArea() { return area; }
	
private:
	ColorDBL color;
	double irradiance;
	double area;
	
	Vec3 normal;

	Vec3 position;
	Vec3 v1;
	Vec3 v2;
};


#pragma once
#include "colordbl.h"
//#include "ray.h"

class Material {
public:
	enum Type {mirror,transparent,lambertian};
	
	Material();
	Material(ColorDBL col);
	Material(Type t, ColorDBL col);

	//Ray* BRDF(Vec3 Normal,Ray& prev);


private: 
	Type type;
	ColorDBL color;
	float reflectance;
	float IOR;

};


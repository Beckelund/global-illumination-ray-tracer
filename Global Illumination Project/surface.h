#pragma once
#include "vec3.h"
#include "ray.h"
#include "material.h"

class Surface
{
public:
	
	
	virtual Material getMaterial() { return material; };
	virtual Vec3 getNormal(Ray& r) = 0;
	virtual void Intersection(Ray& r) = 0;

	//Setters
	void setMaterial(Material mat) { material = mat; }
	
protected:
	Material material;
};


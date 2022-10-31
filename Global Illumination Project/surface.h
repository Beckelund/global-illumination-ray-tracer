#pragma once
#include "vec3.h"
#include "ray.h"
#include "material.h"

class Surface
{
public:
	enum Type { Unset, Polygon, Sphere };
	
	virtual Material getMaterial() { return material; };
	virtual Vec3 getNormal(Ray& r) = 0;
	virtual void Intersection(Ray& r) = 0;
	virtual void Move(Vec3 pos) = 0;

	//Setters
	void setMaterial(Material mat) { material = mat; }
	
	Surface::Type getType() { return type; }
	
protected:
	Type type = Surface::Type::Unset;
	Material material;
};


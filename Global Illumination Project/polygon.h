#pragma once
#include <vector>
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"
#include "material.h"

class Polygon {
public:
	struct Vertex {
		Vec3 pos;
		ColorDBL col; 
		Vertex(Vec3 p,ColorDBL c):pos(p), col(c){}

	};
	
	Polygon(std::vector<Vertex> vertices);
	Polygon(std::vector<Vertex> vertices, Material mat);

	void Intersection(Ray& r);

	//Get
	ColorDBL getColor();
	Vec3 getNormal() { return normal; }
	Material getMaterial() { return material; }

	//Set
	void setMaterial(Material mat) { material = mat; }

private:
	Vec3 normal;
	std::vector<Vertex> vertices;
	Material material;
};


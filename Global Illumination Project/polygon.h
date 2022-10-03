#pragma once
#include <vector>
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "surface.h"

class Polygon : public Surface {
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
	Vec3 getNormal(Ray& r) { return normal; }

	//Set

private:
	Vec3 normal;
	std::vector<Vertex> vertices;
};


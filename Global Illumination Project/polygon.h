#pragma once
#include <vector>
#include "colordbl.h"
#include "vec3.h"
#include "ray.h"

class Polygon {
public:
	struct Vertex {
		Vec3 pos;
		ColorDBL col; 
		Vertex(Vec3 p,ColorDBL c):pos(p), col(c){}

	};

	Polygon(std::vector<Vertex> vertices);

	double Intersection(Ray r);


private:
	Vec3 normal;
	std::vector<Vertex> vertices;
};

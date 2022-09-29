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
	Polygon(std::vector<Vertex> vertices, ColorDBL col);

	void Intersection(Ray& r);

	//Get
	ColorDBL getColor() { return color; }
	Vec3 getNormal() { return normal; }

	//Set
	void setColor(ColorDBL col) { color = col; }

private:
	Vec3 normal;
	std::vector<Vertex> vertices;
	ColorDBL color;
};


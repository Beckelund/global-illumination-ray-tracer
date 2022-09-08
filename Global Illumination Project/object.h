#pragma once
#include "polygon.h"

class Object {
public:
	Object();
	Object(const char* filePath);
	Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind);
	double Intersection(Ray r);

private:
	std::vector<Polygon> polygons;
	std::vector<Polygon::Vertex> vertices;
	std::vector<int> indices; 
};


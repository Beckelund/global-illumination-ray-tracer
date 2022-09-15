#pragma once
#include <iostream>
#include <fstream>
#include "polygon.h"

class Object {
public:
	Object();
	Object(const char* filePath);
	Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind);
	void Intersection(Ray& r);

private:
	std::vector<Polygon> polygons;
};


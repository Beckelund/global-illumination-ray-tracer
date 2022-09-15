#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "polygon.h"

class Object {
public:
	Object();
	Object(const char* filePath);
	Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind);
	void Intersection(Ray& r);

private:
	void createPolygonsFromList(std::vector<Polygon::Vertex>& vert, std::vector<int>& ind);
	
	std::vector<Polygon> polygons;
	std::vector<Polygon::Vertex> vertices;
	std::vector<int> indices; 
};


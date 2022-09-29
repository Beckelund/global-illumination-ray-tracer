#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "polygon.h"
#include "sphere.h"

class Object {
public:
	//Constructors
	Object();
	Object(const char* filePath);
	//Create Polygons from vertices and indices
	Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind);
	Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind, Material mat = ColorDBL(1.0, 1.0, 1.0));

	//Add To object
	void AddSphere(Sphere in);
	void AddPolygon(Polygon in);

	//Intersection
	void Intersection(Ray& r);

private:
	void createPolygonsFromList(std::vector<Polygon::Vertex>& vert, std::vector<int>& ind);
	
	std::vector<Polygon> polygons;
	std::vector<Sphere> spheres;
};


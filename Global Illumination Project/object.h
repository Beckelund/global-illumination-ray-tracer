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

	//Set
	void SetMaterial(Material mat);
	void SetMaterial(Material mat, int index);	//For setting a specific surface


	//Intersection
	void Intersection(Ray& r);

private:
	void createPolygonsFromList(std::vector<Polygon::Vertex>& vert, std::vector<int>& ind);

	bool boundingIntersect(Ray& ray);	//TODO remove this function
	Vec3 origin;	//for bounding check, TODO remove this
	double bounding = -1;	//To optimize intersections TODO remove this

	std::vector<Surface*> surfaces;
};


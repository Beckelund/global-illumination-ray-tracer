#include "object.h"

Object::Object(){}

 
Object::Object(const char* filePath){
//TODO implemetn creating object from a .obj file 
}

Object::Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind) : vertices(vert), indices(ind) {
	int start  = -1;
	std::vector<Polygon::Vertex> polygon;
	for (int i = 0; i < indices.size();i++) {
		if (start == -1) {
			start = indices[i];
		}
		else if(start == indices[i]) {
			polygons.push_back(Polygon(polygon));
			polygon.clear();
			start = -1;
			continue;
		}
		polygon.push_back(vertices[indices[i]]);
	}
}

double Object::Intersection(Ray r) {
	double t = -1;
	double tempt = -1;
	for (auto& poly : polygons) {
		tempt = poly.Intersection(r);
		t = (tempt > 0 && (tempt < t||t < 0)) ? tempt : t;
	}
	return t;
}
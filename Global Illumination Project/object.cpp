#include "object.h"

Object::Object(){}

 
Object::Object(const char* filePath){
//TODO implemetn creating object from a .obj file 
	std::ifstream file;
	file.open(filePath,std::ifstream::in);
	if (!file.is_open())
		std::cout << " The object file was not found \n";

}

Object::Object(std::vector<Polygon::Vertex> vertices, std::vector<int> indices) {
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

void Object::Intersection(Ray& r) {
	for (auto& poly : polygons) {
		poly.Intersection(r);
	}
}

#include "object.h"

Object::Object(){}

 
Object::Object(const char* filePath){
//TODO implemetn creating object from a .obj file 
	std::ifstream file;
	file.open(filePath,std::ifstream::in);
	if (!file.is_open())
		std::cout << " The object file was not found \n";

	std::vector<int> ind;
	std::vector<Polygon::Vertex> vert; 
	const unsigned int maxLength = 40;
	
	


	for (char line[maxLength]; file.getline(&line[0], maxLength);) {
		
		if (line[0] == 'v'&& line[1] == ' ') { // vertex
			std::string ln = line;
			// find X
			size_t stringStart = 2;
			size_t stringEnd = ln.find(' ', stringStart);
			std::string xString = ln.substr(stringStart, stringEnd - stringStart);
			
			// find y
			stringStart = stringEnd + 1;
			stringEnd = ln.find(' ', stringStart);
			std::string yString = ln.substr(stringStart, stringEnd - stringStart);

			// find z
			stringStart = stringEnd + 1;
			ln.erase(0, stringStart);
			std::string zString = ln;
		
			vert.push_back(Polygon::Vertex(
				Vec3(std::stod(xString), std::stod(yString), std::stod(zString)),
				ColorDBL(0.9, 0.9, 0.9)
			));
		}
		if (line[0] == 'f') { // face
			std::string ln = line;
			ln.erase(0, 2); // remove the f;
			int start = -1; 
			int pos = 0;
			while ((pos = ln.find(' ')) != std::string::npos ||!ln.empty()) {
				std::string faceVertex = ln.substr(0, pos);
				ln.erase(0, pos + 1);
				int pos2 = 0;
				int index = 0; 
				while ((pos2 = faceVertex.find('/')) != std::string::npos) {
					std::string v = faceVertex.substr(0, pos2);
					if (index == 0) { // = 0 is vertex index, = 1 is vertex-textur-coord index, = 2  is vertex-normal index 
						ind.push_back(stoi(v) - 1);
						if (start == -1)
							start = stoi(v) - 1; // make sure the start index is saved 
						break;
					}
					index++;
					faceVertex.erase(0, pos2 + 1);
				}
				if (pos == -1)
					ln.clear();
			}
			ind.push_back(start); // clost the face; 

		}

	}
	createPolygonsFromList(vert, ind);
}

Object::Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind) {
	createPolygonsFromList(vert, ind);
}

void Object::Intersection(Ray& r) {
	for (auto& poly : polygons) {
		poly.Intersection(r);
	}
}


void Object::createPolygonsFromList(std::vector<Polygon::Vertex> &vert, std::vector<int> &ind) {
	int start = -1;
	std::vector<Polygon::Vertex> polygon;
	for (int i = 0; i < ind.size(); i++) {
		if (start == -1) {
			start = ind[i];
		}
		else if (start == ind[i]) {
			polygons.push_back(Polygon(polygon));
			polygon.clear();
			start = -1;
			continue;
		}
		polygon.push_back(vert[ind[i]]);
	}
}

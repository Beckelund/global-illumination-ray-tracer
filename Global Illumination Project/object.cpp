#include "object.h"

Object::Object(){}

 
Object::Object(const char* filePath){
	std::ifstream file;
	file.open(filePath,std::ifstream::in);
	if (!file.is_open())
		std::cout << " The object file was not found \n";

	std::vector<int> ind;
	std::vector<Polygon::Vertex> vert; 
	const unsigned int maxLength = 255;
	
	origin = Vec3(0, 0, 0);
	Vec3 currentVertexPos;

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
		
			currentVertexPos = Vec3(std::stod(xString), std::stod(yString), std::stod(zString));
			origin = origin + currentVertexPos;// sum the position 
			vert.push_back(Polygon::Vertex(currentVertexPos, ColorDBL(0.9, 0.9, 0.9)));
		}
		if (line[0] == 'f') { // face
			std::string ln = line;
			ln.erase(0, 2); // remove the f;
			int start = -1; 
			size_t pos = 0;
			while ((pos = ln.find(' ')) != std::string::npos ||!ln.empty()) {
				std::string faceVertex = ln.substr(0, pos);
				ln.erase(0, pos + 1);
				size_t pos2 = 0;
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


	origin = origin / ((double) ind.size());
	for (int i = 1; i < vert.size(); i++)
	{
		if ((vert[i].pos - origin).length() > bounding)
			bounding = (vert[i].pos - origin).length();
	}

	std::reverse(ind.begin(),ind.end());
	createPolygonsFromList(vert, ind);
}

//Create object from vertices
Object::Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind) {
	createPolygonsFromList(vert, ind);
}

Object::Object(std::vector<Polygon::Vertex> vert, std::vector<int> ind, Material mat) {
	createPolygonsFromList(vert, ind);
	
	for (auto& s : surfaces)
	{
		s->setMaterial(mat);
	}
}


void Object::AddSphere(Sphere in)
{
	surfaces.push_back(new Sphere(in));
}

void Object::SetMaterial(Material mat)
{
	for (auto& surface : surfaces)
		surface->setMaterial(mat);

	// TODO
}

void Object::SetMaterial(Material mat, int index)
{
	if (index < surfaces.size())
		surfaces[index]->setMaterial(mat);
}

void Object::Move(Vec3 pos) {
	for (auto& surface : surfaces) {
		surface->Move(pos);
	}
	origin = origin + pos;
}

bool Object::boundingIntersect(Ray& r)
{
	Vec3 L = origin - r.getOrigin();
	double tca = L * r.getDirection();
	if (tca < 0) return false;
	double d2 = L * L - tca * tca;
	if (d2 > bounding * bounding) return false;
	double thc = sqrt(bounding * bounding - d2);
	double t0 = tca - thc;
	double t1 = tca + thc;
	if (t0 > t1) std::swap(t0, t1);
	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}
	
	return true;
}

void Object::Intersection(Ray& r) {
	
	if (bounding != -1)	//TODO remove bounding box
		if (boundingIntersect(r) == false) return;
		
	for (auto& surface : surfaces) {
		if (surface != r.getStartSurface() || surface->getMaterial().getType() == Material::Type::transparent)
			surface->Intersection(r);
	}
}

std::vector<Surface*> Object::getTransparentSurfaces()
{
	std::vector<Surface*> result;

	for (auto& surface : surfaces)
	{
		if (surface->getMaterial().getType() == Material::Type::transparent)
			result.push_back(surface);
	}

	return result;
}


void Object::createPolygonsFromList(std::vector<Polygon::Vertex> &vert, std::vector<int> &ind) {
	int start = -1;
	std::vector<Polygon::Vertex> vertices;
	for (int i = 0; i < ind.size(); i++) {
		if (start == -1) {
			start = ind[i];
		}
		else if (start == ind[i]) {
			surfaces.push_back(new Polygon(vertices));
			vertices.clear();
			start = -1;
			continue;
		}
		vertices.push_back(vert[ind[i]]);
	}
}
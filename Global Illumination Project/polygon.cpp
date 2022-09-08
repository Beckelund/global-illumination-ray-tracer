#include "polygon.h"

Polygon::Polygon(std::vector<Vertex> vertices): vertices(vertices) {
	Vec3 v1 = this->vertices[1].pos - this->vertices[0].pos;
	Vec3 v2 = this->vertices[2].pos - this->vertices[0].pos;
	normal = (v2 % v1).normalize();
}

//returns -1 if the Ray does not intersect
double Polygon::Intersection(Ray r) {
	// plane intersection 
	double demominator = normal * r.getDirection();
	if (demominator >= 0)
		return -1.0;
	double t = ((vertices[0].pos - r.getOrigin()) * normal) / demominator;
	Vec3 hitPoint = r.getPoint(t);


	//triangle intersection (Möller Trumbore algorithm for trianlges)
	Vec3 T = r.getOrigin() - vertices[0].pos;
	Vec3 E1 = vertices[1].pos - vertices[0].pos;
	Vec3 E2 = vertices[2].pos - vertices[0].pos;
	Vec3 D = r.getDirection() - r.getOrigin();
	Vec3 P = D % E2;
	Vec3 Q = T % E1;

	double PE1inv = 1/(P * E1);
	double u = PE1inv * (P * T);
	double v = PE1inv * (Q * D);

	if (u >= 0 && v >= 0 && u + v <= 1)
		return t;
	return -1.0;
}

#include "polygon.h"

Polygon::Polygon(std::vector<Vertex> vertices): vertices(vertices) {
	Vec3 v1 = this->vertices[1].pos - this->vertices[0].pos;
	Vec3 v2 = this->vertices[2].pos - this->vertices[0].pos;
	normal = (v2 % v1).normalize();
}

void Polygon::Intersection(Ray& r) {

	for (int i = 0; i < vertices.size() - 2; i++) {

		// plane intersection 
		double demominator = normal * r.getDirection();
		if (demominator >= 0)
			return;
		double t = ((vertices[0].pos - r.getOrigin()) * normal) / demominator;
		Vec3 hitPoint = r.getPoint(t);


		//triangle intersection (Möller Trumbore algorithm for trianlges)
		Vec3 T = r.getOrigin() - vertices[0].pos;
		Vec3 D = r.getDirection() - r.getOrigin();
		Vec3 E1 = vertices[i+1].pos - vertices[0].pos;
		Vec3 E2 = vertices[i+2].pos - vertices[0].pos;
		Vec3 P = D % E2;
		Vec3 Q = T % E1;

		double PE1inv = 1/(P * E1);
		double u = PE1inv * (P * T);
		double v = PE1inv * (Q * D);

		if (u >= 0 && v >= 0 && u + v <= 1) {
			double v0 = (1 - u - v);
			double v1 = u;
			double v2 = v;
			ColorDBL color = vertices[0].col * v0 + vertices[i+1].col * v1 + vertices[i+2].col * v2;
			color = color * ((r.getDirection()*( - 1)) * normal);
			r.setHit(t, color);
			return;
		}
	}
}

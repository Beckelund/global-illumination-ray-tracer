#include "polygon.h"

Polygon::Polygon(std::vector<Vertex> vertices): vertices(vertices) {
	Vec3 v1 = this->vertices[1].pos - this->vertices[0].pos;
	Vec3 v2 = this->vertices[2].pos - this->vertices[0].pos;
	normal = (v2 % v1).normalize();
	material = ColorDBL(1.0, 1.0, 1.0);
	type = Surface::Type::Polygon;
}

Polygon::Polygon(std::vector<Vertex> vertices, Material mat) : Polygon(vertices) {
	material = mat;
	type = Surface::Type::Polygon;
}

void Polygon::Intersection(Ray& r) {

	for (int i = 0; i < vertices.size() - 2; i++) {

		// plane intersection 
		double demominator = normal * r.getDirection();
		if (demominator >= 0) // wrong normal direction 
			return;
		double t = ((vertices[0].pos - r.getOrigin()) * normal) / demominator;
		if (t < 0) // Behind the ray origin 
			return;


		//triangle intersection (Möller Trumbore algorithm for trianlges)
		Vec3 T = r.getOrigin() - vertices[0].pos;
		Vec3 D = r.getDirection();// - r.getOrigin();
		Vec3 E1 = vertices[i+1].pos - vertices[0].pos;
		Vec3 E2 = vertices[i+2].pos - vertices[0].pos;
		Vec3 P = D % E2;
		Vec3 Q = T % E1;

		double PE1inv = 1/(P * E1);
		double u = PE1inv * (P * T);
		double v = PE1inv * (Q * D);

		if (u >= 0 && v >= 0 && u + v <= 1) {
			/*
			double v0 = (1 - u - v);
			double v1 = u;
			double v2 = v;
			ColorDBL color = vertices[0].col * v0 + vertices[i+1].col * v1 + vertices[i+2].col * v2;
			color = color * ((r.getDirection()*( - 1)) * normal);
			*/
			//ColorDBL hitColor = this->getColor() * ((r.getDirection() * (-1)) * normal);	//Phong shader remove later
			//r.setHit(t, ColorDBL(0.0,0.0,0.0));	//TODO remove later, use HitPolygon method instead
			r.setHit(t, this);
			return;
		}
	}
}

ColorDBL Polygon::getColor()
{
	return material.getColor();
}

void Polygon::Move(Vec3 pos) {
	for (auto& vert : vertices)
		vert.pos = vert.pos + pos;
}

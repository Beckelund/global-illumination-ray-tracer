#pragma once
#include "vec3.h"
#include "colordbl.h"
#include <cstdlib>	//rand()
#include "surface.h"
#include "photon.h"

class AreaLight
{
public:

	//Constructors
	AreaLight(Vec3 pos, Vec3 v1, Vec3 v2, ColorDBL color, double flux);
	
	//
	Vec3 RandomPoint() const;

	//Getters
	ColorDBL getColor() const { return color; }
	double getRadiosity() const { return radiosity; }
	double getRadiance() const { return radiosity / 3.1415; } // energy leving per solid angle
	double getArea() const { return area; }
	
	//Photon map support
	double CalculateFluxOnSurface(const Surface& s) const;	//Add support
	double CalculateFluxOnSurface(const Sphere* s) const;

	std::vector<Photon> GeneratePhotons(std::vector<Object>& objects, Surface* s, int n_photons) const;
	std::vector<Photon> GeneratePhotons(std::vector<Object>& objects, Sphere* s, int n_photons) const;

private:
	ColorDBL color;
	double area;
	double radiosity; // energy leving per unit area
	double flux; // total energy emitted 
	
	Vec3 normal;

	Vec3 position;
	Vec3 v1;
	Vec3 v2;
};


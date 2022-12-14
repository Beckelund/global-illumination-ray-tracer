#pragma once

#include "vec3.h"

class Photon
{
public:
	Photon() = delete;
	Photon(Vec3 pos, Vec3 dir, double flx);
	Photon(const Photon& other);
	
	Vec3 getPosition() const { return position; }
	Vec3 getDirection() const { return direction; }
	double getFlux() const { return flux; }
	
private:
	Vec3 position;
	Vec3 direction;
	double flux;
};
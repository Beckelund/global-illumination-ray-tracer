#pragma once

#include "vec3.h"

class Photon
{
public:
	Photon() = delete;
	Photon(Vec3 pos, Vec3 dir, double flx);

	Vec3 getPosition() const { return position; }
	
private:
	Vec3 position;
	Vec3 direction;
	double flux;
};
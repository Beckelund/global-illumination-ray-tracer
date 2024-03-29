#include "photon.h"

Photon::Photon(Vec3 pos, Vec3 dir, double flx)
{
	position = pos;
	direction = dir;
	flux = flx;
}

Photon::Photon(const Photon& other)
{
	position = other.position;
	direction = other.direction;
	flux = other.flux;
}

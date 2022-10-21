#pragma once
#include <vector>

#include "photon.h"
#include "arealight.h"
#include "sphere.h"

class PhotonMap
{
public:
	PhotonMap();
	PhotonMap(std::vector<Object>& objects, std::vector<AreaLight>& lights, std::vector<Surface*>& spheres, int max_photons);
	
	
	std::vector<Photon> photons;	//Byte mot k-d tree
private:
};


#include "photonmap.h"
#include <iostream>

PhotonMap::PhotonMap()
{
}

PhotonMap::PhotonMap(std::vector<Object>& objects, std::vector<AreaLight>& lights, std::vector<Surface*>& spheres, int max_photons)
{

	if (lights.size() == 0 || spheres.size() == 0) return;
	
	int photons_per_light = max_photons / lights.size();

	for (AreaLight& light : lights) {
		int photons_per_sphere = photons_per_light / spheres.size();
		
		for (Surface* sphere : spheres) {

			std::cout << sphere->getType() << std::endl;
			if (sphere->getType() == Surface::Type::Sphere)
			{
				Sphere* s = dynamic_cast<Sphere*>(sphere);
				std::vector<Photon> photons_from_light = light.GeneratePhotons(objects, s, photons_per_sphere);
				s = nullptr;
				
				photons.insert(photons.end(), photons_from_light.begin(), photons_from_light.end());
			}
		}
	}
}
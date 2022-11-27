#include "photonmap.h"
#include <iostream>


PhotonMap::PhotonMap():root(nullptr){}

PhotonMap::PhotonMap(std::vector<Object>& objects, std::vector<AreaLight>& lights, std::vector<Surface*>& spheres, int max_photons)
{
	root = nullptr;
	if (lights.size() == 0 || spheres.size() == 0) return;
	
	std::vector<Photon> photons;
	
	int photons_per_light = max_photons / (int)lights.size();

	// Generate Photons
	for (AreaLight& light : lights) {
		int photons_per_sphere = photons_per_light / (int)spheres.size();
		
		for (Surface* sphere : spheres) {

			//std::cout << sphere->getType() << std::endl;
			if (sphere->getType() == Surface::Type::Sphere)
			{
				Sphere* s = dynamic_cast<Sphere*>(sphere);
				std::vector<Photon> photons_from_light = light.GeneratePhotons(objects, s, photons_per_sphere);
				s = nullptr;
				
				photons.insert(photons.end(), photons_from_light.begin(), photons_from_light.end());
			}
		}
	}	
	//Build KDtree
	root = generateKDTree(photons,0);
}

PhotonMap::~PhotonMap() {
	delete root;
}


std::vector<Photon> PhotonMap::getPhotons(Vec3 position, double length)
{
	std::vector<Photon> result;
	root->getPhotons(result, position, length);
	return result;
}



PhotonMap::Node* PhotonMap::generateKDTree(std::vector<Photon>& photons,int depth)
{
	//Base case
	if (photons.size() == 0) 
		return nullptr;
	else if (photons.size() == 1) 
		return new Node(photons[0], depth);

	//Find median
	auto median_itr = photons.begin() + photons.size() / 2;
	if (depth % 3 == 0) { // Split in x 
		std::nth_element(photons.begin(), median_itr, photons.end(), [](const Photon& a, const Photon& b) { return a.getPosition().x < b.getPosition().x; });
	}
	else if (depth % 3 == 1) { // Split in y 
		std::nth_element(photons.begin(), median_itr, photons.end(), [](const Photon& a, const Photon& b) { return a.getPosition().y < b.getPosition().y; });
	}
	else if (depth % 3 == 2) { // Split in z 
		std::nth_element(photons.begin(), median_itr, photons.end(), [](const Photon& a, const Photon& b) { return a.getPosition().z < b.getPosition().z; });
	}
	Photon median_photon = *median_itr;

	//Split into left and right
	std::vector<Photon> left(photons.begin(),median_itr);
	std::vector<Photon> right(median_itr+1, photons.end());

	//Create node
	Node* leftNode = generateKDTree(left,depth + 1);
	Node* rightNode = generateKDTree(right,depth + 1);
	return new Node(median_photon, depth,leftNode,rightNode);

}

void PhotonMap::Node::getPhotons(std::vector<Photon>& photons, const Vec3& pos, const double& lngt) const {
	if (this == nullptr) return;

	// Call the function for the children nodes if they are in the range and exists 
	int dimention = depth % 3;// 0 = x, 1 = y, 2 = z;
	if (pos[dimention] + lngt < photon.getPosition()[dimention])
		left->getPhotons(photons, pos, lngt);
	else if (pos[dimention] - lngt > photon.getPosition()[dimention])
		right->getPhotons(photons, pos, lngt);
	else {
		left->getPhotons(photons, pos, lngt);
		right->getPhotons(photons, pos, lngt);

		// check if the current node in range
		if (std::abs(photon.getPosition()[(dimention + 1) % 3] - pos[(dimention + 1) % 3]) < lngt &&
			std::abs(photon.getPosition()[(dimention + 2) % 3] - pos[(dimention + 2) % 3]) < lngt) {
			photons.push_back(photon);
		}
	}
}


PhotonMap::Node::Node(Photon& p,int d) : photon(p), depth(d) {
	left = nullptr;
	right = nullptr;
}

PhotonMap::Node::Node(Photon& p, int d, Node* l, Node* r) 
	:photon(p),depth(d),left(l),right(r){}

PhotonMap::Node::~Node()
{
	delete left;
	delete right;
}


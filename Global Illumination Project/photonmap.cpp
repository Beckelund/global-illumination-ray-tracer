#include "photonmap.h"
#include <iostream>


PhotonMap::PhotonMap()
{
}

PhotonMap::PhotonMap(std::vector<Object>& objects, std::vector<AreaLight>& lights, std::vector<Surface*>& spheres, int max_photons)
{
	if (lights.size() == 0 || spheres.size() == 0) return;
	
	std::vector<Photon> photons;
	
	int photons_per_light = max_photons / (int)lights.size();

	// Generate Photons
	for (AreaLight& light : lights) {
		int photons_per_sphere = photons_per_light / (int)spheres.size();
		
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
	
	//Build KDtree
	tree.BuildTree(photons);
}

std::vector<Photon> PhotonMap::getPhotons(Vec3 position, double length)
{
	std::vector<Photon> result = tree.getPhotons(position, length);
	return result;
}

KDTree::KDTree()
{
	root = nullptr;
}

KDTree::KDTree(std::vector<Photon>& photons) : KDTree()
{
	BuildTree(photons);
}

KDTree::~KDTree()
{
	delete root;
}

/*
bool CompareX(const Photon& lhs, const Photon& rhs)
{
	return lhs.getPosition().x < rhs.getPosition().x;
}

bool CompareY(const Photon& lhs, const Photon  rhs)
{
	return lhs.getPosition().y < rhs.getPosition().y;
}

bool CompareZ(const Photon& lhs, const Photon  rhs)
{
	return lhs.getPosition().z < rhs.getPosition().z;
}
*/

void KDTree::BuildTree(std::vector<Photon>& photons)
{
	if (photons.size() == 0) return;

	//Choose comparison function
	

	//Find median
	int median_index = (int)photons.size() / 2;
	std::nth_element(photons.begin(), photons.begin() + median_index, photons.end(), [](const Photon& a, const Photon& b) { return a.getPosition().x < b.getPosition().x; });
	Photon median = photons[median_index];

	//Split into left and right
	std::vector<Photon> left;
	std::vector<Photon> right;
	for (int i = 0; i < photons.size(); i++) {
		if (i == median_index) continue;
		if (photons[i].getPosition().x < median.getPosition().x) {
			left.push_back(photons[i]);
		}
		else {
			right.push_back(photons[i]);
		}
	}

	//Create node
	root = new Node(median);
	root->left = new KDTree(left);
	root->right = new KDTree(right);
}

std::vector<Photon>& KDTree::getPhotons(Vec3& position, double& length)
{
	std::vector<Photon> result;
	if (root == nullptr) return result;

	if (root->photon.getPosition().x > position.x - length && root->photon.getPosition().x < position.x + length) {
		result.push_back(root->photon);
	}
	
	if (root->left != nullptr && root->photon.getPosition().x > position.x - length) {
		std::vector<Photon> left_photons = root->left->getPhotons(position, length);
		result.insert(result.end(), left_photons.begin(), left_photons.end());
	}
	
	if (root->right != nullptr && root->photon.getPosition().x < position.x + length) {
		std::vector<Photon> right = root->right->getPhotons(position, length);
		result.insert(result.end(), right.begin(), right.end());
	}
	
	return result;
}

/*
KDTree::Node::Node(Photon p) : photon(p)
{
	left = nullptr;
	right = nullptr;
}
*/

KDTree::Node::Node(Photon& p, KDTree::Axis a) : photon(p), median_axis(a)
{
	left = nullptr;
	right = nullptr;
}

KDTree::Node::~Node()
{
	delete left;
	delete right;
}


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
	~PhotonMap();
	std::vector<Photon> getPhotons(Vec3 position, double length); //TODO consider using references for return, pos, and length
	
private:
	
	struct Node {
		Node() = delete;
		Node(Photon& p, int d);
		Node(Photon& p, int d, Node* l, Node* r);
		void getPhotons(std::vector<Photon>& photons, const Vec3& pos, const double& lngt) const;
		~Node();

		Photon photon;
		Node* left;
		Node* right;
		int depth;
	};

	Node* root;
	Node* generateKDTree(std::vector<Photon>& photons,int depth);
	//void getPhotonsKDTree(std::vector<Photon>&, Vec3 pos, double lngt);
};
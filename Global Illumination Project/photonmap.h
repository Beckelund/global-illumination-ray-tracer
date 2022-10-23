#pragma once
#include <vector>

#include "photon.h"
#include "arealight.h"
#include "sphere.h"


class KDTree
{
private:
	enum Axis { X, Y, Z };
public:
	KDTree();
	KDTree(std::vector<Photon>& photons);
	~KDTree();

	void BuildTree(std::vector<Photon>& photons);

	std::vector<Photon>& getPhotons(Vec3& position, double& length);	//TODO consider using references for return, pos, and length

	//Comparisons
	/*
	friend bool CompareX(const Photon& lhs, const Photon& rhs);
	friend bool CompareY(const Photon& lhs, const Photon& rhs);
	friend bool CompareZ(const Photon& lhs, const Photon& rhs);
	*/

private:
	struct Node
	{

		Node() = delete;
		//Node(Photon p);
		Node(Photon& p, KDTree::Axis a = KDTree::Axis::X);
		~Node();

		KDTree::Axis median_axis = KDTree::Axis::X;
		Photon photon;
		KDTree* left;
		KDTree* right;
	};

	Node* root;
};

class PhotonMap
{
public:
	PhotonMap();
	PhotonMap(std::vector<Object>& objects, std::vector<AreaLight>& lights, std::vector<Surface*>& spheres, int max_photons);
	std::vector<Photon> getPhotons(Vec3 position, double length); //TODO consider using references for return, pos, and length

	
private:
	KDTree tree;
};
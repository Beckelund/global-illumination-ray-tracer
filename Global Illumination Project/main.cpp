#include <iostream>
#include "vec3.h"
#include "image.h"
#include "object.h"
#include "material.h"
#include "arealight.h"

Object CreateRoom();

int main()
{
	//Create image 
	int ImageWidth = 600;
	int ImageHeight = 600; 
	
	Image im(ImageWidth, ImageHeight);

	
	std::vector<Object> objList; 
	objList.push_back(CreateRoom());

	//Create Plane
	ColorDBL redcol(0.9, 0.1, 0.1);
	std::vector<Polygon::Vertex> Plane1vert;
	Plane1vert.push_back(Polygon::Vertex(Vec3(10, -4, -5), redcol));//4
	Plane1vert.push_back(Polygon::Vertex(Vec3(10, -4, 5), redcol));//5
	Plane1vert.push_back(Polygon::Vertex(Vec3(0, -4, -5), redcol));//10
	Plane1vert.push_back(Polygon::Vertex(Vec3(0, -4, 5), redcol));//11
	std::vector<int> PlaneInd = {
		0,1,3,2,0
	};

	Object Plane1(Plane1vert, PlaneInd, redcol);
	
	

	//objList.push_back(Plane1);

	//Create Sphere
	Material Sphere1Material(Material::mirror,ColorDBL(1.0, 1.0, 0.0));
	Sphere Sphere1(Vec3(7.0, -3, -2), 4.5, Sphere1Material);
	Sphere Sphere2(Vec3(7.0, 4, -1), 2.5, Sphere1Material);
	Object MiddleSphere;
	MiddleSphere.AddSphere(Sphere1);
	MiddleSphere.AddSphere(Sphere2);
	objList.push_back(MiddleSphere);

	//Create material
	Material m(Material::Type::mirror,ColorDBL(1.0,1.0,1.0));

	// Create object from file 
	Object objectFromFile("Models/monkey.obj");
	objectFromFile.SetMaterial(m);
	//objList.push_back(objectFromFile);


	//Area Lights
	std::vector<AreaLight> lightsList;
	AreaLight light1(Vec3(1, -1, 4.5), Vec3(1, 0, 0), Vec3(0, 1, 0), ColorDBL(1.0, 0.2, 0.2), 200.0);
	AreaLight light2(Vec3(1,5.5,0), Vec3(1, 0, 0), Vec3(0, 0, 1), ColorDBL(0.2, 1.0, 0.2), 200.0);
	lightsList.push_back(light1);
	lightsList.push_back(light2);

	//Create rays from camera
	Vec3 eye = Vec3(-0.5, 0, 0);

	Vec3 c1 = Vec3(0, -1, -1);
	Vec3 c2 = Vec3(0, 1, -1);
	Vec3 c3 = Vec3(0, 1, 1);
	Vec3 c4 = Vec3(0, -1, 1);

	double cPlaneWidth = c3.y - c4.y;
	double cPlaneHeight = c4.z - c1.z;

	double deltaWidth = cPlaneWidth / (double)ImageWidth;
	double deltaHeight = cPlaneHeight / (double)ImageHeight;
	

	for (int i = 0; i < ImageWidth; i++) {
		std::cout << "Calculating :" << (i*100)/ImageWidth << "%";
		for (int j = 0; j < ImageHeight; j++) {
			double y = i * deltaWidth + c1.y + deltaWidth / 2;
			double z = j * deltaHeight + c1.z + deltaHeight / 2;

			Vec3 pixelPos = Vec3(c1.x, y, z);
			Vec3 direction = (pixelPos-eye).normalize();
			Ray* r = new Ray(eye, direction);

			ColorDBL result = r->castRay(objList, lightsList);
			ColorDBL finalColor = ColorDBL(1, 0, 1);
			
			delete r;
			im.SetPixelColor(result, i, j);
		}
		std::cout << "\33[2K\r"; // Clear the line 
	}

	/*
	im.MapColor(Image::linear);
	im.ExportBPM("Images/MapLin2k.bmp");
	*/
	/*
	im.MapColor(Image::logarithmic);
	im.ExportBPM("Images/MapLog2k.bmp");
	*/
	im.MapColor(Image::squareRoot);
	im.ExportBPM("Images/MapNoScaleSqr200.bmp");

	std::cout << "Success! " << std::endl;

	std::cout << "testing random:" << std::endl;
	int randomnum = std::rand();
	std::cout << randomnum << std::endl;

	return 0;
}

Object CreateRoom()
{
	std::vector<Polygon::Vertex> roomVert;
	ColorDBL rcol(0.9, 0.9, 0.9);
	ColorDBL roomCol(0.1, 0.9, 0.9);
	ColorDBL redcol(0.9, 0.1, 0.1);
	roomVert.push_back(Polygon::Vertex(Vec3(10, 6, -5), rcol));//0
	roomVert.push_back(Polygon::Vertex(Vec3(13, 0, -5), rcol));//1
	roomVert.push_back(Polygon::Vertex(Vec3(13, 0, 5), rcol));//2
	roomVert.push_back(Polygon::Vertex(Vec3(10, 6, 5), rcol));//3
	roomVert.push_back(Polygon::Vertex(Vec3(10, -6, -5), redcol));//4
	roomVert.push_back(Polygon::Vertex(Vec3(10, -6, 5), redcol));//5
	roomVert.push_back(Polygon::Vertex(Vec3(0, 6, -5), rcol));//6 
	roomVert.push_back(Polygon::Vertex(Vec3(-3, 0, -5), rcol));//7
	roomVert.push_back(Polygon::Vertex(Vec3(-3, 0, 5), rcol));//8
	roomVert.push_back(Polygon::Vertex(Vec3(0, 6, 5), rcol));//9
	roomVert.push_back(Polygon::Vertex(Vec3(0, -6, -5), redcol));//10
	roomVert.push_back(Polygon::Vertex(Vec3(0, -6, 5), redcol));//11
	std::vector<int> roomInd = {
		0,3,2,1,0
		,1,2,5,4,1
		,7,8,9,6,7
		,10,11,8,7,10
		,6,9,3,0,6
		,4,5,11,10,4
		,2,3,9,8,11,5,2
		,1,4,10,7,6,0,1
	};
	Object Room(roomVert, roomInd, roomCol);

	return Room;
}



/*
			r1.castRay(objList)
			{
				...
					if (hitobj->material != lamb || r1.inportance < (rand(0, 1)))
						Ray r2 = hitobj->material.BRDF(Vec3 n, r1); {
					r1->next = r2;
						}
				r2.castRay()
					color = hitobj->material.color;


			}*/






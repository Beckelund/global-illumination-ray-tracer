#include <iostream>
#include "vec3.h"
#include "image.h"
#include "object.h"
#include "material.h"

int main()
{
	//Create image 
	int ImageWidth = 600;
	int ImageHeight = 600; 
	
	Image im(ImageWidth, ImageHeight);

	

	// Create object from file 
	//Object objectFromFile("Models/monkey.obj");


	//Create Triangle object
	/*
	std::vector<Polygon::Vertex> poly;
	ColorDBL polyCol1(1, 0, 0);
	ColorDBL polyCol2(0, 1, 0);
	ColorDBL polyCol3(0, 0, 1);
	ColorDBL polyCol4(1, 0, 1);
	ColorDBL polyCol5(1, 1, 0);
	poly.push_back(Polygon::Vertex(Vec3(3, -0.5, -0.5), polyCol1));
	poly.push_back(Polygon::Vertex(Vec3(3, 1.5, -0.5), polyCol2));
	poly.push_back(Polygon::Vertex(Vec3(3, 1.2, 1.2), polyCol3));
	poly.push_back(Polygon::Vertex(Vec3(3, -0.5, 1.5), polyCol4));
	poly.push_back(Polygon::Vertex(Vec3(3, -1.0, 0.75), polyCol5));
	std::vector<int> polyInd = { 0,1,2,0,0,2,3,0,0,3,4,0};
	Object triangle(poly, polyInd);
	*/

	// Create room object 
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

	std::vector<Object> objList; 
	objList.push_back(Room);
	//objList.push_back(objectFromFile);

	//Create Sphere
	Material Sphere1Material(ColorDBL(1.0, 1.0, 0.0));
	Sphere Sphere1(Vec3(10.0, 0.0, 0.0), 2.5, Sphere1Material);
	Object MiddleSphere;
	MiddleSphere.AddSphere(Sphere1);
	objList.push_back(MiddleSphere);

	//Create material
	Material m(Material::Type::mirror,ColorDBL(1.0,1.0,1.0));

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

			ColorDBL result = r->castRay(objList);
			ColorDBL finalColor = ColorDBL(1, 0, 1);
			
			
			im.SetPixelColor(result, i, j);
		}
		std::cout << "\33[2K\r"; // Clear the line 
	}

	im.ExportBPM("Images/MonkeyTest4.bmp");

	std::cout << "Success! " << std::endl;

	return 0;
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






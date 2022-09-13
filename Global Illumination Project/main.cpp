#include <iostream>
#include "vec3.h"
#include "image.h"
#include "object.h"

int main()
{
	//Create image 
	int ImageWidth = 600;
	int ImageHeight = 600; 
	
	Image im(ImageWidth, ImageHeight);

	//Create rays from camera
	Vec3 eye = Vec3(-1, 0, 0);

	Vec3 c1 = Vec3(0, -1, -1);
	Vec3 c2 = Vec3(0, 1, -1);
	Vec3 c3 = Vec3(0, 1, 1);
	Vec3 c4 = Vec3(0, -1, 1);

	double cPlaneWidth = c3.y - c4.y;
	double cPlaneHeight = c4.z - c1.z;

	double deltaWidth = cPlaneWidth / (double)ImageWidth;
	double deltaHeight = cPlaneHeight / (double)ImageHeight;


	//Create Triangle object
	ColorDBL polyCol1(1, 0, 0);
	ColorDBL polyCol2(0, 1, 0);
	ColorDBL polyCol3(0, 0, 1);
	ColorDBL polyCol4(1, 0, 1);
	ColorDBL polyCol5(1, 1, 0);
	std::vector<Polygon::Vertex> poly;
	poly.push_back(Polygon::Vertex(Vec3(3, -0.5, -0.5), polyCol1));
	poly.push_back(Polygon::Vertex(Vec3(3, 1.5, -0.5), polyCol2));
	poly.push_back(Polygon::Vertex(Vec3(3, 1.2, 1.2), polyCol3));
	poly.push_back(Polygon::Vertex(Vec3(3, -0.5, 1.5), polyCol4));
	poly.push_back(Polygon::Vertex(Vec3(3, -1.0, 0.75), polyCol5));
	std::vector<int> polyInd = { 0,1,2,0,0,2,3,0,0,3,4,0};
	Object triangle(poly, polyInd);


	for (int i = 0; i < ImageWidth; i++) {
		for (int j = 0; j < ImageHeight; j++) {
			double y = i * deltaWidth + c1.y + deltaWidth / 2;
			double z = j * deltaHeight + c1.z + deltaHeight / 2;

			Vec3 pixelPos = Vec3(c1.x, y, z);
			Vec3 direction = (pixelPos-eye).normalize();
			Ray r(eye, direction);
			triangle.Intersection(r);
			im.SetPixelColor(r.getColor(), i, j);
			//im.SetPixelColor(ColorDBL(0, direction.y, direction.z), i, j);
		}
	}

	im.ExportBPM("Images/PolygonTest2.bmp");

	std::cout << "Success! " << std::endl;

	return 0;
}
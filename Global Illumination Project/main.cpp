#include <iostream>
#include "vec3.h"
#include "image.h"

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

	for (int i = 0; i < ImageWidth; i++) {
		for (int j = 0; j < ImageHeight; j++) {
			double y = i * deltaWidth + c1.y + deltaWidth / 2;
			double z = j * deltaHeight + c1.z + deltaHeight / 2;

			Vec3 pixelPos = Vec3(c1.x, y, z);

			Vec3 direction = (pixelPos-eye).normalize();
			im.SetPixelColor(ColorDBL(0, direction.y, direction.z), i, j);
		}
	}

	im.ExportBPM("Images/testImage3.bmp");

	std::cout << "Success! " << std::endl;

	return 0;
}
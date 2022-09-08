#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "colordbl.h"

class Image
{
public:
	enum colorMapping {linear,logarithmic, squareRoot};

	Image(int width, int height);

	void SetPixelColor(const ColorDBL& c, int x, int y);
	ColorDBL GetPixelColor(int x, int y) const;
	void MapColor(colorMapping clmp);
	void ExportBPM(const char* filePath) const;


private:
	int imageWidth;
	int imageHeight;
	std::vector<ColorDBL> imagePixles;


};


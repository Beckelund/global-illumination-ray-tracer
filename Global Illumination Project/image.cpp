#include "image.h"

Image::Image(int width, int height) : imageWidth(width), imageHeight(height), imagePixles(std::vector<ColorDBL>(width* height)) {}

void Image::SetPixelColor(const ColorDBL& c, int x, int y){
	if (x >= imageWidth || y >= imageHeight)
		return; // outside vector
	imagePixles[imageWidth * y + x] = c;
}

ColorDBL Image::GetPixelColor(int x, int y) const {
	if (x >= imageWidth || y >= imageHeight)
		return imagePixles[0]; // outside vector
	return imagePixles[imageWidth * y + x];
}

void Image::MapColor(colorMapping clmp) {
	switch (clmp)
	{
	case Image::linear:
		break;
	case Image::logarithmic:
		//TODO implement
		break;
	case Image::squareRoot:
		//TODO implement
		break;
	default:
		break;
	}
}

void Image::ExportBPM(const char* filePath) const{
	std::ofstream f;
	f.open(filePath, std::ios::out | std::ios::binary);
	if (!f.is_open()) {
		std::cout << "File could not open \n";
	}

	unsigned char bmpPad[3]{ 0,0,0 };
	const int paddingAmount = ((4 - (imageWidth * 3) % 4) % 4);

	const int fileHeaderSize = 14;
	const int informationHederSize = 40;
	const int fileSize = fileHeaderSize + informationHederSize + imageWidth * imageHeight * 3 + paddingAmount * imageHeight;

	unsigned char fileHeader[fileHeaderSize];

	//File type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';
	// File size 
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;
	// not used
	fileHeader[6] = 0;
	fileHeader[7] = 0;
	//not used 
	fileHeader[8] = 0;
	fileHeader[9] = 0;
	// pixle data offset 
	fileHeader[10] = fileHeaderSize + informationHederSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	unsigned char informationHeader[informationHederSize];

	informationHeader[0] = informationHederSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;

	informationHeader[4] = imageWidth;
	informationHeader[5] = imageWidth >> 8;
	informationHeader[6] = imageWidth >> 16;
	informationHeader[7] = imageWidth >> 24;

	informationHeader[8] = imageHeight;
	informationHeader[9] = imageHeight >> 8;
	informationHeader[10] = imageHeight >> 16;
	informationHeader[11] = imageHeight >> 24;

	informationHeader[12] = 1;
	informationHeader[13] = 0;
	//Bits per pixle(RGB)
	informationHeader[14] = 24;
	informationHeader[15] = 0;

	informationHeader[16] = 0;
	informationHeader[17] = 0;
	informationHeader[18] = 0;
	informationHeader[19] = 0;

	informationHeader[20] = 0;
	informationHeader[21] = 0;
	informationHeader[22] = 0;
	informationHeader[23] = 0;

	informationHeader[24] = 0;
	informationHeader[25] = 0;
	informationHeader[26] = 0;
	informationHeader[27] = 0;

	informationHeader[28] = 0;
	informationHeader[29] = 0;
	informationHeader[30] = 0;
	informationHeader[31] = 0;

	informationHeader[32] = 0;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;

	informationHeader[36] = 0;
	informationHeader[37] = 0;
	informationHeader[38] = 0;
	informationHeader[39] = 0;

	f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
	f.write(reinterpret_cast<char*>(informationHeader), informationHederSize);

	unsigned char r, g, b;
	ColorDBL pixleColor;

	for (int y = 0; y < imageHeight; y++) {
		for (int x = 0; x < imageWidth; x++) {
			pixleColor = this->GetPixelColor(x, y);
			// Can be a problem when static casting double to char
			r = static_cast<unsigned char>(std::min(std::max(pixleColor.getR(), 0.0), 1.0) * 255.0);
			g = static_cast<unsigned char>(std::min(std::max(pixleColor.getG(), 0.0), 1.0) * 255.0);
			b = static_cast<unsigned char>(std::min(std::max(pixleColor.getB(), 0.0), 1.0) * 255.0);

			unsigned char color[] = { b,g,r };
			f.write(reinterpret_cast<char*>(color), 3);
		}
		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
	}
	f.close();

}

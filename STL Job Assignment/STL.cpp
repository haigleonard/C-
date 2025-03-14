
#include "pch.h"
#include "image.hpp"
#include <iostream>
#include <algorithm>

// post: the pixels of the image variable are equal to the input rgb value
void fill(image &image, const rgb &rgb)
{
	generate(image.begin(), image.end(), [rgb]() {return struct rgb(rand() % rgb.r, rand() % rgb.g, rand() % rgb.b); });
	//fill(image.begin(), image.end(), rgb);
}
// post: the rows of the image variable are reversed
void mirror_x(image &image)
{
	const int width = image.width();
	const int height = image.height();
	for (int y = 0; y < height; y++) {
		std::reverse(image.begin() + y * width, image.begin() + y * width + width);
	}
}
// post: the columns of the image variable are reversed
void mirror_y(image &image) {
	const int width = image.width();
	const int height = image.height();
	for (int y = 0; y < floor(height/2); y++) {
		std::swap_ranges(image.begin() + y * width, image.begin() + y * width + width, image.begin() + height * (width - 1 - y));
		
	}
}
// post: the image variable contains a resampled version of the input with the specified width and height
void resample(image &image, const int width, const int height)
{
	// try and write as simple code as possible while maintaining image quality to some degree
	// remember that the image class has default versions of the copy constructor and assignment operator
	
	class image temp(image);
	image.~image();
	new(&image) class image(width,height);
	
	int i = 0;
	int j = 0;
	
	//Nearest Neighbour
	const double xratio = temp.width() / (double)width;
	const double yratio = temp.height() / (double)height;
	generate(image.begin(), image.end(), [&]() {
		double px = floor(j*xratio);
		double py = floor(i*yratio); 
		if (j>width-2) {j = 0; i++;}else {j++;}
		return rgb(temp(px, py).r, temp(px, py).g, temp(px, py).b);
	});
	
	//Bilinear Interpolation
	/*
	generate(image.begin(), image.end(), [&]() {
			float gx = ((float)j) / width * (temp.width() - 1);
			float gy = ((float)i) / height * (temp.height() - 1);
			int ux = (int)gx;
			int uy = (int)gy;
			rgb u1 = temp(ux, uy);
			rgb u2 = temp(ux + 1, uy);
			rgb u3 = temp(ux, uy + 1);
			rgb u4 = temp(ux + 1, uy + 1);
			if (j > width - 2) { j = 0; i++; }else { j++; }
			return rgb(
				(int)((u1.r + (u2.r - u1.r) * (gx - ux)) + ((u3.r + (u4.r - u3.r) * (gx - ux)) - (u1.r + (u2.r - u1.r) * (gx - ux))) * (gy - uy)),
				(int)((u1.g + (u2.g - u1.g) * (gx - ux)) + ((u3.g + (u4.r - u3.g) * (gx - ux)) - (u1.g + (u2.g - u1.g) * (gx - ux))) * (gy - uy)),
				(int)((u1.b + (u2.b - u1.b) * (gx - ux)) + ((u3.b + (u4.r - u3.b) * (gx - ux)) - (u1.b + (u2.b - u1.b) * (gx - ux))) * (gy - uy)));
	});
	*/
}

int main(int argc, char *argv[])
{
	static image image(8, 8);
	fill(image, rgb(256, 256, 256));

	static int newLine = 0;
	auto print = [](rgb n) { if (newLine >= image.width()) { std::cout << endl; newLine = 0; } std::cout << "R:" << n.r << " G:" << n.g << " B:" << n.b << "  \t"; newLine++; };

	puts("Initial Image:");
	for_each(image.begin(), image.end(), print);

	std::cout << std::endl << std::endl << "Mirror X:" << std::endl;
	mirror_x(image);
	for_each(image.begin(), image.end(), print);

	std::cout << endl << std::endl << "Mirror Y:" << std::endl;
	mirror_y(image);
	for_each(image.begin(), image.end(), print);

	resample(image, 6, 16);
	std::cout << std::endl << std::endl << "Mirror Resample Width: " << image.width() << " Height: " << image.height() << std::endl;
	for_each(image.begin(), image.end(), print);

	return 0;
}
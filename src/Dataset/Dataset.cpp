/*
 * Dataset.cpp
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#include <iostream>

#include "Dataset.h"

Dataset::Dataset() {
	// TODO Auto-generated constructor stub

	this->setup();
}

Dataset::~Dataset() {
	// TODO Auto-generated destructor stub
}

void Dataset::setup()
{
	vector_dataset_images ti;
	this->images = ti;

	this->number_of_images = 0;
}

//OPERATORS
DatasetImage& Dataset::operator[] (const int index)
{
	return this->images[index];
}

void Dataset::AddImage(const char *filename)
{
	DatasetImage dsi = DatasetImage(filename);
	this->images.push_back(dsi);

	this->number_of_images++;
}

pixel_value Dataset::getPixelValueAt(unsigned int x, unsigned int y, unsigned int z)
{
	return this->images[z][x][y];
}

unsigned int Dataset::getNumPixelsOnAxis(AXIS a)
{
	//check that there is at least 1 image
	if(this->number_of_images < 1)
	{
		std::cout << "ERROR: no images set!" << std::endl;
		exit(EXIT_FAILURE);
	}

	unsigned int number = 0;

	switch(a)
	{
		case X:
			number = this->images[0].getWidth();
			break;
		case Y:
			number = this->images[0].getHeight();
			break;
		case Z:
			number = this->number_of_images;
			break;
	}

	return number;
}

unsigned int Dataset::getMaxVal()
{
	unsigned int max = 0;

	for(vector_dataset_images::iterator it = this->images.begin(); it != this->images.end(); ++it) {
		if(it->getMaxVal() > max)
			max = it->getMaxVal();
	}

	return max;
}

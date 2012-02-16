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

	DatasetImage dsi;
	this->images.push_back(dsi);
}

//OPERATORS
DatasetImage& Dataset::operator[] (const int index)
{
	return this->images[index];
}

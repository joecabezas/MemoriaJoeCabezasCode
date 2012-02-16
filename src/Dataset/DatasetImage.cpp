/*
 * DatasetImage.cpp
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#include "DatasetImage.h"

DatasetImage::DatasetImage() {
	// TODO Auto-generated constructor stub
	this->setup();
}

DatasetImage::~DatasetImage() {
	// TODO Auto-generated destructor stub
}

void DatasetImage::setup()
{
	matrix_int tm;
	this->points = tm;

	vector_int v1;
	this->points.push_back(v1);

	this->points[0].push_back(11);
}

//OPERATORS
vector_int& DatasetImage::operator[] (const int index)
{
	return this->points[index];
}

/*
 * DatasetImage.cpp
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#include "DatasetImage.h"

DatasetImage::DatasetImage(const char *filename)
{
	this->filename = filename;
	this->setup();
}

DatasetImage::~DatasetImage()
{
}

void DatasetImage::setup()
{
	//create file pointer
	this->file = new std::ifstream();

	//open file
	//this->file->open(filename);

	matrix_pixel tm;
	this->points = tm;

	vector_pixel v1;
	this->points.push_back(v1);

	this->points[0].push_back(11);
}

//OPERATORS
vector_pixel& DatasetImage::operator[] (const int index)
{
	return this->points[index];
}

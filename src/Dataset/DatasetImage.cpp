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
	//setup matrix of pixels
	matrix_pixel mp;
	this->points = mp;

	//create file pointer and open file
	this->file = new std::ifstream();
	this->file->open(this->filename, std::fstream::in | std::fstream::binary);

	if(this->file->is_open())
	{
		std::string s;

		//ignore header type
		*(this->file) >> s;

		//read width
		*(this->file) >> s;
		this->width = std::atoi(s.c_str());
		//std::cout << this->width << std::endl;

		//read height
		*(this->file) >> s;
		this->height = std::atoi(s.c_str());
		//std::cout << this->height << std::endl;

		//read max value
		*(this->file) >> s;
		this->maxval = std::atoi(s.c_str());
		//std::cout << this->maxval << std::endl;

		//check if file is 16bit per pixel
		this->is_16_bit = false;

		if(this->maxval == 0xffff)
		{
			std::cout << "is a 16bit file" << std::endl;
			this->is_16_bit = true;
		}

		if(this->maxval == 0xff)
			std::cout << "is a 8bit file" << std::endl;

		//ignore next separator (0x0A)
		this->file->get();

		unsigned int pixel_value;
		unsigned int counter = 0;
		while (this->file->good())
		{
			pixel_value = this->file->get();

			//TODO: check endianness

			//concatenate with next byte
			//if this is a 16bit file per pixel
			if(this->is_16_bit)
				pixel_value = pixel_value | (this->file->get() << 8);

			//check if we need to create a new row of pixels (vector_pixel)
			if(counter % this->width == 0)
			{
				vector_pixel vector_pixel;
				this->points.push_back(vector_pixel);
			}
			//std::cout << pixel_value << ',';

			int index = counter / this->width;

			this->points[index].push_back(pixel_value);

			counter++;
		}
	}

	this->file->close();
}

//OPERATORS
vector_pixel& DatasetImage::operator[] (const int index)
{
	return this->points[index];
}

std::size_t DatasetImage::getWidth()
{
	return this->width;
}

std::size_t DatasetImage::getHeight()
{
	return this->height;
}

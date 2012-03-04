/*
 * DatasetImage.h
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#ifndef DATASETIMAGE_H_
#define DATASETIMAGE_H_

#include <vector>

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

typedef int pixel_value;
typedef std::vector<pixel_value> vector_pixel;
typedef std::vector< vector_pixel > matrix_pixel;

class DatasetImage
{
	public:

		DatasetImage(const char *filename);
		virtual ~DatasetImage();

		void setup();

		vector_pixel& operator[](const int);

		std::size_t getWidth();
		std::size_t getHeight();

	private:

		//PGM data
		std::size_t width;
		std::size_t height;
		std::size_t maxval;

		matrix_pixel points;

		const char *filename;
		std::ifstream* file;
};

#endif /* DATASETIMAGE_H_ */

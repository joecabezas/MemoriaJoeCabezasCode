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
#include <fstream>

typedef int pixel;
typedef std::vector<pixel> vector_pixel;
typedef std::vector< vector_pixel > matrix_pixel;

class DatasetImage
{
	public:

		DatasetImage(const char *filename);
		virtual ~DatasetImage();

		void setup();

		vector_pixel& operator[](const int);

	private:

		matrix_pixel points;

		std::string filename;
		std::ifstream* file;
};

#endif /* DATASETIMAGE_H_ */

/*
 * DatasetImage.h
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#ifndef DATASETIMAGE_H_
#define DATASETIMAGE_H_

#include <vector>

typedef std::vector<int> vector_int;
typedef std::vector< vector_int > matrix_int;

class DatasetImage
{
	public:

		DatasetImage();
		virtual ~DatasetImage();

		void setup();

		vector_int& operator[](const int);

	private:

		matrix_int points;
};

#endif /* DATASETIMAGE_H_ */

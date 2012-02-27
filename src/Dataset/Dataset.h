/*
 * Dataset.h
 *
 *  Created on: 15/02/2012
 *      Author: joe
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <vector>

#include "DatasetImage.h"

typedef std::vector<DatasetImage> vector_dataset_images;

class Dataset
{
	public:

		Dataset();
		virtual ~Dataset();

		DatasetImage& operator[](const int);

		void AddImage(const char *);

	private:

		void setup();

		vector_dataset_images images;
		int test;
};

#endif /* DATASET_H_ */

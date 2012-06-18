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

		pixel_value getPixelValueAt(unsigned int, unsigned int, unsigned int);

		//AXIS NAMES
		enum AXIS {X,Y,Z};

		unsigned int getNumPixelsOnAxis(AXIS);

		unsigned int getMaxVal();

	private:
		void setup();

		vector_dataset_images images;
		std::size_t number_of_images;
};

#endif /* DATASET_H_ */

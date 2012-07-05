/*
 * MarchingCubesThread.h
 *
 *  Created on: Jun 24, 2012
 *      Author: joe
 */

#ifndef MARCHINGCUBESTHREAD_H_
#define MARCHINGCUBESTHREAD_H_

#include <SFML/Window.hpp>
#include <vector>

#include "../mc/MarchingCubes.h"
#include "../filehandlers/OffFile.h"

class MarchingCubesThread : public sf::Thread
{
	public:
		MarchingCubesThread();
		virtual ~MarchingCubesThread();

		void readFilesFromStandardInput(int argc, char **argv);
		void createOffFile();

		std::vector< GLfloat >* getTriangles(float minvalue);

	private:
		vector_triangles triangles;
		Dataset* dataset;
		std::vector< GLfloat > vertexes;

		unsigned int num_triangles;

		void setup();

		void generateTriangles(float minvalue);

		//overrides
		virtual void Run();
};

#endif /* MARCHINGCUBESTHREAD_H_ */

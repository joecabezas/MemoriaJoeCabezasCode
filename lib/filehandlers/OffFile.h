/*
 * OffFile.h
 *
 *  Created on: 07/02/2012
 *      Author: joe
 */

#ifndef OFFFILE_H_
#define OFFFILE_H_

#include <fstream>

#include "../mc/MarchingCubes.h"

class OffFile {
public:
	OffFile(TRIANGLE*, std::size_t);
	virtual ~OffFile();

	void createOff();

private:
	void setup();

	void createHeader();
	void createVertices();
	void createFaces();

	//members
	TRIANGLE* triangles;
	std::size_t num_triangles;
	std::size_t num_vertices;
	std::size_t num_faces;
	std::size_t num_edges;

	std::ofstream* file;
};

#endif /* OFFFILE_H_ */

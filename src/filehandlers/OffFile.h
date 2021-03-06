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
	OffFile(vector_triangles, std::size_t, std::string);
	virtual ~OffFile();

	void createOff();

private:
	void setup();

	void createHeader();
	void createVertices();
	void createFaces();

	//members
	vector_triangles triangles;
	std::size_t num_triangles;
	std::size_t num_vertices;
	std::size_t num_faces;
	std::size_t num_edges;

	std::string file_name;
	std::ofstream* file;
};

#endif /* OFFFILE_H_ */

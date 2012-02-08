/*
 * OffFile.cpp
 *
 *  Created on: 07/02/2012
 *      Author: joe
 */

#include "OffFile.h"

#define length(x) (sizeof(x)/sizeof(x[0]))

OffFile::OffFile(TRIANGLE* t, std::size_t num_triangles)
{
	this->triangles = t;
	this->num_triangles = num_triangles;

	this->setup();
}

void OffFile::setup()
{
	this->num_vertices =		this->num_triangles * 3;
	this->num_faces =		this->num_triangles;
	this->num_edges =		this->num_triangles * 3;

	//file stream
	this->file = new std::ofstream();
}

void OffFile::createOff()
{
	this->file->open("out.off");

	this->createHeader();
	this->createVertices();
	this->createFaces();

	this->file->close();
}

void OffFile::createHeader()
{
	*(this->file)
		<< "OFF"
		<< std::endl;

	*(this->file)
			<< std::endl;

	*(this->file)
		<< "#num_vertices num_faces num_edges"
		<< std::endl;

	*(this->file)
		<< this->num_vertices << " "
		<< this->num_faces << " "
		<< this->num_edges << " "
		<< std::endl;

	*(this->file)
		<< std::endl;
}

void OffFile::createVertices()
{
	*(this->file)
		<< "#vertices"
		<< std::endl;

	for (std::size_t i = 0; i < this->num_triangles; ++i)
	{
		//primer punto
		*(this->file)
				<< this->triangles[i].p[0].x << " "
				<< this->triangles[i].p[0].y << " "
				<< this->triangles[i].p[0].z << " "
				<< std::endl;

		//segundo punto
		*(this->file)
				<< this->triangles[i].p[1].x << " "
				<< this->triangles[i].p[1].y << " "
				<< this->triangles[i].p[1].z << " "
				<< std::endl;

		//tercer punto
		*(this->file)
				<< this->triangles[i].p[2].x << " "
				<< this->triangles[i].p[2].y << " "
				<< this->triangles[i].p[2].z << " "
				<< std::endl;
	}

	*(this->file)
			<< std::endl;
}

void OffFile::createFaces()
{
	*(this->file)
		<< "#faces"
		<< std::endl;

	for (std::size_t i = 0; i < this->num_triangles; ++i)
	{
		*(this->file)
			<< "3 "
			<< i*3+0 << " " << i*3+1 << " " << i*3+2 << std::endl;
	}
}

OffFile::~OffFile()
{
	delete this->triangles;
}


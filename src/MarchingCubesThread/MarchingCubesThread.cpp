/*
 * MarchingCubesThread.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: joe
 */

#include "MarchingCubesThread.h"

MarchingCubesThread::MarchingCubesThread()
{
	this->setup();
}

MarchingCubesThread::~MarchingCubesThread()
{
	// TODO Auto-generated destructor stub
}

void MarchingCubesThread::Run()
{
	while(true);
}

void MarchingCubesThread::setup()
{
	this->dataset = new Dataset();
}

void MarchingCubesThread::readFilesFromStandardInput(int argc, char **argv)
{
	//create a dataset holder
	Dataset d;

	for (int i = 1; i < argc; ++i)
	{
		//std::cout << "argv[" << i << "]" << argv[i] << std::endl;
		this->dataset->AddImage(argv[i]);
	}
}

std::vector< GLfloat >* MarchingCubesThread::getTriangles(float minvalue_scale)
{
	this->generateTriangles(minvalue_scale);

	//GLfloat array[3 * this->num_triangles];

	for(unsigned int i=0; i < this->num_triangles; i++)
	{
		for(int j=2; j >= 0; j--)
		{
//			array[i*9 + j*3 + 0] = (*this->triangles)[i].p[j].x;
//			array[i*9 + j*3 + 1] = (*this->triangles)[i].p[j].y;
//			array[i*9 + j*3 + 2] = (*this->triangles)[i].p[j].z;

//			std::cout << "("
//				<< this->triangles[i].p[j].x
//				<< ","
//				<< this->triangles[i].p[j].y
//				<< ","
//				<< this->triangles[i].p[j].z
//				<< ")"
//				<< std::endl;

			this->vertexes.push_back(this->triangles[i].p[j].x);
			this->vertexes.push_back(this->triangles[i].p[j].y);
			this->vertexes.push_back(this->triangles[i].p[j].z);

			this->vertexes.push_back(this->triangles[i].norm.x);
			this->vertexes.push_back(this->triangles[i].norm.y);
			this->vertexes.push_back(this->triangles[i].norm.z);
		}
	}

	return &(this->vertexes);
}

void MarchingCubesThread::generateTriangles(float minvalue_scale)
{
	this->vertexes.clear();
	this->triangles.clear();

	this->triangles = MarchingCubesDataset(this->dataset->getMaxVal() * minvalue_scale, *(this->dataset), LinearInterp, this->num_triangles);

	std::cout << "Number of Triangles = " << this->num_triangles << std::endl;
	std::cout << "this->dataset->getMaxVal() = " << this->dataset->getMaxVal() << std::endl;
	std::cout << "Minvalue_scale = " << minvalue_scale << std::endl;
	std::cout << "this->dataset->getMaxVal() * minvalue_scale = " << this->dataset->getMaxVal() * minvalue_scale << std::endl;

//	std::cout << this->triangles[0].p[0].x << std::endl;
//	std::cout << this->triangles[0].p[0].y << std::endl;
//	std::cout << this->triangles[0].p[0].z << std::endl;
}

void MarchingCubesThread::createOffFile()
{
	OffFile* f = new OffFile(this->triangles, this->num_triangles);
	f->createOff();
}

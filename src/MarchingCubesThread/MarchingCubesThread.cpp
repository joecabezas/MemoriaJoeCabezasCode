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
	this->generateTriangles();
}

void MarchingCubesThread::setup()
{
	this->dataset = new Dataset();
	this->vertexes.clear();
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

void MarchingCubesThread::generateTriangles()
{
	this->triangles.clear();
	this->triangles = MarchingCubesDataset(this->dataset->getMaxVal() * this->min_value_scale, *(this->dataset), LinearInterp, this->num_triangles);

	this->vertexes.clear();
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
}

void MarchingCubesThread::createOffFile(std::string file_name)
{
	OffFile* f = new OffFile(this->triangles, this->num_triangles, file_name);
	f->createOff();
}

std::vector< GLfloat >* MarchingCubesThread::getVertexPointer()
{
	return &this->vertexes;
}

void MarchingCubesThread::setMinValueScale(float min_value_scale)
{
	this->min_value_scale = min_value_scale;
}

//      main.cpp
//      
//      Copyright 2011 Joe Cabezas Campos <joe@archlinux-joe>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//

#include <math.h>

#include "../lib/mc/MarchingCubes.h"
#include "Dataset/Dataset.h"
#include "../lib/filehandlers/OffFile.h"
#include "Visualizer/Visualizer.h"

#define MINVAL 1
#define D 1

mpVector Promedio(mp4Vector p1, mp4Vector p2, float value);

int main(int argc, char **argv)
{
	//create the visualizer
	Visualizer v;

	return 0;

	//create a dataset holder
	Dataset d;

	for (int i = 1; i < argc; ++i)
	{
//		std::cout
//			<< "Reading <"
//			<< argv[i]
//			<< ">"
//			<< std::endl;

		d.AddImage(argv[i]);
	}

	int numTriangles;
	float minval = d.getMaxVal() * 0.2f;
	std::cout << "valor minimo: " << minval << std::endl;

	std::cout << "calculando Marching Cubes" << std::endl;
	vector_triangles Triangles = MarchingCubesDataset(minval, d, LinearInterp, numTriangles);

	//debug
	std::cout << "numero de triangulos: " << numTriangles << std::endl;

	OffFile* f = new OffFile(Triangles, numTriangles);
	f->createOff();

	return 0;
}

mpVector Promedio(mp4Vector p1, mp4Vector p2, float value)
{
	//debug
	/*
	std::cout << "Promedio" << std::endl;

	std::cout << "p1: (" << p1.x << "," << p1.y << "," << p1.z << "," << p1.val << ")" << std::endl;
	std::cout << "p2: (" << p2.x << "," << p2.y << "," << p2.z << "," << p2.val << ")" << std::endl;
	std::cout << "value: " << value << std::endl;
	
	std::cout << "interpolacion: " << ((mpVector)p1 + (mpVector)p2)/2 << std::endl;
	*/
	return ((mpVector)p1 + (mpVector)p2)/2;
}

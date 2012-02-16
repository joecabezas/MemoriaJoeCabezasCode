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

#define MINVAL 1
#define D 1

mpVector Promedio(mp4Vector p1, mp4Vector p2, float value);

int main(int argc, char **argv)
{
	TRIANGLE * Triangles;
	int numTriangles;
	
	int nX = 20;
	int nY = 20;
	int nZ = 20;

	int MINX = -10;
	int MAXX = 10;

	int MINY = -10;
	int MAXY = 10;

	int MINZ = -10;
	int MAXZ = 10;

	//mp4Vector* vertices;	//first free the previous allocated memory
	//delete [] vertices;	//first free the previous allocated memory
	mp4Vector* vertices;
	vertices = new mp4Vector[(nX+1)*(nY+1)*(nZ+1)];
	mpVector stepSize((MAXX-MINX)/nX, (MAXY-MINY)/nY, (MAXZ-MINZ)/nZ);
	for(int i=0; i < nX+1; i++)
		for(int j=0; j < nY+1; j++)
			for(int k=0; k < nZ+1; k++) {
				mp4Vector vert(MINX+i*stepSize.x, MINY+j*stepSize.y, MINZ+k*stepSize.z, 0);
				//vert.val = Potential((mpVector)vert);
				vert.val = ( vert.x*vert.x + vert.y*vert.y + vert.z*vert.z );
				vertices[i*(nY+1)*(nZ+1) + j*(nZ+1) + k] = vert;
	}

	//Triangles = MarchingCubes(
	//						/*int ncellsX*/ nX,
	//						/*int ncellsY*/ nY,
	//						/*int ncellsZ*/ nZ,
	//						/*float minValue*/ 50.0f,
	//						/*mp4Vector* */ vertices,
	//						/*INTERSECTION*/ LinearInterp,
	//						/*int & */ numTriangles
	//						);

	Triangles = MarchingCubesLinear(
							/*int ncellsY*/ nX,
							/*int ncellsY*/ nY,
							/*int ncellsZ*/ nZ,
							/*float minValue*/ 50.0f,
							/*mp4Vector* */ vertices,
							/*int & */ numTriangles
							);

	//debug
	std::cout << "numero de triangulos: " << numTriangles << std::endl;
	/*
	for(int i=0; i<numTriangles; i++){
		std::cout << "triangulo " << i << ":" << std::endl;
		for(int j=0; j<3; j++){
			std::cout << "vertice " << j << ": (" << Triangles[i].p[j].x << "," << Triangles[i].p[j].y << "," << Triangles[i].p[j].z << ")" << std::endl;
		}
	}
	*/
	
	OffFile* f = new OffFile(Triangles, numTriangles);
	f->createOff();

	Dataset d;

	//DatasetImage dsi = d[0];
	std::cout << d[0][0][0] << std::endl;

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

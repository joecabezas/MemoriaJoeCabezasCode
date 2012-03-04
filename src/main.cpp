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
	/*for (int i = 1; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}
	//return 0;
	 */

	std::cout << "version 3 marzo 1114" << std::endl;

	Dataset d;

	for (int i = 1; i < argc; ++i)
	{
		d.AddImage(argv[i]);
	}

	/*
	std::cout << d[0][0][0] << std::endl;
	std::cout << d[0][0][1] << std::endl;
	std::cout << d[0][0][2] << std::endl;
	std::cout << d[0][1][0] << std::endl;
	std::cout << d[0][1][1] << std::endl;
	std::cout << d[0][1][2] << std::endl;
	std::cout << d[0][2][0] << std::endl;
	std::cout << d[0][2][1] << std::endl;
	std::cout << d[0][2][2] << std::endl;
	*/

	/*
	std::cout << d[1][0][0] << std::endl;
	std::cout << d[1][0][1] << std::endl;
	std::cout << d[1][0][2] << std::endl;
	std::cout << d[1][1][0] << std::endl;
	std::cout << d[1][1][1] << std::endl;
	std::cout << d[1][1][2] << std::endl;
	std::cout << d[1][2][0] << std::endl;
	std::cout << d[1][2][1] << std::endl;
	std::cout << d[1][2][2] << std::endl;
	*/

	std::cout << d.getPixelValueAt(0,0,0) << std::endl;
	std::cout << d.getPixelValueAt(0,1,0) << std::endl;
	std::cout << d.getPixelValueAt(0,2,0) << std::endl;

	std::cout << d.getPixelValueAt(0,0,1) << std::endl;
	std::cout << d.getPixelValueAt(0,1,1) << std::endl;
	std::cout << d.getPixelValueAt(0,2,1) << std::endl;

	//return 0;

	TRIANGLE * Triangles;
	int numTriangles;
	
	float minval = 50.0f;

	int nX = 300;
	int nY = 300;
	int nZ = 300;

	int MINX = -300;
	int MAXX = 300;

	int MINY = -300;
	int MAXY = 300;

	int MINZ = -300;
	int MAXZ = 300;

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

	Triangles = MarchingCubes(
							/*int ncellsX*/ nX,
							/*int ncellsY*/ nY,
							/*int ncellsZ*/ nZ,
							/*float minValue*/ minval,
							/*mp4Vector* */ vertices,
							/*INTERSECTION*/ Promedio,
							/*int & */ numTriangles
						);

	//Triangles = MarchingCubesLinear(nX, nY, nZ, 50.0f, vertices, numTriangles);

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

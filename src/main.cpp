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

				std::cout << vert.val << std::endl;

				vertices[i*(nY+1)*(nZ+1) + j*(nZ+1) + k] = vert;
	}

	Triangles = MarchingCubes(
						/*int ncellsX*/ nX,
						/*int ncellsY*/ nY,
						/*int ncellsZ*/ nZ,
						/*float minValue*/ 50.0f,
						/*mp4Vector* */ vertices,
						/*INTERSECTION*/ Promedio,
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

	/*
	//escribiendo el OFF
	std::cout << "OFF" << std::endl;
	
	//OFF Header
	int vertices_debug = 8*8;
	int faces_debug = 6*8;
	int edges_debug = 12*8;
	
	int numero_vertices = numTriangles*3+vertices_debug;
	
	std::cout << numero_vertices << " " << numTriangles+faces_debug << " " << numTriangles*3+edges_debug << std::endl;
	
	//vertices
	for(int i=0; i<numTriangles; i++){
		for(int j=0; j<3; j++){
			std::cout << Triangles[i].p[j].x << " " << Triangles[i].p[j].y << " " << Triangles[i].p[j].z << std::endl;
		}
	}
	
	//vertices de debug (cajas contenedoras de los vertices, para poder visualizarlos)
	float delta = 0.1f;
	//por cada vertice
	for(int i=0; i<8; i++){
		//hay que hacer 8 vertices de un cubo contenedor
		//dejando al vertice actual dentro, en el centro
		std::cout << vertices[i].x - delta << " " << vertices[i].y - delta << " " << vertices[i].z - delta << std::endl;
		std::cout << vertices[i].x + delta << " " << vertices[i].y - delta << " " << vertices[i].z - delta << std::endl;
		std::cout << vertices[i].x + delta << " " << vertices[i].y + delta << " " << vertices[i].z - delta << std::endl;
		std::cout << vertices[i].x - delta << " " << vertices[i].y + delta << " " << vertices[i].z - delta << std::endl;
		
		std::cout << vertices[i].x - delta << " " << vertices[i].y - delta << " " << vertices[i].z + delta << std::endl;
		std::cout << vertices[i].x + delta << " " << vertices[i].y - delta << " " << vertices[i].z + delta << std::endl;
		std::cout << vertices[i].x + delta << " " << vertices[i].y + delta << " " << vertices[i].z + delta << std::endl;
		std::cout << vertices[i].x - delta << " " << vertices[i].y + delta << " " << vertices[i].z + delta << std::endl;
	}
	
	//faces
	for(int i=0; i<numTriangles; i++){
		std::cout << "3 " << i*3+0 << " " << i*3+1 << " " << i*3+2 << std::endl;
	}
	
	//faces debug
	numero_vertices = numTriangles*3;
	//por cada vertice del cubo...
	for(int i=0; i<8; i++){
		//hay que espeficiar las 6 caras del cubo contenedor
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+0 << " ";
		std::cout << numero_vertices+8*i+1 << " ";
		std::cout << numero_vertices+8*i+2 << " ";
		std::cout << numero_vertices+8*i+3 << " ";
		std::cout << std::endl;
		
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+0 << " ";
		std::cout << numero_vertices+8*i+1 << " ";
		std::cout << numero_vertices+8*i+4 << " ";
		std::cout << numero_vertices+8*i+5 << " ";
		std::cout << std::endl;
		
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+1 << " ";
		std::cout << numero_vertices+8*i+2 << " ";
		std::cout << numero_vertices+8*i+5 << " ";
		std::cout << numero_vertices+8*i+6 << " ";
		std::cout << std::endl;
		
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+2 << " ";
		std::cout << numero_vertices+8*i+3 << " ";
		std::cout << numero_vertices+8*i+6 << " ";
		std::cout << numero_vertices+8*i+7 << " ";
		std::cout << std::endl;
		
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+0 << " ";
		std::cout << numero_vertices+8*i+3 << " ";
		std::cout << numero_vertices+8*i+4 << " ";
		std::cout << numero_vertices+8*i+7 << " ";
		std::cout << std::endl;
		
		std::cout << "4 ";
		std::cout << numero_vertices+8*i+4 << " ";
		std::cout << numero_vertices+8*i+5 << " ";
		std::cout << numero_vertices+8*i+6 << " ";
		std::cout << numero_vertices+8*i+7 << " ";
		std::cout << std::endl;
		
	}
	*/

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

//asi se rellenan los datos
/*
void GLCanvas::InitData()
{
	delete [] mcPoints;	//first free the previous allocated memory
	mcPoints = new mp4Vector[(nX+1)*(nY+1)*(nZ+1)];
	mpVector stepSize((MAXX-MINX)/nX, (MAXY-MINY)/nY, (MAXZ-MINZ)/nZ);
	for(int i=0; i < nX+1; i++)
		for(int j=0; j < nY+1; j++)
			for(int k=0; k < nZ+1; k++) {
				mp4Vector vert(MINX+i*stepSize.x, MINY+j*stepSize.y, MINZ+k*stepSize.z, 0);
				vert.val = Potential((mpVector)vert);
				mcPoints[i*(nY+1)*(nZ+1) + j*(nZ+1) + k] = vert;
	}
}
*/

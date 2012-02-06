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

#include "MarchingCubes.h"

#define MINVAL 1
#define D 1

mpVector Promedio(mp4Vector p1, mp4Vector p2, float value);

int main(int argc, char **argv)
{
	TRIANGLE * Triangles;
	int numTriangles;
	
	mp4Vector vertices[8];
	
	vertices[0] = mp4Vector(0,0,0,1);
	vertices[1] = mp4Vector(1,0,0,1);
	vertices[2] = mp4Vector(1,1,0,1);
	vertices[3] = mp4Vector(0,1,0,1);
	vertices[4] = mp4Vector(0,0,1,1);
	vertices[5] = mp4Vector(1,0,1,2);
	vertices[6] = mp4Vector(1,1,1,2);
	vertices[7] = mp4Vector(0,1,1,2);
	
	Triangles = MarchingCubes(
						/*int ncellsX*/ 1,
						/*int ncellsY*/ 1,
						/*int ncellsZ*/ 1,
						/*float minValue*/ 1.0f,
						/*mp4Vector* */ vertices,
						/*INTERSECTION*/ Promedio,
						/*int & */ numTriangles
						);

	//debug
	//std::cout << "numero de triangulos: " << numTriangles << std::endl;
	for(int i=0; i<numTriangles; i++){
		//std::cout << "triangulo " << i << ":" << std::endl;
		for(int j=0; j<3; j++){
			//std::cout << "vertice " << j << ": (" << Triangles[i].p[j].x << "," << Triangles[i].p[j].y << "," << Triangles[i].p[j].z << ")" << std::endl;
		}
	}
	
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
	
	return 0;
}

mpVector Promedio(mp4Vector p1, mp4Vector p2, float value)
{
	//debug
	//std::cout << "p1: (" << p1.x << "," << p1.y << "," << p1.z << "," << p1.val << ")" << std::endl;
	//std::cout << "p2: (" << p2.x << "," << p2.y << "," << p2.z << "," << p2.val << ")" << std::endl;
	//std::cout << "value: " << value << std::endl;
	
	//std::cout << "interpolacion: " << ((mpVector)p1 + (mpVector)p2)/2 << std::endl;
	return ((mpVector)p1 + (mpVector)p2)/2;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//	FileName:	MarchingCubes.cpp
//	Author	:	Michael Y. Polyakov
//	email	:	myp@andrew.cmu.edu  or  mikepolyakov@hotmail.com
//	website	:	www.angelfire.com/linux/myp
//	date	:	July 2002
//	
//	Description:	Marching Cubes Algorithm
/////////////////////////////////////////////////////////////////////////////////////////////

#include "MarchingCubes.h"

mpVector LinearInterp(mp4Vector p1, mp4Vector p2, float value)
{
	//debug
	//std::cout << "p1: (" << p1.x << "," << p1.y << "," << p1.z << "," << p1.val << ")" << std::endl;
	//std::cout << "p2: (" << p2.x << "," << p2.y << "," << p2.z << "," << p2.val << ")" << std::endl;
	//std::cout << "value: " << value << std::endl;
	
	mpVector p;
	if(p1.val != p2.val)
		p = (mpVector)p1 + ((mpVector)p2 - (mpVector)p1)/(p2.val - p1.val)*(value - p1.val);
	else
		p = (mpVector)p1;

	//std::cout << "interpolacion: " << p << std::endl;

	return p;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//	MARCHING CUBES	//

//  VERSION  1A).  //
TRIANGLE* MarchingCubes(
	int ncellsX,
	int ncellsY,
	int ncellsZ,
	float minValue,
	mp4Vector * points,
	
	INTERSECTION intersection,
	int &numTriangles
)
{
	TRIANGLE * triangles = new TRIANGLE[3*ncellsX*ncellsY*ncellsZ];//this should be enough space, if not change 4 to 5
	numTriangles = int(0);

	int YtimeZ = (ncellsY+1)*(ncellsZ+1);
	//go through all the points
	for(int i=0; i < ncellsX; i++)			//x axis
		for(int j=0; j < ncellsY; j++)		//y axis
			for(int k=0; k < ncellsZ; k++)	//z axis
			{
				//initialize vertices
				mp4Vector verts[8];
				int ind = i*YtimeZ + j*(ncellsZ+1) + k;

				//(step 3)
				
				//VERSION ORIGINAL
				verts[0] = points[ind];
				verts[1] = points[ind + YtimeZ];
				verts[2] = points[ind + YtimeZ + 1];
				verts[3] = points[ind + 1];
				verts[4] = points[ind + (ncellsZ+1)];
				verts[5] = points[ind + YtimeZ + (ncellsZ+1)];
				verts[6] = points[ind + YtimeZ + (ncellsZ+1) + 1];
				verts[7] = points[ind + (ncellsZ+1) + 1];
				
				//VERSION JOE PARA VER EL RESULTADO DE UN CUBO
				/*
				verts[0] = points[ind + 0];
				verts[1] = points[ind + 1];
				verts[2] = points[ind + 2];
				verts[3] = points[ind + 3];
				verts[4] = points[ind + 4];
				verts[5] = points[ind + 5];
				verts[6] = points[ind + 6];
				verts[7] = points[ind + 7];
				*/
				
				//get the index
				int cubeIndex = int(0);
				for(int n=0; n < 8; n++)
				{	
					//std::cout << "(verts[n].val, minValue) = (" << verts[n].val << "," << minValue << ")";
	
					/*(step 4)*/
					if(verts[n].val <= minValue)
					{
						cubeIndex |= (1 << n);
						//std::cout << " OK ";
					}
					//std::cout << std::endl;
				}
				
				//std::cout << "cube index: (" << cubeIndex << ")" << std::endl;

				//check if its completely inside or outside
				
				/*(step 5)*/
				if(!edgeTable[cubeIndex])
					continue;
			
				//get intersection vertices on edges and save into the array
				mpVector intVerts[12];
				
				/*(step 6)*/
				/*
				if(edgeTable[cubeIndex] & 1) intVerts[0] = intersection(verts[0], verts[1], minValue);
				if(edgeTable[cubeIndex] & 2) intVerts[1] = intersection(verts[1], verts[2], minValue);
				if(edgeTable[cubeIndex] & 4) intVerts[2] = intersection(verts[2], verts[3], minValue);
				if(edgeTable[cubeIndex] & 8) intVerts[3] = intersection(verts[3], verts[0], minValue);
				if(edgeTable[cubeIndex] & 16) intVerts[4] = intersection(verts[4], verts[5], minValue);
				if(edgeTable[cubeIndex] & 32) intVerts[5] = intersection(verts[5], verts[6], minValue);
				if(edgeTable[cubeIndex] & 64) intVerts[6] = intersection(verts[6], verts[7], minValue);
				if(edgeTable[cubeIndex] & 128) intVerts[7] = intersection(verts[7], verts[4], minValue);
				if(edgeTable[cubeIndex] & 256) intVerts[8] = intersection(verts[0], verts[4], minValue);
				if(edgeTable[cubeIndex] & 512) intVerts[9] = intersection(verts[1], verts[5], minValue);
				if(edgeTable[cubeIndex] & 1024) intVerts[10] = intersection(verts[2], verts[6], minValue);
				if(edgeTable[cubeIndex] & 2048) intVerts[11] = intersection(verts[3], verts[7], minValue);
				*/

				if(edgeTable[cubeIndex] & 1){
					intVerts[0] = intersection(verts[0], verts[1], minValue);
					//std::cout << "CERO" << std::endl;
				}
				
				if(edgeTable[cubeIndex] & 2){
					intVerts[1] = intersection(verts[1], verts[2], minValue);
					//std::cout << "UNO" << std::endl;
				}
				
				if(edgeTable[cubeIndex] & 4){
					intVerts[2] = intersection(verts[2], verts[3], minValue);
					//std::cout << "DOS" << std::endl;
				}
				
				if(edgeTable[cubeIndex] & 8){
					intVerts[3] = intersection(verts[3], verts[0], minValue);
					//std::cout << "TRES" << std::endl;
				}
				
				if(edgeTable[cubeIndex] & 16){
					intVerts[4] = intersection(verts[4], verts[5], minValue);	
					//std::cout << "CUATRO" << std::endl;	
				}
				if(edgeTable[cubeIndex] & 32){	
					intVerts[5] = intersection(verts[5], verts[6], minValue);	
					//std::cout << "CINCO" << std::endl;	
				}
				
				if(edgeTable[cubeIndex] & 64){			
					intVerts[6] = intersection(verts[6], verts[7], minValue);	
					//std::cout << "SEIS" << std::endl;	
				}

				if(edgeTable[cubeIndex] & 128){			
					intVerts[7] = intersection(verts[7], verts[4], minValue);	
					//std::cout << "SIETE" << std::endl;	
				}

				if(edgeTable[cubeIndex] & 256){			
					intVerts[8] = intersection(verts[0], verts[4], minValue);	
					//std::cout << "OCHO" << std::endl;	
				}
				
				if(edgeTable[cubeIndex] & 512){			
					intVerts[9] = intersection(verts[1], verts[5], minValue);	
					//std::cout << "NUEVE" << std::endl;	
				}

				if(edgeTable[cubeIndex] & 1024){			
					intVerts[10] = intersection(verts[2], verts[6], minValue);	
					//std::cout << "DIEZ" << std::endl;	
				}

				if(edgeTable[cubeIndex] & 2048){			
					intVerts[11] = intersection(verts[3], verts[7], minValue);	
					//std::cout << "ONCE" << std::endl;	
				}

				//now build the triangles using triTable
				for (int n=0; triTable[cubeIndex][n] != -1; n+=3) {
   /*(step 7)*/ 	triangles[numTriangles].p[0] = intVerts[triTable[cubeIndex][n+2]];
					triangles[numTriangles].p[1] = intVerts[triTable[cubeIndex][n+1]];
					triangles[numTriangles].p[2] = intVerts[triTable[cubeIndex][n]];
   /*(step 8)*/ 	triangles[numTriangles].norm = ((triangles[numTriangles].p[1] - 
						triangles[numTriangles].p[0]).Cross(triangles[numTriangles].p[2] - 
						triangles[numTriangles].p[0])).Normalize();
						
					//debug
					//std::cout << "intVerts[triTable[cubeIndex][n+2]: " << (mpVector)intVerts[triTable[cubeIndex][n+2]] << std::endl;
					//std::cout << "intVerts[triTable[cubeIndex][n+1]: " << (mpVector)intVerts[triTable[cubeIndex][n+1]] << std::endl;
					//std::cout << "intVerts[triTable[cubeIndex][n+0]: " << (mpVector)intVerts[triTable[cubeIndex][n+0]] << std::endl;
					
					numTriangles++;
				}
			
			}	//END OF FOR LOOP
		
		//free all the wasted space
		TRIANGLE * retTriangles = new TRIANGLE[numTriangles];
		for(int i=0; i < numTriangles; i++){
			retTriangles[i] = triangles[i];
			
			//debug
			//std::cout << "retTriangles[" << i << "].p[" << 0 << "]: " << retTriangles[i].p[0] << std::endl;
			//std::cout << "retTriangles[" << i << "].p[" << 1 << "]: " << retTriangles[i].p[1] << std::endl;
			//std::cout << "retTriangles[" << i << "].p[" << 2 << "]: " << retTriangles[i].p[2] << std::endl;
		}
			
		delete [] triangles;
	
	return retTriangles;
}


//	VERSION  1B).  //
TRIANGLE* MarchingCubesLinear(int ncellsX, int ncellsY, int ncellsZ, float minValue, 
									mp4Vector * points, int &numTriangles)
{
	return MarchingCubes(ncellsX, ncellsY, ncellsZ, minValue, points, LinearInterp, numTriangles);
}


//	VERSION  2A).  //
TRIANGLE* MarchingCubes(float mcMinX, float mcMaxX, float mcMinY, float mcMaxY, float mcMinZ, float mcMaxZ, 
							int ncellsX, int ncellsY, int ncellsZ, float minValue, 
							FORMULA formula, INTERSECTION intersection, int &numTriangles)
{
	//space is already defined and subdivided, staring with step 3
	//first initialize the points
	mp4Vector * mcDataPoints = new mp4Vector[(ncellsX+1)*(ncellsY+1)*(ncellsZ+1)];
	mpVector stepSize((mcMaxX-mcMinX)/ncellsX, (mcMaxY-mcMinY)/ncellsY, (mcMaxZ-mcMinZ)/ncellsZ);
	
	int YtimesZ = (ncellsY+1)*(ncellsZ+1);	//for extra speed
	for(int i=0; i < ncellsX+1; i++) {
		int ni = i*YtimesZ;						//for speed
		float vertX = mcMinX + i*stepSize.x;
		for(int j=0; j < ncellsY+1; j++) {
			int nj = j*(ncellsZ+1);				//for speed
			float vertY = mcMinY + j*stepSize.y;
			for(int k=0; k < ncellsZ+1; k++) {
				mp4Vector vert(vertX, vertY, mcMinZ + k*stepSize.z, 0);
				vert.val = formula((mpVector)vert);
   /*(step 3)*/ mcDataPoints[ni + nj + k] = vert;
			}
		}
	}
	//then run Marching Cubes (version 1A) on the data
	return MarchingCubes(ncellsX, ncellsY, ncellsZ, minValue, mcDataPoints, intersection, numTriangles);
}

//	VERSION  2B).  //
TRIANGLE* MarchingCubesLinear(float mcMinX, float mcMaxX, float mcMinY, float mcMaxY, float mcMinZ, float mcMaxZ, 
								int ncellsX, int ncellsY, int ncellsZ, float minValue, 
								FORMULA formula, int &numTriangles)
{
	return MarchingCubes(mcMinX, mcMaxX, mcMinY, mcMaxY, mcMinZ, mcMaxZ, ncellsX, ncellsY, ncellsZ, minValue,
		formula, LinearInterp, numTriangles);
}

//JOE
std::vector< TRIANGLE > MarchingCubesDataset(
	float minValue,
	Dataset dataset,

	INTERSECTION intersection,
	unsigned int &numTriangles
)
{

	unsigned int ncellsX = dataset.getNumPixelsOnAxis(dataset.X) - 1;
	unsigned int ncellsY = dataset.getNumPixelsOnAxis(dataset.Y) - 1;
	unsigned int ncellsZ = dataset.getNumPixelsOnAxis(dataset.Z) - 1;

	std::vector< TRIANGLE > triangles;

	numTriangles = int(0);

	//go through all the points
	for(unsigned int i=0; i < ncellsX; i++)			//x axis
		for(unsigned int j=0; j < ncellsY; j++)		//y axis
			for(unsigned int k=0; k < ncellsZ; k++)	//z axis
			{
				//initialize vertices
				mp4Vector verts[8];
				//int ind = i*YtimeZ + j*(ncellsZ+1) + k;

				//(step 3)

				//VERSION ORIGINAL
				/*
				verts[0] = points[ind];
				verts[1] = points[ind + YtimeZ];
				verts[2] = points[ind + YtimeZ + 1];
				verts[3] = points[ind + 1];
				verts[4] = points[ind + (ncellsZ+1)];
				verts[5] = points[ind + YtimeZ + (ncellsZ+1)];
				verts[6] = points[ind + YtimeZ + (ncellsZ+1) + 1];
				verts[7] = points[ind + (ncellsZ+1) + 1];
				*/

				verts[0].x = i;		verts[0].y = j;		verts[0].z = k;
				verts[1].x = i;		verts[1].y = j;		verts[1].z = k+1;
				verts[2].x = i+1;	verts[2].y = j;		verts[2].z = k+1;
				verts[3].x = i+1;	verts[3].y = j;		verts[3].z = k;
				verts[4].x = i;		verts[4].y = j+1;	verts[4].z = k;
				verts[5].x = i;		verts[5].y = j+1;	verts[5].z = k+1;
				verts[6].x = i+1;	verts[6].y = j+1;	verts[6].z = k+1;
				verts[7].x = i+1;	verts[7].y = j+1;	verts[7].z = k;

				verts[0].val = dataset.getPixelValueAt(i,		j,		k);
				verts[1].val = dataset.getPixelValueAt(i,		j,		k+1);
				verts[2].val = dataset.getPixelValueAt(i+1,		j,		k+1);
				verts[3].val = dataset.getPixelValueAt(i+1,		j,		k);
				verts[4].val = dataset.getPixelValueAt(i,		j+1,	k);
				verts[5].val = dataset.getPixelValueAt(i,		j+1,	k+1);
				verts[6].val = dataset.getPixelValueAt(i+1,		j+1,	k+1);
				verts[7].val = dataset.getPixelValueAt(i+1,		j+1,	k);

				//get the index
				int cubeIndex = int(0);
				for(int n=0; n < 8; n++)
				{
					/*(step 4)*/
					if(verts[n].val <= minValue)
						cubeIndex |= (1 << n);
				}

				//check if its completely inside or outside

				/*(step 5)*/
				if(!edgeTable[cubeIndex])
					continue;

				//get intersection vertices on edges and save into the array
				mpVector intVerts[12];

				/*(step 6)*/

				//arista 0 = vertice 0 -> vertice 1
				//arista 1 = vertice 1 -> vertice 2
				//arista 2 = vertice 2 -> vertice 3
				//arista 3 = vertice 3 -> vertice 0

				//arista 4 = vertice 4 -> vertice 5
				//arista 5 = vertice 5 -> vertice 6
				//arista 6 = vertice 6 -> vertice 7
				//arista 7 = vertice 7 -> vertice 4

				//arista 8 = vertice 0 -> vertice 4
				//arista 9 = vertice 1 -> vertice 5
				//arista 10 = vertice 2 -> vertice 6
				//arista 11 = vertice 3 -> vertice 7

				if(edgeTable[cubeIndex] & 1) intVerts[0] = intersection(verts[0], verts[1], minValue);
				if(edgeTable[cubeIndex] & 2) intVerts[1] = intersection(verts[1], verts[2], minValue);
				if(edgeTable[cubeIndex] & 4) intVerts[2] = intersection(verts[2], verts[3], minValue);
				if(edgeTable[cubeIndex] & 8) intVerts[3] = intersection(verts[3], verts[0], minValue);
				if(edgeTable[cubeIndex] & 16) intVerts[4] = intersection(verts[4], verts[5], minValue);
				if(edgeTable[cubeIndex] & 32) intVerts[5] = intersection(verts[5], verts[6], minValue);
				if(edgeTable[cubeIndex] & 64) intVerts[6] = intersection(verts[6], verts[7], minValue);
				if(edgeTable[cubeIndex] & 128) intVerts[7] = intersection(verts[7], verts[4], minValue);
				if(edgeTable[cubeIndex] & 256) intVerts[8] = intersection(verts[0], verts[4], minValue);
				if(edgeTable[cubeIndex] & 512) intVerts[9] = intersection(verts[1], verts[5], minValue);
				if(edgeTable[cubeIndex] & 1024) intVerts[10] = intersection(verts[2], verts[6], minValue);
				if(edgeTable[cubeIndex] & 2048) intVerts[11] = intersection(verts[3], verts[7], minValue);

				//now build the triangles using triTable
				for(int n=0; triTable[cubeIndex][n] != -1; n+=3)
				{
					/*(step 7)*/
					//triangles[numTriangles].p[0] = intVerts[triTable[cubeIndex][n+2]];
					//triangles[numTriangles].p[1] = intVerts[triTable[cubeIndex][n+1]];
					//triangles[numTriangles].p[2] = intVerts[triTable[cubeIndex][n]];
					TRIANGLE t;
					t.p[0] = intVerts[triTable[cubeIndex][n+2]];
					t.p[1] = intVerts[triTable[cubeIndex][n+1]];
					t.p[2] = intVerts[triTable[cubeIndex][n]];

					/*(step 8)*/
					//calculo de normales
					t.norm =
					(
						(t.p[2] - t.p[0]).Cross(t.p[1] - t.p[0])
					).Normalize();

					triangles.push_back(t);

					numTriangles++;
				}
			}	//END OF FOR LOOP

	return triangles;
}

// STLReader Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stlReader.h"

int main()
{
	//load the stl datasss
	std::string input_filename = "./triangle.stl";
	Mesh *mesh1 = new Mesh(input_filename);
	//export the stl data
	std::string output_filename = "./triangle_out.stl";
	long a=mesh1->trianglelist.size();
	//Create Voxel Grid
	Mesh::Vec3 bbMax, bbMin;
	mesh1->BBox(*mesh1, bbMin, bbMax);

	//Build Voxel Grid
	float bbX = bbMax[0] - bbMin[0];
	float bbY = bbMax[1] - bbMin[1];
	float bbZ = bbMax[2] - bbMin[2];
	std::cout << bbX << std::endl;
	std::cout << bbY << std::endl;
	std::cout << bbZ << std::endl;
	std::cout << a << std::endl;
	mesh1->export_stl(output_filename);
	delete mesh1;
    return 0;
}


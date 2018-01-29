// STLReader Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stlReader.h"
#include <ctime>
#include <chrono>

int main()
{

	//set a clock for the nearest neighbor search
	auto start2 = std::chrono::steady_clock::now();
	//load the stl data
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
	//calculate the duration of the Kd Tree Search
	auto end2 = std::chrono::steady_clock::now();
	auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
	std::cout << "The duration of the STL Reader is " << elapsed2.count() << " microseconds." << std::endl;
	delete mesh1;
    return 0;
}


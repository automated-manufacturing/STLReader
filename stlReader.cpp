//this library is used to import and export binary stl files
//Copyright: Fei Shen 
//last update: 10/01/2017

#include "stdafx.h"
#include "stlReader.h"

Mesh::Mesh(const std::string& filename)
{
	load_mesh(filename);
}

// read stl file data into algorithm
//Binary Stl format
//UINT8[80] – Header
//UINT32 – Number of triangles
//foreach triangle
//REAL32[3] – Normal vector
//REAL32[3] – Vertex 1
//REAL32[3] – Vertex 2
//REAL32[3] – Vertex 3
//UINT16 – Attribute byte count
//end

void Mesh::load_mesh(const std::string& filename){
	//read binary file
	//file open for reading
	//operations are performed in binary mode rather than text
	std::ifstream f(filename, std::ios::in | std::ios::binary);
	if (!f.good()) {
		std::cout << "Error: cannot open mesh " << filename << "\n";
		return;
	}
	//header
	char header_info[80] = "";
	char n_triangles[4];
	f.read(header_info, 80);
	f.read(n_triangles, 4);
	unsigned int* r = (unsigned int*)n_triangles;
	unsigned int num_triangles = *r;
	//number of triangles
	std::cout << "Num Triangles: " << num_triangles << "\n";
	for (unsigned int i = 0; i < num_triangles; i++) {
		//normal vector of triangle
		auto normal = parse_point(f);
		//vertice of triangle
		auto v1 = parse_point(f);
		//vertice of triangle
		auto v2 = parse_point(f);
		//vertice of triangle
		auto v3 = parse_point(f);
		//push into triangle list
		trianglelist.push_back(Triangle(normal, v1, v2, v3));
		//attributes
		char dummy[2];

		f.read(dummy, 2);
	}
	std::cout << "Successfully import stl file"<< "\n";
}

//parse the binary data and convert to float 
float Mesh::parse_float(std::ifstream& s) {

	char f_buf[sizeof(float)];

	s.read(f_buf, 4);

	float* fptr = (float*)f_buf;

	return *fptr;
};

//parse the vector
Mesh::Vec3 Mesh::parse_point(std::ifstream& s) {

	Vec3 vec;

	vec[0] = parse_float(s);

	vec[1] = parse_float(s);

	vec[2] = parse_float(s);

	return  vec;
};

//export binary stl file 
//Binary Stl format
//UINT8[80] – Header
//UINT32 – Number of triangles
//foreach triangle
//REAL32[3] – Normal vector
//REAL32[3] – Vertex 1
//REAL32[3] – Vertex 2
//REAL32[3] – Vertex 3
//UINT16 – Attribute byte count
//end

void Mesh::export_stl(const std::string& filename) {
	//binary file
	std::string header_info = "solid " + filename + "-output";
	char head[80];
	std::strncpy(head, header_info.c_str(), sizeof(head));
	//attributes
	char attribute[2] = "0";
	//number of triangles
	int nTrilong = trianglelist.size();
	std::ofstream ofs(filename, std::ofstream::binary | std::ofstream::trunc);
	if (!ofs.good()) {
		std::cout << "cannot open output file" << filename << "\n";
	}
	//write header into stl file
	ofs.write(head, sizeof(head));
	//write number of triangles into stl file
	ofs.write((char*) &nTrilong,sizeof(int));
	for (unsigned int ii = 0; ii < trianglelist.size(); ++ii) {
		// normal vector coordinates

		ofs.write((char*)&trianglelist[ii].normal.x, sizeof(float));
		ofs.write((char*)&trianglelist[ii].normal.y, sizeof(float));
		ofs.write((char*)&trianglelist[ii].normal.z, sizeof(float));

		//vertex 1 coordinates
		ofs.write((char*)&trianglelist[ii].v1.x, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v1.y, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v1.z, sizeof(float));

		//vertex 2 coordinates
		ofs.write((char*)&trianglelist[ii].v2.x, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v2.y, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v2.z, sizeof(float));

		//vertex 3 coordinates
		ofs.write((char*)&trianglelist[ii].v3.x, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v3.y, sizeof(float));
		ofs.write((char*)&trianglelist[ii].v3.z, sizeof(float));

		//Attibutes
		ofs.write(attribute, sizeof(short));
	}
	
	ofs.close();
	std::cout << "Successfully export stl file." << std::endl;
};

void Mesh::BBox(const Mesh & m,
	Vec3 & mn, Vec3 & mx)
{
	BBox(m.trianglelist, mn, mx);
}

void Mesh::BBox(const std::vector<Triangle >& trianglelist,
	Vec3 & mn, Vec3 & mx)
{
	mn = trianglelist[0].v1;
	mx = trianglelist[0].v1;
	for (unsigned int ii = 1; ii<trianglelist.size(); ii++) {
		for (int dim = 0; dim<3; dim++) {
			if (trianglelist[ii].v1[dim]<mn[dim]) {
				mn[dim] = trianglelist[ii].v1[dim];
			}
			if (trianglelist[ii].v2[dim]<mn[dim]) {
				mn[dim] = trianglelist[ii].v2[dim];
			}
			if (trianglelist[ii].v3[dim]<mn[dim]) {
				mn[dim] = trianglelist[ii].v3[dim];
			}
			if (trianglelist[ii].v1[dim]>mx[dim]) {
				mx[dim] = trianglelist[ii].v1[dim];
			}
			if (trianglelist[ii].v2[dim]>mx[dim]) {
				mx[dim] = trianglelist[ii].v2[dim];
			}
			if (trianglelist[ii].v3[dim]>mx[dim]) {
				mx[dim] = trianglelist[ii].v3[dim];
			}
		}
	}
}

Mesh & Mesh::operator= (const Mesh& m)
{
	trianglelist = m.trianglelist;
	return *this;
}


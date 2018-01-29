//this library is used to import and export binary stl files
//Copyright: Fei Shen 
//last update: 10/01/2017

#pragma once
#ifndef MESH_H
#define MESH_H

#include <map>
#include <cstdlib>
#include <algorithm>
#ifdef _WIN32
#define NOMINMAX //Stop errors with std::max
#include <windows.h>
#endif
#include <stdio.h>
#define EPSILON 1e-9
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


class Mesh {
public:
	//Data Types 3D vector
	typedef struct Vec3Struct
	{
		union
		{
			float m_pos[3];
			struct { float x, y, z; };
		};

		Vec3Struct() :x(0.0), y(0.0), z(0.0) {}
		Vec3Struct(float m_x, float m_y, float m_z) :x(m_x), y(m_y), z(m_z) {}
		inline float & operator[](unsigned int index) { return m_pos[index]; }
		inline const float & operator[](unsigned int index) const { return m_pos[index]; }
		inline void operator+=(const Vec3Struct &a)
		{
			x += a.x;
			y += a.y;
			z += a.z;
		}
	}Vec3;

	// data type triangle (normal and 3 vertices)
	typedef struct TriangleStruct
	{
		Vec3 normal;
		Vec3 v1, v2, v3;
		TriangleStruct(Vec3 normalp, Vec3 m_v1, Vec3 m_v2, Vec3 m_v3) :normal(normalp), v1(m_v1), v2(m_v2), v3(m_v3) {};
	}Triangle;

	/// triangle list
	std::vector<Triangle> trianglelist;
	Mesh() {};
	Mesh & operator= (const Mesh& m);
	Mesh(const std::string&);
	void load_mesh(const std::string& filename);
	void export_stl(const std::string& filename);
	float parse_float(std::ifstream& s);
	Vec3 parse_point(std::ifstream& s);
	void BBox(const Mesh & m,
		Vec3 & mn, Vec3 & mx);
	void BBox(const std::vector<Triangle >& triangles, Vec3 & mn,
		Vec3 & mx);

	//Some useful operations
	//Compute v1 - v2
	friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
	{
		Vec3 v3;
		v3[0] = v1[0] - v2[0];
		v3[1] = v1[1] - v2[1];
		v3[2] = v1[2] - v2[2];
		return v3;
	}

	friend Vec3  operator+(const Vec3 &v1, const Vec3 &v2)
	{
		Vec3 v3;
		v3[0] = v1[0] + v2[0];
		v3[1] = v1[1] + v2[1];
		v3[2] = v1[2] + v2[2];

		return v3;
	}

	//Cross Product
	friend Vec3  operator%(const Vec3 &v1, const Vec3 &v2)
	{
		Vec3 v3;
		v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
		v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
		v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return v3;
	}
	//Dot Product
	friend float operator*(const Mesh::Vec3 &v1, const Mesh::Vec3 &v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

};
#endif




#include "ShapeGenerator.h"
#include <vertex.h>
#include <glm\glm.hpp>
#include <iostream>     
#include <fstream> 
#include <string>
#include <vector>
#include <sstream>
#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/ sizeof(*a)
ShapeData ShapeGenerator::makeTriangle() {

	ShapeData ret;
	Vertex verts[] =
	{	//Main sahpe
		glm::vec3(+0.0f, +0.05f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(+.1f, -0.05f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(-0.1f, -0.05f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		// back ground image
		glm::vec3(-1.0f, 0.0f, +0.1f),
		glm::vec3(+0.0f, +0.0f, +1.0f),

		glm::vec3(+1.0f, 0.0f, +0.1f),
		glm::vec3(+0.0f, +0.0f, +1.0f),

		glm::vec3(+0.0f, 1.0f, +0.1f),
		glm::vec3(+0.0f, +0.0f, +1.0f),

		glm::vec3(+0.0f, -1.0f, +0.1f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
	};
	ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, verts, sizeof(verts));

	GLushort indices[] = { 0,1,2 };
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::makeCube() {
	ShapeData ret;
	Vertex verts[] = {
		glm::vec3(-1.0f, +1.0f, +1.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(+1.0f, +1.0f, +1.0f), // 1
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(+1.0f, +1.0f, -1.0f), // 2
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(-1.0f, +1.0f, -1.0f), // 3
		glm::vec3(+1.0f, +1.0f, +1.0f), // Color
		glm::vec3(-1.0f, +1.0f, -1.0f), // 4
		glm::vec3(+1.0f, +0.0f, +1.0f), // Color
		glm::vec3(+1.0f, +1.0f, -1.0f), // 5
		glm::vec3(+0.0f, +0.5f, +0.2f), // Color
		glm::vec3(+1.0f, -1.0f, -1.0f), // 6
		glm::vec3(+0.8f, +0.6f, +0.4f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 7
		glm::vec3(+0.3f, +1.0f, +0.5f), // Color
		glm::vec3(+1.0f, +1.0f, -1.0f), // 8
		glm::vec3(+0.2f, +0.5f, +0.2f), // Color
		glm::vec3(+1.0f, +1.0f, +1.0f), // 9
		glm::vec3(+0.9f, +0.3f, +0.7f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 10
		glm::vec3(+0.3f, +0.7f, +0.5f), // Color
		glm::vec3(+1.0f, -1.0f, -1.0f), // 11
		glm::vec3(+0.5f, +0.7f, +0.5f), // Color
		glm::vec3(-1.0f, +1.0f, +1.0f), // 12
		glm::vec3(+0.7f, +0.8f, +0.2f), // Color
		glm::vec3(-1.0f, +1.0f, -1.0f), // 13
		glm::vec3(+0.5f, +0.7f, +0.3f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 14
		glm::vec3(+0.4f, +0.7f, +0.7f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 15
		glm::vec3(+0.2f, +0.5f, +1.0f), // Color
		glm::vec3(+1.0f, +1.0f, +1.0f), // 16
		glm::vec3(+0.6f, +1.0f, +0.7f), // Color
		glm::vec3(-1.0f, +1.0f, +1.0f), // 17
		glm::vec3(+0.6f, +0.4f, +0.8f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 18
		glm::vec3(+0.2f, +0.8f, +0.7f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 19
		glm::vec3(+0.2f, +0.7f, +1.0f), // Color
		glm::vec3(+1.0f, -1.0f, -1.0f), // 20
		glm::vec3(+0.8f, +0.3f, +0.7f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 21
		glm::vec3(+0.8f, +0.9f, +0.5f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 22
		glm::vec3(+0.5f, +0.8f, +0.5f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 23
		glm::vec3(+0.9f, +1.0f, +0.2f), // Color
	};
	ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, verts, sizeof(verts));
	unsigned short indices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));
	return ret;
}

ShapeData ShapeGenerator::makeArrow()
{
	ShapeData ret;
	Vertex stackVerts[] =
	{
		// Top side of arrow head
		glm::vec3(+0.00f, +0.25f, -0.25f),         // 0
		glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
		glm::vec3(+0.50f, +0.25f, -0.25f),         // 1
		glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
		glm::vec3(+0.00f, +0.25f, -1.00f),         // 2
		glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
		glm::vec3(-0.50f, +0.25f, -0.25f),         // 3
		glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
		// Bottom side of arrow head
		glm::vec3(+0.00f, -0.25f, -0.25f),         // 4
		glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
		glm::vec3(+0.50f, -0.25f, -0.25f),         // 5
		glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
		glm::vec3(+0.00f, -0.25f, -1.00f),         // 6
		glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
		glm::vec3(-0.50f, -0.25f, -0.25f),         // 7
		glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
		// Right side of arrow tip
		glm::vec3(+0.50f, +0.25f, -0.25f),         // 8
		glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
		glm::vec3(+0.00f, +0.25f, -1.00f),         // 9
		glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
		glm::vec3(+0.00f, -0.25f, -1.00f),         // 10
		glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
		glm::vec3(+0.50f, -0.25f, -0.25f),         // 11
		glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
	    // Left side of arrow tip
	    glm::vec3(+0.00f, +0.25f, -1.00f),         // 12
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(-0.50f, +0.25f, -0.25f),         // 13
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(+0.00f, -0.25f, -1.00f),         // 14
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(-0.50f, -0.25f, -0.25f),         // 15
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    // Back side of arrow tip
	    glm::vec3(-0.50f, +0.25f, -0.25f),         // 16
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(+0.50f, +0.25f, -0.25f),         // 17
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(-0.50f, -0.25f, -0.25f),         // 18
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(+0.50f, -0.25f, -0.25f),         // 19
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	     // Top side of back of arrow
	    glm::vec3(+0.25f, +0.25f, -0.25f),         // 20
	    glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
	    glm::vec3(+0.25f, +0.25f, +1.00f),         // 21
	    glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
	    glm::vec3(-0.25f, +0.25f, +1.00f),         // 22
	    glm::vec3(+1.00f, +0.00f, +0.00f),		  // Color
	    glm::vec3(-0.25f, +0.25f, -0.25f),         // 23
	    // Color
	    // Bottom side of back of arrow
	    glm::vec3(+0.25f, -0.25f, -0.25f),         // 24
	    glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
	    glm::vec3(+0.25f, -0.25f, +1.00f),         // 25
	    glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
	    glm::vec3(-0.25f, -0.25f, +1.00f),         // 26
	    glm::vec3(+0.00f, +0.00f, +1.00f),		  // Color
	    glm::vec3(-0.25f, -0.25f, -0.25f),         // 27
        // Color
        // Right side of back of arrow
        glm::vec3(+0.25f, +0.25f, -0.25f),         // 28
        glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
        glm::vec3(+0.25f, -0.25f, -0.25f),         // 29
        glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
        glm::vec3(+0.25f, -0.25f, +1.00f),         // 30
        glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
        glm::vec3(+0.25f, +0.25f, +1.00f),         // 31
        glm::vec3(+0.60f, +1.00f, +0.00f),		  // Color
	    // Left side of back of arrow
	    glm::vec3(-0.25f, +0.25f, -0.25f),         // 32
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(-0.25f, -0.25f, -0.25f),         // 33
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(-0.25f, -0.25f, +1.00f),         // 34
	    glm::vec3(+0.00f, +1.00f, +0.00f),		  // Color
	    glm::vec3(-0.25f, +0.25f, +1.00f),         // 35
	     // Color
	     // Back side of back of arrow
	    glm::vec3(-0.25f, +0.25f, +1.00f),         // 36
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(+0.25f, +0.25f, +1.00f),         // 37
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(-0.25f, -0.25f, +1.00f),         // 38
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    glm::vec3(+0.25f, -0.25f, +1.00f),         // 39
	    glm::vec3(+0.50f, +0.50f, +0.50f),		  // Color
	    };

	GLushort stackIndices[] = {
		0, 1, 2, // Top
		0, 2, 3,
		4, 6, 5, // Bottom
		4, 7, 6,
		8, 10, 9, // Right side of arrow tip
		8, 11, 10,
		12, 15, 13, // Left side of arrow tip
		12, 14, 15,
		16, 19, 17, // Back side of arrow tip
		16, 18, 19,
		20, 22, 21, // Top side of back of arrow
		20, 23, 22,
		24, 25, 26, // Bottom side of back of arrow
		24, 26, 27,
		28, 30, 29, // Right side of back of arrow
		28, 31, 30,
		32, 33, 34, // Left side of back of arrow
		32, 34, 35,
		36, 39, 37, // Back side of back of arrow
		36, 38, 39,
	};

	ret.numVertices = sizeof(stackVerts) / sizeof(*stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	ret.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));
	return ret;
}

ShapeData ShapeGenerator::readObj(const char* path)
{
	ShapeData ret;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normalsl;
	std::vector<GLushort> Indices;

	std::ifstream in(path, std::ifstream::in);
	if (!in)
	{
		std::cerr << "Cannot open " << path << std::endl; exit(1);
	}
	std::string line;
	while (getline(in, line)) 
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream linePiece(line.substr(2));
			glm::vec3 v;
			linePiece >> v.x; linePiece >> v.y; linePiece >> v.z;
			vertices.push_back(v);
			glm::vec3 color = glm::vec3(+1.0f, +1.0f, +1.0f);
			vertices.push_back(color);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream linePiece(line.substr(2));
			GLushort a, b, c;
			linePiece >> a; linePiece >> b; linePiece >> c;
			a--; b--; c--;
			Indices.push_back(a); Indices.push_back(b); Indices.push_back(c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
	}

	ret.numVertices = vertices.size();
	ret.vertices = new Vertex[vertices.size()];
	memcpy(ret.vertices, vertices.data(), vertices.size());

	ret.numIndices = Indices.size();
	ret.indices = new GLushort[Indices.size()];
	memcpy(ret.indices, Indices.data(), Indices.size());


	return ret;
}

ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}

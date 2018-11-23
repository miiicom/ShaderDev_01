#include "ShapeGenerator.h"
#include <vertex.h>
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
		glm::vec3(+0.0f, +1.0f, +0.0f),			// position
		glm::vec4(+1.0f, +0.0f, +0.0f, +0.0f),	// color
		glm::vec3(+0.0f, +0.0f, +1.0f),			// normal
		glm::vec2(+0.5f, +0.0f),					// uv
		glm::vec3(+1.0f, +0.0f, 0.0f),			// tangent
		
		glm::vec3(-1.0f, -1.0f, +0.0f),			// position
		glm::vec4(+0.0f, +1.0f, +0.0f, +0.0f),	// color
		glm::vec3(+0.0f, +0.0f, +1.0f),			// normal
		glm::vec2(+0.0f, +1.0f),					// uv
		glm::vec3(+1.0f, +0.0f, 0.0f),			// tangent
		
		glm::vec3(+1.0f, -1.0f, +0.0f),			// position
		glm::vec4(+0.0f, +0.0f, +1.0f, +0.0f),	// color
		glm::vec3(+0.0f, +0.0f, +1.0f),			// normal
		glm::vec2(+1.0f, +1.0f),					// uv
		glm::vec3(+1.0f, +0.0f, 0.0f),			// tangent
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
	Vertex stackVerts[] =
	{
		// Top
		glm::vec3(-1.0f, +1.0f, +1.0f),        // 0
		glm::vec4(+1.0f, +0.0f, +0.0f, +1.0f), // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, +1.0f, +1.0f),        // 1
		glm::vec4(+0.0f, +1.0f, +0.0f, +1.0f), // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, +1.0f, -1.0f),        // 2
		glm::vec4(+0.0f, +0.0f, +1.0f, +1.0f), // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, +1.0f, -1.0f),        // 3
		glm::vec4(+1.0f, +1.0f, +1.0f, +1.0f), // Color
		glm::vec3(+0.0f, +1.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent

		// Front
		glm::vec3(-1.0f, +1.0f, -1.0f),        // 4
		glm::vec4(+1.0f, +0.0f, +1.0f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, +1.0f, -1.0f),        // 5
		glm::vec4(+0.0f, +0.5f, +0.2f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, -1.0f, -1.0f),        // 6
		glm::vec4(+0.8f, +0.6f, +0.4f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, -1.0f),        // 7
		glm::vec4(+0.3f, +1.0f, +0.5f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, -1.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent

		// Right
		glm::vec3(+1.0f, +1.0f, -1.0f),        // 8
		glm::vec4(+0.2f, +0.5f, +0.2f, +1.0f), // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+0.0f, +0.0f, -1.0f),		  // Tangent
		glm::vec3(+1.0f, +1.0f, +1.0f),        // 9
		glm::vec4(+0.9f, +0.3f, +0.7f, +1.0f), // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+0.0f, +0.0f, -1.0f),		  // Tangent
		glm::vec3(+1.0f, -1.0f, +1.0f),        // 10
		glm::vec4(+0.3f, +0.7f, +0.5f, +1.0f), // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+0.0f, +0.0f, -1.0f),		  // Tangent
		glm::vec3(+1.0f, -1.0f, -1.0f),        // 11
		glm::vec4(+0.5f, +0.7f, +0.5f, +1.0f), // Color
		glm::vec3(+1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+0.0f, +0.0f, -1.0f),		  // Tangent

		 // Left
		glm::vec3(-1.0f, +1.0f, +1.0f),        // 12
		glm::vec4(+0.7f, +0.8f, +0.2f, +1.0f), // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+0.0f, +0.0f, +1.0f),		  // Tangent
		glm::vec3(-1.0f, +1.0f, -1.0f),        // 13
		glm::vec4(+0.5f, +0.7f, +0.3f, +1.0f), // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+0.0f, +0.0f, +1.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, -1.0f),        // 14
		glm::vec4(+0.4f, +0.7f, +0.7f, +1.0f), // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+0.0f, +0.0f, +1.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, +1.0f),        // 15
		glm::vec4(+0.2f, +0.5f, +1.0f, +1.0f), // Color
		glm::vec3(-1.0f, +0.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+0.0f, +0.0f, +1.0f),		  // Tangent

		// Back
		glm::vec3(+1.0f, +1.0f, +1.0f),        // 16
		glm::vec4(+0.6f, +1.0f, +0.7f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, +1.0f, +1.0f),        // 17
		glm::vec4(+0.6f, +0.4f, +0.8f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, +1.0f),        // 18
		glm::vec4(+0.2f, +0.8f, +0.7f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, -1.0f, +1.0f),        // 19
		glm::vec4(+0.2f, +0.7f, +1.0f, +1.0f), // Color
		glm::vec3(+0.0f, +0.0f, +1.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent

		// Bottom
		glm::vec3(+1.0f, -1.0f, -1.0f),        // 20
		glm::vec4(+0.8f, +0.3f, +0.7f, +1.0f), // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, -1.0f),        // 21
		glm::vec4(+0.8f, +0.9f, +0.5f, +1.0f), // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +1.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(-1.0f, -1.0f, +1.0f),        // 22
		glm::vec4(+0.5f, +0.8f, +0.5f, +1.0f), // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),        // Normal
		glm::vec2(+0.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
		glm::vec3(+1.0f, -1.0f, +1.0f),        // 23
		glm::vec4(+0.9f, +1.0f, +0.2f, +1.0f), // Color
		glm::vec3(+0.0f, -1.0f, +0.0f),        // Normal
		glm::vec2(+1.0f, +0.0f),               // UV
		glm::vec3(+1.0f, +0.0f, +0.0f),		  // Tangent
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}

ShapeData ShapeGenerator::makeArrow()
{
	ShapeData ret;
	Vertex stackVerts[] =
	{
		// Top side of arrow head
		// Top side of arrow head
		 glm::vec3(+0.00f, +0.25f, -0.25f),         // 0
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.50f, +0.25f, -0.25f),         // 1
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.00f, +0.25f, -1.00f),         // 2
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.50f, +0.25f, -0.25f),         // 3
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Bottom side of arrow head
		 glm::vec3(+0.00f, -0.25f, -0.25f),         // 4
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.50f, -0.25f, -0.25f),         // 5
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.00f, -0.25f, -1.00f),         // 6
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.50f, -0.25f, -0.25f),         // 7
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Right side of arrow tip
		 glm::vec3(+0.50f, +0.25f, -0.25f),         // 8
		 glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.00f, +0.25f, -1.00f),         // 9
		 glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.00f, -0.25f, -1.00f),         // 10
		 glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.50f, -0.25f, -0.25f),         // 11
		 glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Left side of arrow tip
		 glm::vec3(+0.00f, +0.25f, -1.00f),         // 12
		 glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.50f, +0.25f, -0.25f),         // 13
		 glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.00f, -0.25f, -1.00f),         // 14
		 glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.50f, -0.25f, -0.25f),         // 15
		 glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
		 glm::vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Back side of arrow tip
		 glm::vec3(-0.50f, +0.25f, -0.25f),         // 16
		 glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
		 glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.50f, +0.25f, -0.25f),         // 17
		 glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
		 glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.50f, -0.25f, -0.25f),         // 18
		 glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
		 glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.50f, -0.25f, -0.25f),         // 19
		 glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
		 glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Top side of back of arrow
		 glm::vec3(+0.25f, +0.25f, -0.25f),         // 20
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.25f, +0.25f, +1.00f),         // 21
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.25f, +0.25f, +1.00f),         // 22
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.25f, +0.25f, -0.25f),         // 23
		 glm::vec4(+1.00f, +0.00f, +0.00f, +1.00f), // Color
		 glm::vec3(+0.00f, +1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 // Bottom side of back of arrow
		 glm::vec3(+0.25f, -0.25f, -0.25f),         // 24
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(+0.25f, -0.25f, +1.00f),         // 25
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.25f, -0.25f, +1.00f),         // 26
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
		 glm::vec3(-0.25f, -0.25f, -0.25f),         // 27
		 glm::vec4(+0.00f, +0.00f, +1.00f, +1.00f), // Color
		 glm::vec3(+0.00f, -1.00f, +0.00f),         // Normal
		 glm::vec2(+0.00f, +0.00f),                 // UV
		 glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     // Right side of back of arrow
	     glm::vec3(+0.25f, +0.25f, -0.25f),         // 28
	     glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(+1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(+0.25f, -0.25f, -0.25f),         // 29
	     glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(+1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(+0.25f, -0.25f, +1.00f),         // 30
	     glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(+1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(+0.25f, +0.25f, +1.00f),         // 31
	     glm::vec4(+0.60f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(+1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     // Left side of back of arrow
	     glm::vec3(-0.25f, +0.25f, -0.25f),         // 32
	     glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(-1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(-0.25f, -0.25f, -0.25f),         // 33
	     glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(-1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(-0.25f, -0.25f, +1.00f),         // 34
	     glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(-1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(-0.25f, +0.25f, +1.00f),         // 35
	     glm::vec4(+0.00f, +1.00f, +0.00f, +1.00f), // Color
	     glm::vec3(-1.00f, +0.00f, +0.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     // Back side of back of arrow
	     glm::vec3(-0.25f, +0.25f, +1.00f),         // 36
	     glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
	     glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(+0.25f, +0.25f, +1.00f),         // 37
	     glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
	     glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(-0.25f, -0.25f, +1.00f),         // 38
	     glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
	     glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
	     glm::vec3(+0.25f, -0.25f, +1.00f),         // 39
	     glm::vec4(+0.50f, +0.50f, +0.50f, +1.00f), // Color
	     glm::vec3(+0.00f, +0.00f, +1.00f),         // Normal
	     glm::vec2(+0.00f, +0.00f),                 // UV
	     glm::vec3(+0.00f, +0.00f, +0.00f),		  // Tangent
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

//
//# is a comment, just like // in C++
//usemtl and mtllib describe the look of the model.We won’t use this in this tutorial.
//v is a vertex
//vt is the texture coordinate of one vertex
//vn is the normal of one vertex
//f is a face


ShapeData ShapeGenerator::readObj(const char* path)
{
	ShapeData ret;
	std::vector<glm::vec3> verticesVector;
	std::vector<glm::vec3> normalslVector;
	std::vector<GLushort> IndicesVector;
	std::vector<glm::vec2> uv0Vector;

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
			verticesVector.push_back(v);
			glm::vec3 color = glm::vec3(+1.0f, +1.0f, +1.0f);
			verticesVector.push_back(color);
		}
		else if (line.substr(0, 2) == "vt ") {
			std::istringstream linePiece(line.substr(2));
			glm::vec3 uv0;
			linePiece >> uv0.x; linePiece >> uv0.y;
			verticesVector.push_back(uv0);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream linePiece(line.substr(2));
			GLushort a, b, c;
			linePiece >> a; linePiece >> b; linePiece >> c;
			a--; b--; c--;
			IndicesVector.push_back(a); IndicesVector.push_back(b); IndicesVector.push_back(c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	ret.numVertices = verticesVector.size();
	ret.vertices = new Vertex[verticesVector.size()];
	memcpy(ret.vertices, verticesVector.data(), verticesVector.size());

	ret.numIndices = IndicesVector.size();
	ret.indices = new GLushort[IndicesVector.size()];
	memcpy(ret.indices, IndicesVector.data(), IndicesVector.size());


	return ret;
}

ShapeData ShapeGenerator::makePlaneVerts(GLuint dimensions)
{
	ShapeData ret;
	ret.numVertices = dimensions * dimensions;
	int half = dimensions / 2;
	ret.vertices = new Vertex[ret.numVertices];
	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			Vertex& thisVert = ret.vertices[i * dimensions + j];
			thisVert.position.x = j - half;
			thisVert.position.z = i - half;
			thisVert.position.y = 0;
			thisVert.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			thisVert.color = glm::vec4(1.0f, 1.0f, 1.0f, +1.0f);
			thisVert.uv0.x = (float) j / (float)dimensions;
			thisVert.uv0.y = (float) i / (float)dimensions;
			thisVert.tangent = glm::vec3(1.0f, 0.0f, 0.0f);
		}
	}
	return ret;
}

ShapeData ShapeGenerator::makePlaneIndices(GLuint dimensions)
{
	ShapeData ret;
	ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
	ret.indices = new unsigned short[ret.numIndices];
	int runner = 0;
	for (int row = 0; row < dimensions - 1; row++)
	{
		for (int col = 0; col < dimensions - 1; col++)
		{
			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;

			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;
			ret.indices[runner++] = dimensions * row + col + 1;
		}
	}
	assert(runner = ret.numIndices);
	return ret;
}


ShapeData ShapeGenerator::makePlane(GLuint dimensions)
{
	ShapeData ret = makePlaneVerts(dimensions);
	ShapeData ret2 = makePlaneIndices(dimensions);
	ret.numIndices = ret2.numIndices;
	ret.indices = ret2.indices;
	return ret;
}

ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}

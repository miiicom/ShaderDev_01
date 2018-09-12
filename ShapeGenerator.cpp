#include "ShapeGenerator.h"
#include <vertex.h>
#include <glm\glm.hpp>
#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/ sizeof(*a)
ShapeData ShapeGenerator::makeTriangle() {

	ShapeData ret;
	Vertex verts[] =
	{	//Main sahpe
		glm::vec3(-0.9f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(-1.0f, 0.9f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(-0.8f, 0.9f, +0.0f),
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


ShapeGenerator::ShapeGenerator()
{
}


ShapeGenerator::~ShapeGenerator()
{
}
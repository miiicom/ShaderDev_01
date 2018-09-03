#pragma once
#include <GL\glew.h>
class Vertex;

struct ShapeData {
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;
};
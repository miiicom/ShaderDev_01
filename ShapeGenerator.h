#pragma once
#include <ShapeData.h>
#include <glm\glm.hpp>
class ShapeGenerator
{
public:
	static ShapeData makeTriangle();
	static ShapeData makeCube();
	static ShapeData makeArrow();
	static ShapeData makePlaneVerts(GLuint dimensions);
	static ShapeData makePlaneIndices(GLuint dimensions);
	static ShapeData makePlane(GLuint dimensions);
	static ShapeData readObj(const char* path);
	ShapeGenerator();
	~ShapeGenerator();
};


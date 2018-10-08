
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <MeGLWindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <ShapeGenerator.h>
#include <vertex.h>
#include <MeCamera.h>
using namespace std;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRU = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
GLuint programID;
GLuint whitePlaneProgramID;
GLuint numIndices;

GLuint  vertexShaderID;
GLuint  fragmentShaderID;
GLuint  WhitePlanefragmentShaderID;

void MeGLWindow::sendDataToOpenGL() {
	ShapeData shape = ShapeGenerator::makeCube();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLuint indexArrayBufferID;
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	numIndices = shape.numIndices;
	shape.cleanup();

	GLuint transformationMatriuxBufferID;
	glGenBuffers(1, &transformationMatriuxBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, transformationMatriuxBufferID);

	mat4 projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f); // Projection matrix
	mat4 fullTransform[] = {
		projectionMatrix * meCamera->getWorldToViewMatrix() * glm::translate(mat4(),glm::vec3(0.0f,0.0f,-7.0f)) * glm::rotate(mat4(),90.0f,glm::vec3(1.0f, 0.5f, -0.3f)),
		projectionMatrix * meCamera->getWorldToViewMatrix() * glm::translate(mat4(),glm::vec3(0.0f,-0.3f,-6.0f)) * glm::rotate(mat4(),-90.0f,glm::vec3(1.0f, 0.5f, -0.3f)),
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransform), fullTransform, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
}


bool  MeGLWindow::checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}
bool  MeGLWindow::checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}


bool  MeGLWindow::checkProgramStatus(GLuint programID) {
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string  MeGLWindow::readShaderCode(const char* filename) {
	ifstream meInput(filename); {
		if (!meInput.good()) {
			cout << "File fail to load" << filename;
			exit(1);
		}

		return std::string(
			std::istreambuf_iterator<char>(meInput),
			std::istreambuf_iterator<char>()
		);
	}
}

void MeGLWindow::installShaders() {
	
	GLuint  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  WhitePlanevertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint  WhitePlanefragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string temp = readShaderCode("VertexShaderCode.glsl");
	const GLchar* adapter[1];

	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = readShaderCode("WhitePlaneVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(WhitePlanevertexShaderID, 1, adapter, 0);

	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	temp = readShaderCode("WhitePlaneFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(WhitePlanefragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	glCompileShader(WhitePlanefragmentShaderID);
	glCompileShader(WhitePlanevertexShaderID);

	if (!checkShaderStatus(vertexShaderID) 
		||!checkShaderStatus(fragmentShaderID) 
		|| !checkShaderStatus(WhitePlanefragmentShaderID)
		|| !checkShaderStatus(WhitePlanevertexShaderID)) {
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	
	whitePlaneProgramID = glCreateProgram();
	glAttachShader(whitePlaneProgramID, WhitePlanevertexShaderID);
	glAttachShader(whitePlaneProgramID, WhitePlanefragmentShaderID);
	glLinkProgram(whitePlaneProgramID);

	if (!checkProgramStatus(programID) || !checkProgramStatus(whitePlaneProgramID)) {
		return;
	}
}

void MeGLWindow::initializeGL() {
	
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}

void MeGLWindow::paintGL() {
	//Clean buffer before draw
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());
	//Draw a cube
	glUseProgram(programID);
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0,2);

	// Draw white plane using different shader
	glUseProgram(whitePlaneProgramID);
	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f); // Projection matrix
	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, -0.3f, -7.0f)); // push 4 away from camera
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(3.0f, 0.05f, 3.0f));
	mat4 fullTransformMatrix = projectionMatrix * meCamera->getWorldToViewMatrix() * modelTransformMatrix * modelRotateMatrix * modelScaleMatrix;
		
	GLint fullTransformMatrixUniformLocation = glGetUniformLocation(whitePlaneProgramID, "fullTransformMatrix");
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

}

MeGLWindow::MeGLWindow()
{
	meCamera = new MeCamera;
	setMouseTracking(true);
}


MeGLWindow::~MeGLWindow()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

void MeGLWindow::InitialValueSetter(GLfloat rotationValue)
{
	this->rotationValue = rotationValue;
}


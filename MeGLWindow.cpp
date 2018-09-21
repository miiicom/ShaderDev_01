
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <MeGLWindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <ShapeGenerator.h>
#include <vertex.h>
using namespace std;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRU = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
GLuint programID;
GLuint numIndices;

void sendDataToOpenGL() {
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
	}


bool checkStatus(
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
bool checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}


bool checkProgramStatus(GLuint programID) {
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* filename) {
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

void installShaders() {
	
	GLuint  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string temp = readShaderCode("VertexShaderCode.glsl");
	const GLchar* adapter[1];

	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || ! checkShaderStatus(fragmentShaderID)) {
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID)) {
		return;
	}

	glUseProgram(programID);
}

void MeGLWindow::initializeGL() {
	glewInit();
	sendDataToOpenGL();
	installShaders();
}

void MeGLWindow::paintGL() {
	//Clean buffer before draw
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());

	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, 0.0f, -4.0f)); // push 4 away from camera
	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f); // Projection matrix

	/*GLint x_MoveUniformLocation = glGetUniformLocation(programID, "xMove");
	GLint y_MoveUniformLocation = glGetUniformLocation(programID, "yMove");
	glUniform1f(x_MoveUniformLocation, +0.0f);
	glUniform1f(y_MoveUniformLocation, +0.0f);*/

	GLint modelTransMatUniformLoc = glGetUniformLocation(programID, "modelTransformMatrix");
	GLint projectMatUniformLoc = glGetUniformLocation(programID, "projectionMatrix");

	glUniformMatrix4fv(modelTransMatUniformLoc, 1, GL_FALSE, &modelTransformMatrix [0][0]);
	glUniformMatrix4fv(projectMatUniformLoc, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

void MeGLWindow::InjectUniformValue(GLfloat X_Offset, GLfloat Y_Offset) {
	
	X_Start += X_Offset;
	Y_Start += Y_Offset;
}

void MeGLWindow::InjectUniformValue_2(GLfloat X_Offset, GLfloat Y_Offset) {

	X_Start_2 += X_Offset;
	Y_Start_2 += Y_Offset;
}

MeGLWindow::MeGLWindow()
{
	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // push 4 away from camera
	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f); // Projection matrix
}


MeGLWindow::~MeGLWindow()
{
}

void MeGLWindow::InitialValueSetter(GLfloat X_Start, GLfloat Y_Start)
{
	this->X_Start = X_Start;
	this->Y_Start = Y_Start;
}


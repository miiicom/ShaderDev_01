
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <MeGLWindow.h>
#include <glm\glm.hpp>
#include <ShapeGenerator.h>
#include <vertex.h>
using namespace std;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRU = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
GLuint programID;

void sendDataToOpenGL() {
	ShapeData tri = ShapeGenerator::makeTriangle();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	//GLushort indices[] = { 0,1,2 };
	GLuint indexArrayBufferID;
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices, GL_STATIC_DRAW);
	tri.cleanup();
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


	// create input uniform value. They are the same for each draw call.
	//glm::vec3 dominatingColor(1.0f, 0.0f, 0.0f);
	//GLint dominatingColorUniformLocation = glGetUniformLocation(programID, "dominatingColor");
	//glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);// assign them

	//------------Flip------------
	//GLint yFlipUniformLocation =
	//	glGetUniformLocation(programID, "yFlip");
	//glUniform1f(yFlipUniformLocation, 1.0f);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	GLint x_MoveUniformLocation = glGetUniformLocation(programID, "xMove");
	glUniform1f(x_MoveUniformLocation, X_Start);

	

	GLint y_MoveUniformLocation = glGetUniformLocation(programID, "yMove");
	glUniform1f(y_MoveUniformLocation, Y_Start);

	printf("x_start is %f\n", X_Start);
	printf("y_start is %f\n", Y_Start);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	glUniform1f(x_MoveUniformLocation, X_Start_2+ 0.5f);
	glUniform1f(y_MoveUniformLocation, Y_Start_2 - 0.5f);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	//-----------CHANGE COLOR CODE-------------
	//dominatingColor.r = 0;
	//dominatingColor.b = 1;
	//glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
	//glUniform1f(yFlipUniformLocation, -1.0f);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	//-----------
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
	X_Start = +0.0f;
	Y_Start = +0.0f;

	X_Start_2 = +0.0f;
	Y_Start_2 = +0.0f;
}


MeGLWindow::~MeGLWindow()
{
}


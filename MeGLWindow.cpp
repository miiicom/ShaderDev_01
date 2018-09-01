
#include <GL/glew.h>
#include <iostream>
#include <MeGLWindow.h>
using namespace std;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

void sendDataToOpenGL() {
	GLfloat verts[]{

		-0.0f, -0.0f,
		+1.0f, +1.0f, +1.0f,

		+0.0f, +1.0f,
		+1.0f, +0.0f, +0.0f,

		+1.0f, -1.0f,
		+0.0f, +1.0f, +0.0f,

		-1.0f, -1.0f,
		+0.0f, +0.0f, +1.0f,

		-1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,

		+1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
	};
	/*
	GLfloat coordinate[]{
		-1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,

		+1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
	};*/
	
	GLuint vertexBufferID;

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	GLushort indices[] = { 0,1,2, 0,2,3, 0,3,1};
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType) {
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE) {
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
	/*
	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;*/

	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}


bool checkProgramStatus(GLuint programID){
	/*
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
	*/

	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

void installShaders() {
	
	GLuint  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	adapter[0] = vertexShaderCode;
	glShaderSource(vertexShaderID, 1, adapter, 0);
	adapter[0] = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || ! checkShaderStatus(fragmentShaderID)) {
		return;
	}

	GLuint programID = glCreateProgram();
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
	glViewport(0, 0, 512, 512);
	glDrawElements(GL_LINE_LOOP, 9, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 2);
}

MeGLWindow::MeGLWindow()
{
}


MeGLWindow::~MeGLWindow()
{
}


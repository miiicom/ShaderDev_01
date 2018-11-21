
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <MeGLWindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <ShapeGenerator.h>
#include <vertex.h>
#include <MeCamera.h>
#include <QtGui\qmouseevent>
using namespace std;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRU = 3;
const uint NUM_FLOATS_PER_VERTICE = 11;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

GLuint programID;
GLuint whitePlaneProgramID;
GLuint cubeIndices;
GLuint arrowIndices;
GLuint planeIndices;

GLuint  vertexShaderID;
GLuint  fragmentShaderID;
GLuint  WhitePlanefragmentShaderID;

GLuint cubeVertexBufferID;
GLuint cubeIndexBufferID;
GLuint ArrowVertexBufferID;
GLuint ArrowIndexBufferID;
GLuint PlaneVertexBufferID;
GLuint PlaneIndexBufferID;

GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint PlaneVertexArrayObjectID;

void MeGLWindow::sendDataToOpenGL() {
	ShapeData shape = ShapeGenerator::makeCube();

	glGenBuffers(1, &cubeVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &cubeIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	cubeIndices = shape.numIndices;

	shape = ShapeGenerator::makeArrow();

	glGenBuffers(1, &ArrowVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, ArrowVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ArrowIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ArrowIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	arrowIndices = shape.numIndices;

	GLuint PlaneDimension = 10;

	shape = ShapeGenerator::makePlane(PlaneDimension);
	glGenBuffers(1, &PlaneVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &PlaneIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PlaneIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	planeIndices = shape.numIndices;

	shape.cleanup();
	//Create QImage obj
	const char * texName = "normalMap";
	QImage normalMap = loadTexture(texName);
	// send Image to OpenGL
	glActiveTexture(GL_TEXTURE0);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, normalMap.width(),
		normalMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		normalMap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

}

void MeGLWindow::setupVertexArrays()
{
	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 9));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);

	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, ArrowVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 9));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ArrowIndexBufferID);

	glBindVertexArray(PlaneVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 9));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PlaneIndexBufferID);
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
	setupVertexArrays();
	installShaders();
}

void MeGLWindow::mouseMoveEvent(QMouseEvent * event)
{
	//printf("moving in QGLWidget\n");
	event->ignore();// the key!!!
}

QImage MeGLWindow::loadTexture(const char * texName)
{
	return QGLWidget::convertToGLFormat(QImage(texName, "PNG"));;
}


glm::vec2 MeGLWindow::Calculate2DSpriteLoc(GLfloat time, GLint XSegNum, GLint YSegNum)
{
	GLfloat UnitDistanceX = 1.0f / (float)XSegNum;
	GLfloat UnitDistanceY = 1.0f / (float)YSegNum;
	GLfloat SpriteNum = (int)time % (XSegNum * YSegNum);
	printf(" SpriteNum is %f\n", SpriteNum);

	GLfloat XCellNum = (int)SpriteNum / XSegNum;
	GLfloat YCellNum = (int)SpriteNum % YSegNum;
	printf(" Sprite  Choice is %f in X, %f in Y \n", XCellNum, YCellNum);
	GLfloat SpriteUVOffsetX = XCellNum * UnitDistanceX;
	GLfloat SpriteUVOffsetY = YCellNum * UnitDistanceY;
	printf(" Sprite offset is %f in X, %f in Y", SpriteUVOffsetX, SpriteUVOffsetY);
	return glm::vec2(SpriteUVOffsetX, SpriteUVOffsetY);
}

void MeGLWindow::paintGL() {
	mat4 projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.01f, 50.0f); // Projection matrix
	mat4 fullTransform[] = {
		projectionMatrix * meCamera->getWorldToViewMatrix() * glm::translate(mat4(),glm::vec3(0.0f,0.0f,-7.0f)) * glm::rotate(mat4(),90.0f,glm::vec3(1.0f, 0.5f, -0.3f)),
		projectionMatrix * meCamera->getWorldToViewMatrix() * glm::translate(mat4(),glm::vec3(0.0f,-0.3f,-6.0f)) * glm::rotate(mat4(),-90.0f,glm::vec3(1.0f, 0.5f, -0.3f)),
	};

	//glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransform) * 2, fullTransform, GL_DYNAMIC_DRAW);
	//Clean buffer before draw
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());

	glUseProgram(programID);
	//Draw cube in old fashion way
	// in here rebind for cube
	glBindVertexArray(cubeVertexArrayObjectID);

	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, 0.3f, -7.0f));
	modelRotateMatrix = glm::rotate(mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	mat4 ModelToWorldMatrix = modelTransformMatrix * modelRotateMatrix *  modelScaleMatrix;
	mat4 Cube1FullTransformMatrix = projectionMatrix * meCamera->getWorldToViewMatrix() *ModelToWorldMatrix;

	//In here find all Uniforms and assign them
	GLint CubefullTransformMatrixUniformLocation = glGetUniformLocation(programID, "modelToProjectionMatrix");
	glUniformMatrix4fv(CubefullTransformMatrixUniformLocation, 1, GL_FALSE, &Cube1FullTransformMatrix[0][0]);
	GLint ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLightUniform");
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	GLuint pointLightUniformLocation = glGetUniformLocation(programID, "pointLightPositionWorld");
	glUniform3fv(pointLightUniformLocation, 1, &pointLightPosition[0]);
	GLuint eyeUniformLocation = glGetUniformLocation(programID, "eyePositionWorld");
	glm::vec3 eyePosition = meCamera->getPosition();
	glUniform3fv(eyeUniformLocation, 1,&eyePosition[0]);
	GLuint modelTransformMatrixUniformLocation = glGetUniformLocation(programID, "modelToWorldTransMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &ModelToWorldMatrix[0][0]);
	

	//glDrawElements(GL_TRIANGLES, cubeIndices, GL_UNSIGNED_SHORT, 0);
	//Draw arrow 
	glBindVertexArray(arrowVertexArrayObjectID);

	modelTransformMatrix = glm::translate(mat4(), glm::vec3(3.0f,0.0f, -6.0f));
	modelRotateMatrix = glm::rotate(mat4(), 45.0f, glm::vec3(0.0f, 0.5f, 0.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(3.0f, 0.5f, 1.0f));
	ModelToWorldMatrix = modelTransformMatrix* modelRotateMatrix *  modelScaleMatrix;
	mat4 Cube2FullTransformMatrix = projectionMatrix * meCamera->getWorldToViewMatrix() *ModelToWorldMatrix;
	
	glUniformMatrix4fv(CubefullTransformMatrixUniformLocation, 1, GL_FALSE, &Cube2FullTransformMatrix[0][0]);
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	glUniform3fv(pointLightUniformLocation, 1, &pointLightPosition[0]);
	glUniform3fv(eyeUniformLocation, 1, &eyePosition[0]);
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &ModelToWorldMatrix[0][0]);
	//glDrawElements(GL_TRIANGLES,arrowIndices, GL_UNSIGNED_SHORT, 0);

	// Draw white plane using different shader
	glUseProgram(whitePlaneProgramID);
	// in here rebind for cube
	glBindVertexArray(PlaneVertexArrayObjectID);

	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f); // Projection matrix
	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, -1.0f, -5.0f)); // push 4 away from camera
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(1.0f,1.0f, 1.0f));
	ModelToWorldMatrix = modelTransformMatrix* modelRotateMatrix *  modelScaleMatrix;
	mat4 fullTransformMatrix = projectionMatrix * meCamera->getWorldToViewMatrix() *ModelToWorldMatrix;
		
	GLint fullTransformMatrixUniformLocation = glGetUniformLocation(whitePlaneProgramID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	ambientLightUniformLocation = glGetUniformLocation(whitePlaneProgramID, "ambientLightUniform");
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	pointLightUniformLocation = glGetUniformLocation(whitePlaneProgramID, "pointLightPositionWorld");
	glUniform3fv(pointLightUniformLocation, 1, &pointLightPosition[0]);
	eyeUniformLocation = glGetUniformLocation(whitePlaneProgramID, "eyePositionWorld");
	glUniform3fv(eyeUniformLocation, 1, &eyePosition[0]);
	modelTransformMatrixUniformLocation = glGetUniformLocation(whitePlaneProgramID, "modelToWorldTransMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]);
	GLuint normalTextureUniformLocation = glGetUniformLocation(whitePlaneProgramID, "normalTextureTC");
	glUniform1i(normalTextureUniformLocation, 0);
	GLuint timeUniformLocation = glGetUniformLocation(whitePlaneProgramID, "time");
	glUniform1f(timeUniformLocation, this->time);
	glDrawElements(GL_TRIANGLES, planeIndices, GL_UNSIGNED_SHORT, 0);
	printf("time is %f", this->time);
}

MeGLWindow::MeGLWindow()
{
	meCamera = new MeCamera;
	ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLightPosition = glm::vec3(0.0f, 0.2f,-5.0f);
	time = -1.0f;
}


MeGLWindow::~MeGLWindow()
{
	glDeleteBuffers(1, &cubeVertexBufferID);
	glDeleteBuffers(1, &ArrowIndexBufferID);
	glUseProgram(0);
	glDeleteProgram(programID);
}

void MeGLWindow::InitialValueSetter(GLfloat rotationValue)
{
	this->rotationValue = rotationValue;
}


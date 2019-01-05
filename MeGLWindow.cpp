
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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

const uint NUM_VERTICES_PER_TRU = 3;
const uint NUM_FLOATS_PER_VERTICE = 3+4+3+2+3;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

GLuint programID;
GLuint PBRProgramID;
GLuint EqtangToCubeProgramID;
GLuint cubeIndices;
GLuint arrowIndices;
GLuint SphereIndices;
GLuint planeIndices;
GLuint framebuffer;
GLuint SphereVertexBufferID;
GLuint SphereIndexBufferID;
GLuint PlaneVertexBufferID;
GLuint PlaneIndexBufferID;
GLuint CubeVertexBufferID;
GLuint CubeIndexBufferID;

GLuint SphereVertexArrayObjectID;
GLuint PlaneVertexArrayObjectID;
GLuint CubeVertexArrayObjectID;

GLuint environemntRenderTexture;

void MeGLWindow::sendDataToOpenGL() {
	GLuint PlaneDimension = 60;

	ShapeData shape = ShapeGenerator::makeSphere(PlaneDimension);
	glGenBuffers(1, &SphereVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, SphereVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &SphereIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SphereIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	SphereIndices = shape.numIndices;

	shape = ShapeGenerator::makefillerQuard();
	glGenBuffers(1, &PlaneVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &PlaneIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PlaneIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	planeIndices = shape.numIndices;

	shape = ShapeGenerator::makeCube();
	glGenBuffers(1, &CubeVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, CubeVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &CubeIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	cubeIndices = shape.numIndices;

	shape.cleanup();
	//Create QImage obj
	const char * texName = "texture/rustediron2_basecolor.png";
	QImage normalMap = loadTexture(texName);
	// send Normal Image to OpenGL
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
	//Create another QImage obj
	texName = "texture/rustediron2_normal.png";
	QImage AlbedoMap = loadTexture(texName);
	//send Albedo color to OpenGL
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AlbedoMap.width(),
		AlbedoMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		AlbedoMap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	//Create another QImage obj
	texName = "texture/rustediron2_roughness.png";
	QImage RoughnessMap = loadTexture(texName);
	//send Albedo color to OpenGL
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RoughnessMap.width(),
		RoughnessMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		RoughnessMap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	//Create another QImage obj
	texName = "texture/rustediron2_metallic.png";
	QImage metallicMap = loadTexture(texName);
	//send metallic color to OpenGL
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, metallicMap.width(),
		metallicMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		metallicMap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	//Create another QImage obj
	texName = "texture/rustediron2_ao.png";
	QImage aoMap = loadTexture(texName);
	//send metallic color to OpenGL
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aoMap.width(),
		aoMap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		aoMap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	float *data  = stbi_loadf("texture/Newport_Loft_Ref.hdr", &width, &height, &nrComponents, 0);
	GLuint hdrTexture;
	
	if (data) {
		glGenTextures(1, &hdrTexture);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, hdrTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		stbi_image_free(data);
	}
	else {
		printf("fail to load hdr");
	}
}

void MeGLWindow::setupVertexArrays()
{
	glGenVertexArrays(1, &SphereVertexArrayObjectID);

	glBindVertexArray(SphereVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, SphereVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 7));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 10));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 12));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SphereIndexBufferID);

	glGenVertexArrays(1, &PlaneVertexArrayObjectID);

	glBindVertexArray(PlaneVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 7));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 10));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 12));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PlaneIndexBufferID);

	glBindVertexArray(CubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, CubeVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 7));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 10));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * NUM_FLOATS_PER_VERTICE, (void*)(sizeof(float) * 12));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeIndexBufferID);
}

void MeGLWindow::setupFrameBuffer()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	unsigned int renderBufferObject;
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 1024);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

	//To make framebuffer render to a texture I need to generate a texture object first

	glGenTextures(1, &environemntRenderTexture);
	glActiveTexture(GL_TEXTURE5); // Use texture unit 5
	glBindTexture(GL_TEXTURE_CUBE_MAP, environemntRenderTexture);
	for (int i = 0; i < 6; ++i)
	{
		// note that we store each face with 16 bit floating point values
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
			1024, 1024, 0, GL_RGB, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0); //bind back to default

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, environemntRenderTexture, 0);
	// use render Buffer object for depth test
	

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	GLuint  PBRvertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint  PBRfragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint  EqToCubevertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint  EqToCubefragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	string temp = readShaderCode("VertexShaderCode.glsl");
	const GLchar* adapter[1];

	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	temp = readShaderCode("PBR_vertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(PBRvertexShaderID, 1, adapter, 0);

	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	temp = readShaderCode("PBR_fragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(PBRfragmentShaderID, 1, adapter, 0);

	temp = readShaderCode("EquTanToCubeVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(EqToCubevertexShaderID, 1, adapter, 0);

	temp = readShaderCode("EquTanToCubeFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(EqToCubefragmentShader, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	glCompileShader(PBRfragmentShaderID);
	glCompileShader(PBRvertexShaderID);
	glCompileShader(EqToCubevertexShaderID);
	glCompileShader(EqToCubefragmentShader);

	if (!checkShaderStatus(vertexShaderID) 
		||!checkShaderStatus(fragmentShaderID) 
		|| !checkShaderStatus(PBRfragmentShaderID)
		|| !checkShaderStatus(PBRvertexShaderID)
		|| !checkShaderStatus(EqToCubevertexShaderID)
		|| !checkShaderStatus(EqToCubefragmentShader)
		) {
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	
	PBRProgramID = glCreateProgram();
	glAttachShader(PBRProgramID, PBRvertexShaderID);
	glAttachShader(PBRProgramID, PBRfragmentShaderID);
	glLinkProgram(PBRProgramID);

	EqtangToCubeProgramID = glCreateProgram();
	glAttachShader(EqtangToCubeProgramID, EqToCubevertexShaderID);
	glAttachShader(EqtangToCubeProgramID, EqToCubefragmentShader);
	glLinkProgram(EqtangToCubeProgramID);
	if (!checkProgramStatus(programID) || !checkProgramStatus(PBRProgramID) || !checkProgramStatus(EqtangToCubeProgramID)) {
		return;
	}
}

void MeGLWindow::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	setupFrameBuffer();
	sendDataToOpenGL();
	setupVertexArrays();
	installShaders();
}

void MeGLWindow::mouseMoveEvent(QMouseEvent * event)
{
	//printf("moving in QGLWidget\n");
	event->ignore();// the key!!!
}

void MeGLWindow::MoveLightLight(glm::vec3 pointlightOffset)
{
	this->pointLightPosition += pointlightOffset;
}

QImage MeGLWindow::loadTexture(const char * texName)
{
	return QGLWidget::convertToGLFormat(QImage(texName, "PNG"));
}


glm::vec2 MeGLWindow::Calculate2DSpriteLoc(GLfloat time, GLint XSegNum, GLint YSegNum)
{
	printf("time is %f\n", time);
	GLfloat UnitDistanceX = 1.0f / (float)XSegNum;
	GLfloat UnitDistanceY = 1.0f / (float)YSegNum;
	GLfloat SpriteNum = (int)(time) % (XSegNum * YSegNum);
	printf(" SpriteNum is %f\n", SpriteNum);

	GLfloat XCellNum = (int)SpriteNum / XSegNum;
	GLfloat YCellNum = (int)SpriteNum % YSegNum;
	printf(" Sprite  Choice is %f in X, %f in Y \n", XCellNum, YCellNum);
	GLfloat SpriteUVOffsetX = XCellNum * UnitDistanceX;
	GLfloat SpriteUVOffsetY = YCellNum * UnitDistanceY;
	printf(" Sprite offset is %f in X, %f in Y", SpriteUVOffsetX, SpriteUVOffsetY);
	this->spriteOffset = glm::vec2(SpriteUVOffsetX, SpriteUVOffsetY);
	return glm::vec2(SpriteUVOffsetX, SpriteUVOffsetY);
}

void MeGLWindow::paintGL() {
	// render environment texture first
	
	glm::mat4 renderProjectionMatrix = glm::perspective(glm::radians(90.0f), ((float)width()) / height(), 0.01f, 50.0f);
	glm::mat4 renderVires[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

	glUseProgram(EqtangToCubeProgramID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	GLuint EqTangToCubeTextureUniformLoc = glGetUniformLocation(EqtangToCubeProgramID, "equirectangularMap");
	glUniform1i(EqTangToCubeTextureUniformLoc, 6);
	GLuint EqTangToCubeProjectionUniformLoc = glGetUniformLocation(EqtangToCubeProgramID, "viewToProjectionMatrix");
	glUniformMatrix4fv(EqTangToCubeProjectionUniformLoc, 1, GL_FALSE, &renderProjectionMatrix[0][0]);
	GLuint EqTangToCubeViewUniformLoc = glGetUniformLocation(EqtangToCubeProgramID, "worldToViewMatrix");
	glViewport(0, 0, width(), height());
	for ( int i = 0; i < 6; ++i)
	{
		glUniformMatrix4fv(EqTangToCubeViewUniformLoc, 1, GL_FALSE, &renderVires[i][0][0]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, environemntRenderTexture, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, cubeIndices, GL_UNSIGNED_SHORT, 0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	mat4 projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.01f, 50.0f); // Projection matrix
	//render things into my frame buffer																								// bind to framebuffer and draw scene as we normally would to color texture 
	/*glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);*/
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(PBRProgramID);
	// in here rebind for cube
	glBindVertexArray(SphereVertexArrayObjectID);
	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 50.0f); // Projection matrix
	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // push 4 away from camera
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(1.0f,1.0f, 1.0f));
	mat4 ModelToWorldMatrix = modelTransformMatrix* modelRotateMatrix *  modelScaleMatrix;
	mat4 ModelToViewMatrix = meCamera->getWorldToViewMatrix() * ModelToWorldMatrix;
	mat4 fullTransformMatrix = projectionMatrix * ModelToViewMatrix;

	// bind texture
	GLint AlbedoUniformLoc = glGetUniformLocation(PBRProgramID, "albedoMap");
	glUniform1i(AlbedoUniformLoc, 0);
	GLint NormalUniformLoc = glGetUniformLocation(PBRProgramID, "normalMap");
	glUniform1i(NormalUniformLoc, 1);
	GLint RoughnessUniformLoc = glGetUniformLocation(PBRProgramID, "roughnessMap");
	glUniform1i(RoughnessUniformLoc, 2);
	GLint MetallicUniformLoc = glGetUniformLocation(PBRProgramID, "metallicMap");
	glUniform1i(MetallicUniformLoc, 3);
	GLint AoUniformLoc = glGetUniformLocation(PBRProgramID, "aoMap");
	glUniform1i(AoUniformLoc, 4);


		
	GLint fullTransformMatrixUniformLocation = glGetUniformLocation(PBRProgramID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	GLint modelToWorldMatrixUniformLoc = glGetUniformLocation(PBRProgramID, "modelToWorldMatrix");
	glUniformMatrix4fv(modelToWorldMatrixUniformLoc, 1, GL_FALSE,&ModelToWorldMatrix[0][0]);
	glm::vec3 cameraDirection = meCamera->getPosition();
	GLint cameraDirectionUniformLoc = glGetUniformLocation(PBRProgramID, "CameraDirectionWorld");
	glUniform3fv(cameraDirectionUniformLoc, 1, &cameraDirection[0]);
	GLint lightpositionUniformLoc = glGetUniformLocation(PBRProgramID,"lightPositionWorld");
	glUniform3fv(lightpositionUniformLoc, 1, &pointLightPosition[0]);


	glm::vec3 albedoColor = glm::vec3(-1.0f, -1.0f, -1.0f);
	GLint albedoUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.albedo");
	glUniform3fv(albedoUniformLoc, 1,&albedoColor[0]);
	GLint metallicUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.metallic");
	glUniform1f(metallicUniformLoc,-1.0f);
	GLint roughnesslicUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.roughness");
	glUniform1f(roughnesslicUniformLoc, -1.0f);
	GLint aoUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.AO");
	glUniform1f(aoUniformLoc, -1.0f);

	// Draw first metallic ball with texture
	glDrawElements(GL_TRIANGLES, SphereIndices, GL_UNSIGNED_SHORT, 0);

	modelTransformMatrix = glm::translate(mat4(), glm::vec3(3.0f, 0.0f, 0.0f)); // push 4 away from camera
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelToWorldMatrix = modelTransformMatrix * modelRotateMatrix *  modelScaleMatrix;
	ModelToViewMatrix = meCamera->getWorldToViewMatrix() * ModelToWorldMatrix;
	fullTransformMatrix = projectionMatrix * ModelToViewMatrix;

	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLoc, 1, GL_FALSE, &ModelToWorldMatrix[0][0]);
	albedoColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glUniform3fv(albedoUniformLoc, 1, &albedoColor[0]);
	glUniform1f(metallicUniformLoc, 0.01f);
	glUniform1f(roughnesslicUniformLoc, 1.0f);
	glUniform1f(aoUniformLoc, 1.0f);

	glDrawElements(GL_TRIANGLES, SphereIndices, GL_UNSIGNED_SHORT, 0);
	//test cube
	/*glUseProgram(EqtangToCubeProgramID);
	glBindVertexArray(CubeVertexArrayObjectID);

	modelTransformMatrix = glm::translate(mat4(), glm::vec3(-3.0f, 0.0f, 0.0f));
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelToWorldMatrix = modelTransformMatrix * modelRotateMatrix *  modelScaleMatrix;
	ModelToViewMatrix = meCamera->getWorldToViewMatrix() * ModelToWorldMatrix;
	fullTransformMatrix = projectionMatrix * ModelToViewMatrix;

	fullTransformMatrixUniformLocation = glGetUniformLocation(EqtangToCubeProgramID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	GLuint EqToCubeUniformLocation = glGetUniformLocation(EqtangToCubeProgramID, "equirectangularMap");
	glUniform1i(EqToCubeUniformLocation, 6);
	glDrawElements(GL_TRIANGLES, cubeIndices, GL_UNSIGNED_SHORT, 0);*/

	// bind back to default framebuffer
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glUseProgram(programID);
	glBindVertexArray(PlaneVertexArrayObjectID);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	GLuint framebufferTextureUniformLoc = glGetUniformLocation(programID, "frameBufferTexture");
	glUniform1i(framebufferTextureUniformLoc, 5);

	glDrawElements(GL_TRIANGLES, planeIndices, GL_UNSIGNED_SHORT, 0);*/
}

MeGLWindow::MeGLWindow()
{
	meCamera = new MeCamera;
	spriteOffset = glm::vec2(0.0f, 0.0f);
	ambientLight = glm::vec3(+0.1f, +0.2f, +0.25f);
	pointLightPosition = glm::vec3(+0.0f,+1.2f,+0.0f);
	time = 0.0f;
}


MeGLWindow::~MeGLWindow()
{
	glDeleteBuffers(1, &SphereVertexBufferID);
	glUseProgram(0);
	glDeleteProgram(programID);
}

void MeGLWindow::InitialValueSetter(GLfloat rotationValue)
{
	this->rotationValue = rotationValue;
}


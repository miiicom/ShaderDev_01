
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
const uint NUM_FLOATS_PER_VERTICE = 3+4+3+2+3;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

GLuint programID;
GLuint PBRProgramID;
GLuint cubeIndices;
GLuint arrowIndices;
GLuint SphereIndices;
GLuint planeIndices;
GLuint framebuffer;
GLuint SphereVertexBufferID;
GLuint SphereIndexBufferID;
GLuint PlaneVertexBufferID;
GLuint PlaneIndexBufferID;


GLuint teapotVertexBufferID;
GLuint teapotIndexBufferID;
GLuint teapotVertexArrayObjectID;
GLuint teapotIndices;

GLuint SphereVertexArrayObjectID;
GLuint PlaneVertexArrayObjectID;

GLuint framebufferTexture;

void MeGLWindow::sendDataToOpenGL() {
	GLuint PlaneDimension = 30;

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

	std::ostream *outStream = &std::cout;
	if (teapot.LoadFromFileObj("object/teapot.obj", TRUE, outStream)) {
		printf("load success");
	}
	else {
		printf("load fail");
	}

	//Load teapot

	std::vector<cyPoint3f> teapotVertices;
	for (int i = 0; i < teapot.NV(); i++) {
		teapotVertices.push_back(teapot.V(i));
	}

	std::vector<cyPoint3f> teapotColors;
	for (int i = 0; i < teapot.NV(); i++) {
		teapotColors.push_back(teapot.VN(i));
	}

	std::vector<cyPoint3f> teapotNormals;
	for (int i = 0; i < teapot.NV(); i++) {
		teapotNormals.push_back(teapot.VN(i));
	}

	//std::vector<cyPoint3f> teapotUVs;
	//for (int i = 0; i < teapot.NVT(); i++) {
	//	teapotUVs.push_back(teapot.VT(i));
	//}

	std::vector<cyPoint3f> teapotUVs;
	teapotUVs.resize(teapot.NV());
	for (int i = 0; i < teapot.NF(); i++) {
		for (int j = 0; j < 3; j++) {
			teapotUVs[teapot.F(i).v[j]] = cyPoint3f(teapot.VT(teapot.FT(i).v[j]).x,
				teapot.VT(teapot.FT(i).v[j]).y, 0);
		}
	}

	std::vector<cyPoint3f> teapotInfos;
	teapotInfos.insert(teapotInfos.end(), teapotVertices.begin(), teapotVertices.end());
	teapotInfos.insert(teapotInfos.end(), teapotColors.begin(), teapotColors.end());
	teapotInfos.insert(teapotInfos.end(), teapotNormals.begin(), teapotNormals.end());
	teapotInfos.insert(teapotInfos.end(), teapotUVs.begin(), teapotUVs.end());

	printf("teapot vertices buffer is %d size large\n", teapotVertices.size());
	printf("teapot has %d vertices\n", teapot.NV());

	printf("\nthe num of vertes is %d\n", teapot.NV());
	printf("\nthe num of NORMAL is %d\n", teapot.NV());
	printf("\nthe num of FACE is %d\n", teapot.NF());
	printf("\nthe num of uv is %d\n", teapot.NVT());

	glGenBuffers(1, &teapotVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, teapotVertexBufferID);
	// read vertex position info only
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, teapot.NF() * sizeof(unsigned int) *3 , &teapot.F(0), GL_STATIC_DRAW);
	// read vertex information from a vector
	glBufferData(GL_ARRAY_BUFFER, (teapot.NV()*2 + teapot.NVN() + teapot.NV()) * sizeof(cyPoint3f), &teapotInfos[0], GL_STATIC_DRAW);


	glGenBuffers(1, &teapotIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, teapotIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, teapot.NF() * sizeof(unsigned int) * 3, &teapot.F(0), GL_STATIC_DRAW);
	teapotIndices = teapot.NF() * 3;



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

	glGenVertexArrays(1, &teapotVertexArrayObjectID);

	glBindVertexArray(teapotVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, teapotVertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(cyPoint3f) * teapot.NV()));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(cyPoint3f) * teapot.NV()*2));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(cyPoint3f) * teapot.NVN() + sizeof(cyPoint3f) * teapot.NV()*2));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, teapotIndexBufferID);
}

void MeGLWindow::setupFrameBuffer()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	//To make framebuffer render to a texture I need to generate a texture object first

	
	glGenTextures(1, &framebufferTexture);
	//glActiveTexture(GL_TEXTURE5); // Use texture unit 5
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0); //bind back to default

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);
	// use render Buffer object for depth test
	unsigned int renderBufferObject;
	glGenRenderbuffers(1, &renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 1024);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

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

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	glCompileShader(PBRfragmentShaderID);
	glCompileShader(PBRvertexShaderID);

	if (!checkShaderStatus(vertexShaderID) 
		||!checkShaderStatus(fragmentShaderID) 
		|| !checkShaderStatus(PBRfragmentShaderID)
		|| !checkShaderStatus(PBRvertexShaderID)) {
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

	if (!checkProgramStatus(programID) || !checkProgramStatus(PBRProgramID)) {
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
	mat4 projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.01f, 50.0f); // Projection matrix
	//render things into my frame buffer																								// bind to framebuffer and draw scene as we normally would to color texture 
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width(), height());

	glUseProgram(PBRProgramID);
	// in here rebind for cube
	glBindVertexArray(teapotVertexArrayObjectID);
	projectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 50.0f); // Projection matrix
	modelTransformMatrix = glm::translate(mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // push 4 away from camera
	modelRotateMatrix = glm::rotate(mat4(), +0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	modelScaleMatrix = glm::scale(mat4(), glm::vec3(0.1f,0.1f, 0.1f));
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
	GLint modelToWorldMatrixUniformLoc = glGetUniformLocation(PBRProgramID, "modelToWorldMatrix");
	glm::vec3 cameraDirection = meCamera->getPosition();
	GLint cameraDirectionUniformLoc = glGetUniformLocation(PBRProgramID, "CameraDirectionWorld");
	glUniform3fv(cameraDirectionUniformLoc, 1, &cameraDirection[0]);
	GLint lightpositionUniformLoc = glGetUniformLocation(PBRProgramID,"lightPositionWorld");
	glUniform3fv(lightpositionUniformLoc, 1, &pointLightPosition[0]);
	glm::vec3 albedo = glm::vec3(-1.0, -1.0,-1.0);
	GLint albedormLoc = glGetUniformLocation(PBRProgramID, "parameter.albedo");
	glUniform3fv(albedormLoc, 1, &albedo[0]);
	GLint metallicUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.metallic");
	
	GLint roughnesslicUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.roughness");
	
	GLint aoUniformLoc = glGetUniformLocation(PBRProgramID, "parameter.AO");
	glUniform1f(aoUniformLoc, -1.0f);

	for (int i = 0; i < 1; ++i) { // i  for roughness and  x movement
		for (int j = 0; j < 1; ++j) { // j for metallic and y movement
			modelTransformMatrix = glm::translate(mat4(), glm::vec3(2.2f * (float)i, 2.2f * (float)j, 0.0f));
			ModelToWorldMatrix = modelTransformMatrix * modelRotateMatrix *  modelScaleMatrix;
			ModelToViewMatrix = meCamera->getWorldToViewMatrix() * ModelToWorldMatrix;
			fullTransformMatrix = projectionMatrix * ModelToViewMatrix;

			glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
			glUniformMatrix4fv(modelToWorldMatrixUniformLoc, 1, GL_FALSE, &ModelToWorldMatrix[0][0]);
			//glUniform1f(metallicUniformLoc,(float)j * (1.0f/7.0f));
			//glUniform1f(roughnesslicUniformLoc, (float)i * (1.0f / 7.0f));

			glUniform1f(metallicUniformLoc, -1);
			glUniform1f(roughnesslicUniformLoc, -1);
			glDrawElements(GL_TRIANGLES, teapotIndices, GL_UNSIGNED_INT, 0);
		}
	}
	
	


	// bind back to default framebuffer
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);


	//glUseProgram(programID);
	//glBindVertexArray(PlaneVertexArrayObjectID);
	//glActiveTexture(GL_TEXTURE5);
	//glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	//GLuint framebufferTextureUniformLoc = glGetUniformLocation(programID, "frameBufferTexture");
	//glUniform1i(framebufferTextureUniformLoc, 5);

	//glDrawElements(GL_TRIANGLES, planeIndices, GL_UNSIGNED_SHORT, 0);
}

MeGLWindow::MeGLWindow()
{
	meCamera = new MeCamera;
	spriteOffset = glm::vec2(0.0f, 0.0f);
	ambientLight = glm::vec3(+0.1f, +0.2f, +0.25f);
	pointLightPosition = glm::vec3(+1.0f,+1.0f,+2.0f);
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


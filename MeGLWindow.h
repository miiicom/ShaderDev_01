#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <GL\glew.h>
#include<QtOpenGL\qglwidget>
#include <glm\glm.hpp>
#include <String>
#include <MeCamera.h>

using glm::mat4;
class MeGLWindow : public QGLWidget
{
protected:
	void paintGL();
	void sendDataToOpenGL();
	bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string readShaderCode(const char * filename);
	void installShaders();
	void initializeGL();
public:
	MeGLWindow();
	~MeGLWindow();
	void InitialValueSetter(GLfloat rotationValue);

private:
	GLfloat rotationValue;

	mat4 modelTransformMatrix;
	mat4 modelRotateMatrix;
	mat4 modelScaleMatrix;
	mat4 projectionMatrix;

	MeCamera * meCamera;
};

#endif

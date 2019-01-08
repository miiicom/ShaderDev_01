#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <GL\glew.h>
#include<QtOpenGL\qglwidget>
#include <glm\glm.hpp>
#include <String>
#include <MeCamera.h>
#include <Qt\qimage.h>
using glm::mat4;
class MeGLWindow : public QGLWidget
{
protected:
	void paintGL();
	void sendDataToOpenGL();
	void setupVertexArrays();
	void setupFrameBuffer();
	bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string readShaderCode(const char * filename);
	void installShaders();
	void initializeGL();
	void mouseMoveEvent(QMouseEvent *event) ;
	QImage loadTexture(const char * texName);
	void RenderToFrameBuffer();

	
public:
	MeGLWindow();
	~MeGLWindow();
	void InitialValueSetter(GLfloat rotationValue);
	MeCamera * meCamera;
	GLfloat time;
	glm::vec2 Calculate2DSpriteLoc(GLfloat time, GLint XSegNum, GLint YSegNum);
	void MoveLightLight(glm::vec3 pointlightOffset);

private:
	GLfloat rotationValue;

	mat4 modelTransformMatrix;
	mat4 modelRotateMatrix;
	mat4 modelScaleMatrix;
	mat4 projectionMatrix;

	glm::vec2 spriteOffset;
	glm::vec3 ambientLight;
	glm::vec3 pointLightPosition;
	
};

#endif

#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW

#include<QtOpenGL\qglwidget>
#include <glm\glm.hpp>

using glm::mat4;
class MeGLWindow : public QGLWidget
{
protected:
	void paintGL();
	void initializeGL();
public:
	MeGLWindow();
	~MeGLWindow();
	void InitialValueSetter(GLfloat rotationValue);

private:
	GLfloat rotationValue;

	mat4 modelTransformMatrix;
	mat4 modelRotateMatrix;
	mat4 projectionMatrix;
};

#endif

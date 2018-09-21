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
	void InitialValueSetter(GLfloat X_Start, GLfloat Y_Start);
	void InjectUniformValue(GLfloat X_Offset, GLfloat Y_Offset);
	void InjectUniformValue_2(GLfloat X_Offset, GLfloat Y_Offset);
private:
	GLfloat X_Start;
	GLfloat Y_Start;

	GLfloat X_Start_2;
	GLfloat Y_Start_2;

	mat4 modelTransformMatrix;
	mat4 projectionMatrix;
};

#endif

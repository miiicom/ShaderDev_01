#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW

#include<QtOpenGL\qglwidget>
#include <glm\glm.hpp>
class MeGLWindow : public QGLWidget
{
protected:
	void paintGL();
	void initializeGL();

public:
	MeGLWindow();
	~MeGLWindow();
	void InjectUniformValue(GLint X_Offset, GLint Y_Offset);
	
private:
	GLint X_Start;
	GLint Y_Start;
};

#endif

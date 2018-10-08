#pragma once
#include <QtGui\qwidget.h>
#include <Qt\qevent.h>
#include <MeGLWindow.h>
#include <glm\glm.hpp>
class MeWidget : public QWidget
{
public:
	MeWidget();
	~MeWidget();

	glm::vec3 scale(GLfloat scale, glm::vec3 input);
	glm::vec3 multiply(glm::vec3 left, glm::vec3 right);
	glm::vec3 subtraction3d(glm::vec3 left, glm::vec3 right);
	glm::vec2 subtraction2d(glm::vec2 left, glm::vec2 right);
	glm::vec3 perpCw3d(glm::vec3 input);
	glm::vec3 perpCc3d(glm::vec3 input);
	GLfloat dot2d(glm::vec2 input1, glm::vec2 input2);
	GLfloat dot3d(glm::vec3 input1, glm::vec3 input2);
	GLfloat vecMagnitude(glm::vec3 input);
	glm::vec3 normalize(glm::vec3 input);

	void handleBoundaries();

protected:
	void keyPressEvent(QKeyEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEnvet(QMouseEvent *event);
	void timerEvent(QTimerEvent *event);

private:
	MeGLWindow * myGLWindow;
	GLfloat rotationValue;
	QPoint dragStartPosition;
	bool IsPressing;
};




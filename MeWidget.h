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
	glm::vec3 subtraction3d(glm::vec3 left, glm::vec3 right);
	glm::vec2 subtraction2d(glm::vec2 left, glm::vec2 right);
	glm::vec2 perpCw2d(glm::vec2 input);
	glm::vec2 perpCc2d(glm::vec2 input);

protected:
	void keyPressEvent(QKeyEvent *);
	void timerEvent(QTimerEvent *event);

private:
	MeGLWindow * myGLWindow;
	glm::vec2 FlyingVector;
};




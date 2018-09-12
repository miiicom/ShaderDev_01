#include "MeWidget.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <Qt\qevent.h>
#include <MeGLwindow.h>
#include <glm\glm.hpp>


MeWidget::MeWidget()
{
	myGLWindow = new MeGLWindow();

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

	startTimer(20);

	FlyingVector = glm::vec2(+0.01f, +0.0f);
}


MeWidget::~MeWidget()
{

}


glm::vec2 MeWidget::perpCw2d(glm::vec2 input) {

	return glm::vec2(input.y, -input.x);
}

glm::vec2 MeWidget::perpCc2d(glm::vec2 input) {

	return glm::vec2(-input.y, input.x);
}

glm::vec3 MeWidget::subtraction3d(glm::vec3 left, glm::vec3 right) {

	return glm::vec3(left.x - right.x, left.y - right. y, left.z - right.z);
}

glm::vec2 MeWidget::subtraction2d(glm::vec2 left, glm::vec2 right)
{
	return glm::vec2(left.x - right.x, left.y - right.y);
}

void MeWidget::timerEvent(QTimerEvent *event) {

	printf("One second passed");
	myGLWindow->InjectUniformValue(FlyingVector.x, FlyingVector.y);
	myGLWindow->repaint();
}

void MeWidget::keyPressEvent(QKeyEvent *event)
{
	printf("catch\n"); 
	/*
	if (event->key() == Qt::Key_W)
	{
		printf("w");
		myGLWindow->InjectUniformValue(+0.00f, +0.01f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_S)
	{
		printf("s");
		myGLWindow->InjectUniformValue(+0.00f, -0.01f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_A)
	{
		printf("a");
		myGLWindow->InjectUniformValue(-0.01f, +0.00f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_D)
	{
		printf("d");
		myGLWindow->InjectUniformValue(+0.01f, +0.00f);
		myGLWindow->repaint();
	}

	//-------for another triangle

	printf("catch\n");
	if (event->key() == Qt::Key_Up)
	{
		printf("up");
		myGLWindow->InjectUniformValue_2(+0.00f, +0.01f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Down)
	{
		printf("down");
		myGLWindow->InjectUniformValue_2(+0.00f, -0.01f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Left)
	{
		printf("left");
		myGLWindow->InjectUniformValue_2(-0.01f, +0.00f);
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Right)
	{
		printf("right");
		myGLWindow->InjectUniformValue_2(+0.01f, +0.00f);
		myGLWindow->repaint();
	}
	*/
}
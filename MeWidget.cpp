#include "MeWidget.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <Qt\qevent.h>
#include <MeGLwindow.h>
#include <glm\glm.hpp>


MeWidget::MeWidget()
{
	FlyingVector = glm::vec2(-0.01f, +0.0f);
	InitialPosition= glm::vec2(+0.8f, -0.8f);
	TriPosition = glm::vec2(+0.0f, -0.0f);
	TriPosition.x = InitialPosition.x + FlyingVector.x;
	TriPosition.y = InitialPosition.y + FlyingVector.y;

	myGLWindow = new MeGLWindow();
	myGLWindow->InitialValueSetter(InitialPosition.x, InitialPosition.y);
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

	startTimer(20);

	//---Hard code boundaries---
	boundaryPoint1 = glm::vec3(-1.0f, 0.0f, +0.1f);
	boundaryPoint2 = glm::vec3(+1.0f, 0.0f, +0.1f);
	boundaryPoint3 = glm::vec3(+0.0f, 1.0f, +0.1f);
	boundaryPoint4 = glm::vec3(+0.0f, -1.0f, +0.1f);

	
}


MeWidget::~MeWidget()
{

}

//----vector maths------
glm::vec3 MeWidget::perpCw3d(glm::vec3 input) {

	return glm::vec3(input.y, -input.x, +0.0f);
}

glm::vec3 MeWidget::perpCc3d(glm::vec3 input) {

	return glm::vec3(-input.y, input.x, +0.0f);
}

GLfloat MeWidget::dot2d(glm::vec2 input1, glm::vec2 input2)
{
	return input1.x*input2.x + input1.y*input2.y;
}

GLfloat MeWidget::dot3d(glm::vec3 input1, glm::vec3 input2)
{
	return input1.x*input2.x + input1.y*input2.y + input1.z*input2.z;
}

void MeWidget::handleBoundaries()
{
	glm::vec3 wall1 = subtraction3d(boundaryPoint1, boundaryPoint2);
	glm::vec3 normal1 = perpCc3d(wall1);
	//glm::vec3 respectivePosition = 
}

glm::vec3 MeWidget::subtraction3d(glm::vec3 left, glm::vec3 right) {

	return glm::vec3(left.x - right.x, left.y - right. y, left.z - right.z);
}

glm::vec2 MeWidget::subtraction2d(glm::vec2 left, glm::vec2 right)
{
	return glm::vec2(left.x - right.x, left.y - right.y);
}

//--------vector maths------

void MeWidget::timerEvent(QTimerEvent *event) {

	//printf("One second passed");
	TriPosition.x = TriPosition.x + FlyingVector.x;
	TriPosition.y = TriPosition.y + FlyingVector.y;
	myGLWindow->InitialValueSetter(TriPosition.x, TriPosition.y);
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
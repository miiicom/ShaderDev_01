#include "MeWidget.h"
#include <Qt\qapplication.h>
#include <QtGui\qmouseevent>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <Qt\qevent.h>
#include <MeGLwindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


MeWidget::MeWidget()
{
	rotationValue = +45.0f;
	myGLWindow = new MeGLWindow();
	myGLWindow->InitialValueSetter(rotationValue);
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

	IsPressing = false;
	myGLWindow->setMouseTracking(true);
	startTimer(50);

	//---Hard code boundaries---
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

GLfloat MeWidget::vecMagnitude(glm::vec3 input) {
	
	return sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
}

glm::vec3 MeWidget::normalize(glm::vec3 input)
{
	GLfloat mag = vecMagnitude(input);
	return glm::vec3(input.x / mag, input.y / mag, input.z/ mag);
}

glm::vec3 MeWidget::scale(GLfloat scale, glm::vec3 input)
{
	return glm::vec3(input.x * scale, input.y * scale, input.z * scale);
}

glm::vec3 MeWidget::multiply(glm::vec3 left, glm::vec3 right)
{
	return glm::vec3(left.x*right.x, left.y*right.y, left.z*right.x);
}

glm::vec3 MeWidget::subtraction3d(glm::vec3 left, glm::vec3 right) {

	return glm::vec3(left.x - right.x, left.y - right. y, left.z - right.z);
}

glm::vec2 MeWidget::subtraction2d(glm::vec2 left, glm::vec2 right)
{
	return glm::vec2(left.x - right.x, left.y - right.y);
}

//--------vector maths------
void MeWidget::handleBoundaries()
{
/*
	//Left up wall
	glm::vec3 OldTriPosition = TriPosition;

	glm::vec3 wall1 = subtraction3d(boundaryPoint1, boundaryPoint3);
	glm::vec3 normal1 = normalize(perpCc3d(wall1));
	glm::vec3 respectivePosition = subtraction3d(TriPosition, boundaryPoint3);
	GLfloat dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		printf("collided with Left up wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);
	}
	else {
		collided = false;
	}

	//Left Down wall
	wall1 = subtraction3d(boundaryPoint1, boundaryPoint4);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint4);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		printf("collided with Left down wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f,FlyingVector);
	}
	else {
		collided = false;
	}

	//Right up wall
	wall1 = subtraction3d(boundaryPoint2, boundaryPoint3);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint3);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		printf("collided with Right Up wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);
		
	}
	else {
		collided = false;
	}

	//Right down wall
	wall1 = subtraction3d(boundaryPoint2, boundaryPoint4);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint4);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		printf("collided with Right Down wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);
		
	}
	else {
		collided = false;
	}*/
}
void MeWidget::timerEvent(QTimerEvent *event) {
	rotationValue++;
	//myGLWindow->InitialValueSetter(rotationValue);
	myGLWindow->time += 1.0f;
	myGLWindow->Calculate2DSpriteLoc(myGLWindow->time,16,16);
	myGLWindow->repaint();
}

void MeWidget::keyPressEvent(QKeyEvent *event)
{
	printf("catch\n"); 
	if (event->key() == Qt::Key_W)
	{
		printf("w");
		myGLWindow->meCamera->moveForward();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_S)
	{
		printf("s");
		myGLWindow->meCamera->moveBackward();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_A)
	{
		printf("a");
		myGLWindow->meCamera->strafeLeft();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_D)
	{
		printf("d");
		myGLWindow->meCamera->strafeRight();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_R)
	{
		printf("up");
		myGLWindow->meCamera->moveUP();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_F)
	{
		printf("down");
		myGLWindow->meCamera->moveDown();
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_G)
	{
		printf("left");
		myGLWindow->meCamera->reset();
		myGLWindow->repaint();
	}
	if (event->key() == Qt::Key_J)
	{
		printf("light move X positive");
		myGLWindow->MoveLightLight(glm::vec3(0.1, 0.0, 0.0));
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_K)
	{
		printf("light move X negative");
		myGLWindow->MoveLightLight(glm::vec3(-0.1, 0.0, 0.0));
		myGLWindow->repaint();
	}
	if (event->key() == Qt::Key_I)
	{
		printf("light move Z positive");
		myGLWindow->MoveLightLight(glm::vec3(0.0, 0.0, 0.1));
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_M)
	{
		printf("light move Z negative");
		myGLWindow->MoveLightLight(glm::vec3(0.0, 0.0, -0.1));
		myGLWindow->repaint();
	}

}

void MeWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {

		printf("clicked");
		if (hasMouseTracking()) {
			printf("tracking\n");
		}
		IsPressing = true;
		dragStartPosition = event->pos();
	}
}

void MeWidget::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {

		printf("released");
		if (hasMouseTracking()) {
			printf("tracking\n");
		}
		IsPressing = false;
	}
}

void MeWidget::mouseMoveEvent(QMouseEvent * event)
{
	if (!(event->buttons() & Qt::LeftButton))
		return;
	if ((event->pos() - dragStartPosition).manhattanLength()
		< QApplication::startDragDistance())
		return;
	float xMovement = event->pos().x() - dragStartPosition.x();
	float yMovement = event->pos().y() - dragStartPosition.y();

	dragStartPosition = event->pos();

	glm::vec2 Displacement = glm::vec2(xMovement, yMovement);
	myGLWindow->meCamera->mouseUpdate(Displacement);
	printf("Dragging");
	myGLWindow->repaint();
}

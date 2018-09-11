#include "MeWidget.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <Qt\qevent.h>
#include <MeGLwindow.h>



MeWidget::MeWidget()
{
	myGLWindow = new MeGLWindow();

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

	startTimer(20);
}


MeWidget::~MeWidget()
{

}

void MeWidget::timerEvent(QTimerEvent *event) {

	printf("One second passed");
	myGLWindow->InjectUniformValue(+0.01f, +0.00f);
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
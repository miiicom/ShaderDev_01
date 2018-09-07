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
}


MeWidget::~MeWidget()
{
}

void MeWidget::keyPressEvent(QKeyEvent *event)
{
	printf("catch");
	if (event->key() == Qt::Key_W)
	{
		myGLWindow->repaint();
	}
}
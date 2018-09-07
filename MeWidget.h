#pragma once
#include <QtGui\qwidget.h>
#include <Qt\qevent.h>
#include <MeGLWindow.h>
class MeWidget : public QWidget
{
public:
	MeWidget();
	~MeWidget();


protected:
	void keyPressEvent(QKeyEvent *);

private:
	MeGLWindow * myGLWindow;
};




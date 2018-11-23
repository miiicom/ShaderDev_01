#include <Qt\qapplication.h>
#include <MeGLWindow.h>
#include <MeWidget.h>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	//MeGLWindow meWindow;
	//meWindow.setFixedSize(512, 512);
	//meWindow.show();

	MeWidget meWidg;
	meWidg.setFixedSize(1024, 1024);
	meWidg.show();
	
	return app.exec();
}
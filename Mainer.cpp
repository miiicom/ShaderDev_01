#include <Qt\qapplication.h>
#include <MeGLWindow.h>
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MeGLWindow meWindow;
	meWindow.setFixedSize(512, 512);
	meWindow.show();

	
	return app.exec();
}
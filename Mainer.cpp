#include <Qt\qapplication.h>
#include <MeGlWindow.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MeGLWindow meWindow;
	meWindow.setFixedSize(1024,512);
	meWindow.show();
	return app.exec();
}
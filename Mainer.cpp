#include <Qt\qapplication.h>
#include <MeGlWindow.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MeGLWindow meWindow;
	meWindow.setFixedSize(512,1024);
	meWindow.move(0, 0);
	meWindow.show();

	while (1) {
		Sleep(50);
		meWindow.repaint();

	}
	return app.exec();
}
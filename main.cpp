#include <QtGui\qapplication.h>
#include <MyGLWindow.h>
#include <QtGui\qwidget.h>
#include <MyWidget.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MyWidget widg;
	widg.show();
	//MyGLWindow myWindow;
	//myWindow.show();
	return app.exec();

}
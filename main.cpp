#include <QtGui\qapplication.h>
#include <Qt\qrect.h>
#include <QtGui\qdesktopwidget.h>
#include <MyGLWindow.h>
#include <QtGui\qwidget.h>
#include <MyWidget.h>
 
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MyWidget widg;
 
	widg.show();
	
	app.setKeyboardInputInterval(40);
	return app.exec();

}
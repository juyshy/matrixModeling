#pragma once
#include <QtGui\qwidget.h>
#include <Qt\qelapsedtimer.h>
#include <QtGui\qlabel.h>
#include <MyModel.h>
#include <sstream>
class DebugSlider;
class MyGLWindow; // forward declare
class MyWidget : public  QWidget
{
	Q_OBJECT
	DebugSlider * lightXSlider;
	DebugSlider * lightYSlider;
	DebugSlider * lightZSlider;
	QLabel *label;
	MyGLWindow * myGlWindow;
	MyModel theModel;
	int elapsed;
	QElapsedTimer etimer;
	int previousTime;
	std::ostringstream debugstr;
	std::string currtimeStr;
	bool savefpsTracing;
	bool saved;
	void MyWidget::saveTrace();
	private slots:
	void sliderValueChanged();
 
	void  animate();
protected:
	void keyPressEvent(QKeyEvent* e);
public:
	MyWidget();
	~MyWidget();
};


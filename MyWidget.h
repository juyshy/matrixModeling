#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qmainwindow.h>
 
#include <Qt\qelapsedtimer.h>
#include <QtGui\qlabel.h>
#include <QtGui\qspinbox.h>
#include <MyModel.h>
#include <sstream>
class DebugSlider;
class MyGLWindow; // forward declare
class MyWidget : public  QMainWindow
{
	Q_OBJECT
	DebugSlider * lightXSlider;
	DebugSlider * lightYSlider;
	DebugSlider * lightZSlider;

	DebugSlider * extrScaleXSlider;
	DebugSlider * extrScaleYSlider;
	DebugSlider * extrScaleZSlider;
	DebugSlider * extrScaleWSlider;

	DebugSlider * extrTransXSlider;
	DebugSlider * extrTransYSlider;
	DebugSlider * extrTransZSlider;
 

	QLabel *label;
	QLabel *sblabel;

	QSpinBox * spinBox;

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


	QWidget *centralWidget;


	private slots:
	void sliderValueChanged();
	void spinBValueChanged(int);
	void exsliderValueChanged();
	void exsTrliderValueChanged();
	void  animate();
protected:
	void keyPressEvent(QKeyEvent* e);
public:
	MyWidget();
	~MyWidget();
};


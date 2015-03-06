#pragma once
#include <QtGui\qwidget.h>
#include <MyModel.h>
class DebugSlider;
class MyGLWindow; // forward declare
class MyWidget : public  QWidget
{
	Q_OBJECT
	DebugSlider * lightXSlider;
	DebugSlider * lightYSlider;
	DebugSlider * lightZSlider;

	MyGLWindow * myGlWindow;
	MyModel theModel;
	private slots:
	void sliderValueChanged();

protected:
	void keyPressEvent(QKeyEvent* e);
public:
	MyWidget();
 
};


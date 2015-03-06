#include "MyWidget.h"
#include <Qt\qdebug.h>
#include <Qt\qelapsedtimer.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qkeyevent>
#include <QtGui\qlabel.h>
#include <MyGLWindow.h>
#include <DebugSlider.h>
#include <Qt\qtimer.h>
#include <Qt\qdatetime.h>
#include <string>
#include <Utility.h>
#include <boost\algorithm\string\replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <iostream>
#include <string>

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost;
MyWidget::MyWidget()
{
	//setFocusPolicy(Qt::StrongFocus);
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	QVBoxLayout* controlsLayout;
	QVBoxLayout* labelLayout;
 

	label = new QLabel(tr("FPS:"));
	mainLayout->addLayout(labelLayout = new QVBoxLayout);
	labelLayout->addWidget (label);
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(myGlWindow =  new MyGLWindow(&theModel));

	QHBoxLayout* lightPositionLayout;
	controlsLayout->addLayout(lightPositionLayout = new QHBoxLayout);
	lightPositionLayout->addWidget(lightXSlider = new DebugSlider);
	lightPositionLayout->addWidget(lightYSlider = new DebugSlider);
	lightPositionLayout->addWidget(lightZSlider = new DebugSlider);
	lightXSlider->setValue(-1.5f);
	lightYSlider->setValue(0);
	lightZSlider->setValue(0);
	connect(lightXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	theModel.sliderPosition.x = lightXSlider->value();
	theModel.sliderPosition.y = lightYSlider->value();
	theModel.sliderPosition.z = lightZSlider->value();

	saved = false;
	QTimer *timer = new QTimer(this);

	etimer.start();
	//connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(1);
	elapsed=0;
	myGlWindow->repaint();
}

void MyWidget::animate(){
	elapsed = etimer.elapsed(); //(elapsed + qobject_cast<QTimer*>(sender())->interval()) % 100000;
	double fps = 1000 / (elapsed - previousTime);
 
	QString fpsstr = "FPS:" + QString::number(fps); 
	
	label->setText(fpsstr);
	if (elapsed <60000) {
		debugstr << elapsed << ":" << fps << "\n";
	}
	else if (!saved )
	{
		saveTrace(); 
	}
	previousTime = elapsed;
	myGlWindow->update(elapsed);
	myGlWindow->repaint();
}

void MyWidget::saveTrace(){
	saved = true;
	date today = day_clock::local_day();
	ptime now = second_clock::local_time();
	std::string nowstr = to_simple_string(now);
	erase_all(nowstr, ":");
	std::string filename = "tracing/fpstrace" + nowstr + ".txt";
	Utility::SaveToFile(filename, debugstr.str());
}

MyWidget::~MyWidget(){

	if (!saved)
	{
		saveTrace();
	}
}

void MyWidget::sliderValueChanged()
{
	//qDebug() << "slider!!!" << lightXSlider->value();
	theModel.sliderPosition.x = lightXSlider->value();
	theModel.sliderPosition.y = lightYSlider->value();
	theModel.sliderPosition.z = lightZSlider->value();
	//myGlWindow->repaint();
}


void MyWidget::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		myGlWindow->camera.moveForward();
		break;
	case Qt::Key::Key_S:
		myGlWindow->camera.moveBackwards();
		break;
	case Qt::Key::Key_A:
		myGlWindow->camera.strafeLeft();
		break;
	case Qt::Key::Key_D:
		myGlWindow->camera.strafeRight();
		break;
	case Qt::Key::Key_R:
		myGlWindow->camera.moveUp();
		break;
	case Qt::Key::Key_F:
		myGlWindow->camera.moveDown();
		break;
	default:
		break;
	}
	//myGlWindow->repaint();
}

 
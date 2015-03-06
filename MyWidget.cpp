#include "MyWidget.h"
#include <Qt\qdebug.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qkeyevent>
#include <MyGLWindow.h>
#include <DebugSlider.h>

MyWidget::MyWidget()
{
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	QVBoxLayout* controlsLayout;
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
	myGlWindow->repaint();
}

void MyWidget::sliderValueChanged()
{
	//qDebug() << "slider!!!" << lightXSlider->value();
	theModel.sliderPosition.x = lightXSlider->value();
	theModel.sliderPosition.y = lightYSlider->value();
	theModel.sliderPosition.z = lightZSlider->value();
	myGlWindow->repaint();
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
	myGlWindow->repaint();
}

 
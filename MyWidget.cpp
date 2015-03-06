#include "MyWidget.h"
#include <Qt\qdebug.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
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
	lightXSlider->setValue(0);
	lightYSlider->setValue(0);
	lightZSlider->setValue(0);
	connect(lightXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));

}

void MyWidget::sliderValueChanged()
{
	qDebug() << "slider!!!" << lightXSlider->value();
	theModel.lightPosition.x = lightXSlider->value();
	theModel.lightPosition.y = lightYSlider->value();
	theModel.lightPosition.z = lightZSlider->value();
	myGlWindow->repaint();
}


 
#include "MyWidget.h"
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
	mainLayout->addWidget(new MyGLWindow);

	QHBoxLayout* lightPositionLayout;
	controlsLayout->addLayout(lightPositionLayout = new QHBoxLayout);
	lightPositionLayout->addWidget(new DebugSlider);
	lightPositionLayout->addWidget(new DebugSlider);
	lightPositionLayout->addWidget(new DebugSlider);
}


 
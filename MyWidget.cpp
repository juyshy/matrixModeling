#include "MyWidget.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <MyGLWindow.h>
MyWidget::MyWidget()
{
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	QVBoxLayout* controlsLayout;
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(new MyGLWindow);
}


 
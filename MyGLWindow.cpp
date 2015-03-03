#include <gl\glew.h>
#include "MyGLWindow.h"

void MyGLWindow::initializeGL(){
	glewInit();
}

void MyGLWindow::paintGL(){
	glClearColor(0.5, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

MyGLWindow::MyGLWindow()
{
}


MyGLWindow::~MyGLWindow()
{
}

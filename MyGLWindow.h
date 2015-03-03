#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW
#include <QtOpenGL\qglwidget>

class MyGLWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
public:
	MyGLWindow();
	~MyGLWindow();
};

#endif


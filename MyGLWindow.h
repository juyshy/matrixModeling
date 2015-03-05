#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW
#include <gl\glew.h>
#include <QtOpenGL\qglwidget>
#include <string>
class MyGLWindow : public QGLWidget
{
	void MyGLWindow::sendDataToOpenGL();
	bool MyGLWindow::checkStatus(
		GLuint objectID,
		PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		GLenum statusType
		);
	bool MyGLWindow::checkShaderStatus(GLuint shaderID);
	bool MyGLWindow::checkProgramStatus(GLuint programID);
	std::string MyGLWindow::readShaderCode(const char* filename);
	void MyGLWindow::installShaders();
protected:
	void initializeGL();
	void paintGL();

public:
	MyGLWindow();
	~MyGLWindow();
};

#endif


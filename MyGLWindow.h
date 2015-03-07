#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW
#include <gl\glew.h>
#include <QtOpenGL\qglwidget>
#include <string>
#include "Camera.h"
#include <ShapeModel.h>
#include <vector>
class MyModel;

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
	void setupVertexArrays();
	MyModel * theModel;
	GLuint ambientLightUniformLocation;
	glm::vec3 ambientLight;
	//int elapsed;

protected:
	
	void initializeGL();
	void paintGL();
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	Camera camera;
	MyGLWindow(MyModel * theModel); 
 
	~MyGLWindow();

	void update(int elapsed);
 

	ShapeModel triangle;
 

};

#endif


#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW
#include <gl\glew.h>
#include <QtOpenGL\qglwidget>
#include <string>
#include "Camera.h"
#include <ShapeModel.h>
#include <vector>
#include "shader/glslprogram.h"
#include <extra\vbotorus.h>
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
	void MyGLWindow::compile();
 
	MyModel * theModel;
	GLuint ambientLightUniformLocation;
	glm::vec3 ambientLight;
	//int elapsed;
	GLuint vaoHandle;
	//void MyGLWindow::printActiveUniforms(GLuint programHandle);
	glm::mat4 rotationMatrix;
	float angle;
	GLuint programHandle;
	GLSLProgram prog;

	mat4 model;
	mat4 view;
	mat4 projection;

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
 
	VBOTorus * torus;
	ShapeModel triangle;
 

};

#endif


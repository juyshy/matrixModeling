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

#include <ProcModel.h>
class MyModel;

__declspec(align(16))  class MyGLWindow : public QGLWidget
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
	void setMatrixes();
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
	void resizeGL(int width, int height);
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

	float fps;
	
	ProcModel pModel;

	// fix for warning http://stackoverflow.com/questions/20104815/warning-c4316-object-allocated-on-the-heap-may-not-be-aligned-16
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
		void operator delete(void* p)
	{
		_mm_free(p);
	}

};

#endif


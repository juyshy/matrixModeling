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
	 
	void sendDataToOpenGL();
	bool checkStatus(
		GLuint objectID,
		PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
		PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
		GLenum statusType
		);
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string readShaderCode(const char* filename);
	void installShaders();
	void setupVertexArrays();
	void compile();
	void setMatrixes();
	MyModel * theModel;
	GLuint ambientLightUniformLocation;
	glm::vec3 ambientLight;
	//int elapsed;
	GLuint vaoHandle;
	//void printActiveUniforms(GLuint programHandle);
	glm::mat4 rotationMatrix;
	float angle;
	GLuint programHandle;
	GLSLProgram prog;

	mat4 model;
	mat4 view;
	mat4 projection;
	glm::vec3 materialDiffuse; 
	glm::vec3 materialAmbient;
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

	void updateColor();

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


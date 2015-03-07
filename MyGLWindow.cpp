#include <gl\glew.h>
#include "MyGLWindow.h"
#include <iostream>
#include <fstream>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Qt\qtimer.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <Vertex.h>
#include <ShapeGenerator.h>
#include "Camera.h"
#include <MyModel.h>
using namespace std;
using glm::vec3;
using glm::mat4;

extern const char* vertexShaderCode;
extern  const char* fragmentShaderCode;

GLuint programID;
bool mouseDown = false;

MyGLWindow::MyGLWindow(MyModel * theModel) : theModel(theModel)
{
	angle = 0;
}

void MyGLWindow::update(int elapsed) {
	angle += 0.01f * theModel->sliderPosition.x;
	if (angle >= 360.0f) angle -= 360.0f;
	
	////arrow.rotation.angle = elapsed / 20.0f;
	std::cout << angle << std::endl;
}

void MyGLWindow::sendDataToOpenGL() {
 
	//triangle.Init("triangle");
	/////////////////// Create the VBO ////////////////////
	float positionData[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f };
	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };


	// Create and populate the buffer objects
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);  // Vertex position
	glEnableVertexAttribArray(1);  // Vertex color

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
}

void MyGLWindow::setupVertexArrays(){
}
bool MyGLWindow::checkStatus(	GLuint objectID,	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,	GLenum statusType	)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE){
		GLint infoLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLength);
		GLchar* buffer = new GLchar[infoLength];
		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}
bool MyGLWindow::checkShaderStatus(GLuint shaderID){
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool MyGLWindow::checkProgramStatus(GLuint programID){
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);

}
string MyGLWindow::readShaderCode(const char* filename)
{
	ifstream myInput(filename);
	if (!myInput.good())
	{
		cout << "File failled to load .. " << filename;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(myInput),
		std::istreambuf_iterator<char>());
}
void MyGLWindow::installShaders(){
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* adapter[1];
	string temp = readShaderCode("shader/basic_uniform.vert");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("shader/basic_uniform.frag");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	 programID = glCreateProgram();

	 //// Bind index 0 to the shader input variable "VertexPosition"
	 //glBindAttribLocation(programID, 0, "VertexPosition");
	 //// Bind index 1 to the shader input variable "VertexColor"
	 //glBindAttribLocation(programID, 1, "VertexColor");

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
	this->programHandle = programID;
	//printActiveUniforms(programID);


}
void MyGLWindow::initializeGL(){
	setMinimumSize(800, 600);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	
	//setupVertexArrays();
	//installShaders();
	compile();
	prog.printActiveUniforms();
	sendDataToOpenGL();

 
}

void MyGLWindow::paintGL(){

	// clear background
	glClearColor(0.2, 0, 0.5, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	mat4 viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProojectionMatrix = viewToProjectionMatrix* worldToViewMatrix;

	rotationMatrix = glm::rotate(mat4(1.0f), angle, vec3(0.0f, 0.0f, 1.0f));

	mat4 fullTransformMatrix = worldToProojectionMatrix * rotationMatrix;

	GLuint programHandle = prog.getHandle();
	GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	}

	///triangle.Draw();
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGLWindow::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	}
	catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void MyGLWindow::mouseReleaseEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton)
		mouseDown = false;
}
void MyGLWindow::mousePressEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton)
		mouseDown = true;
}

void MyGLWindow::mouseMoveEvent(QMouseEvent* e)
{
	if (mouseDown)
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
	//repaint();
}

void MyGLWindow::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		camera.moveForward();
		break;
	case Qt::Key::Key_S:
		camera.moveBackwards();
		break;
	case Qt::Key::Key_A:
		camera.strafeLeft();
		break;
	case Qt::Key::Key_D:
		camera.strafeRight();
		break;
	case Qt::Key::Key_R:
		camera.moveUp();
		break;
	case Qt::Key::Key_F:
		camera.moveDown();
		break;
	default:
		break;
	}
	repaint();
}
 

MyGLWindow::~MyGLWindow()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

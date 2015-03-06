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

	//elapsed = 0;

}
//void MyGLWindow::animate()
//{
//	elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
//	std::cout << elapsed << std::endl;
//
//	repaint();
//}

void MyGLWindow::update(int elapsed) {
	arrow.rotation.angle = elapsed / 20.0f;
	std::cout << elapsed << std::endl;
}

void MyGLWindow::sendDataToOpenGL() {
 
	cube1.Init("cube");
	cube2.Init("cube");
	arrow.Init("arrow");
	plane.Init("plane");

	cube2.position = vec3(10.5f, 1.0f, -3.0f);
	arrow.position = vec3(4.5f, 2.0f, -3.0f);
	plane.position = vec3(0.0f, 0.0f, 0.0f);

	
	arrow.rotation.axis = vec3(0.0f, 0.0f, 1.0f);
	cube1.rotation.angle = 36.0f;
	cube1.rotation.axis = vec3(1.0f, 0.0f, 0.0f);
	cube2.rotation.angle = 56.0f;
	cube2.rotation.axis = vec3(0.0f, 1.0f, 0.0f);
	cube2.scale = glm::vec3(0.5f, 2.0f, 3.0f);
	plane.scale =   glm::vec3(10.0f, 1.0f, 30.0f);

	for (uint i = 0; i < 20; i++){
		for (uint j = 0; j < 20; j++){
			ShapeModel block;
			block.Init("cube");
			block.scale = glm::vec3(0.2f, 1.0f, 0.2f);
			block.position = vec3(i * 2 - 20, 0.5f, j * 2 - 20);
			blocks.push_back(block);
		}
	}
	 
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
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	 programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);

}
void MyGLWindow::initializeGL(){
	setMinimumSize(800, 600);
	setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	
	//setupVertexArrays();
	installShaders();
	fullTransformUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
	ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	ambientLight = vec3(0.9f, 0.9f, 0.9f);
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	sendDataToOpenGL();
}

void MyGLWindow::paintGL(){

	glClearColor(0.2, 0, 0.5, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 100.0f);
 
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	worldToProojectionMatrix = viewToProjectionMatrix* worldToViewMatrix;

 
	cube1.position = theModel->sliderPosition;
	cube1.Draw(&worldToProojectionMatrix, &fullTransformUniformLocation);
	cube2.Draw(&worldToProojectionMatrix, &fullTransformUniformLocation);
	arrow.Draw(&worldToProojectionMatrix, &fullTransformUniformLocation);
	plane.Draw(&worldToProojectionMatrix, &fullTransformUniformLocation);

	for (ShapeModel block : blocks)
		block.Draw(&worldToProojectionMatrix, &fullTransformUniformLocation);



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

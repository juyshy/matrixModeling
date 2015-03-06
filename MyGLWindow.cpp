#include <gl\glew.h>
#include "MyGLWindow.h"
#include <iostream>
#include <fstream>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <Vertex.h>
#include <ShapeGenerator.h>
#include "Camera.h"
using namespace std;
using glm::vec3;
using glm::mat4;

extern const char* vertexShaderCode;
extern  const char* fragmentShaderCode;


const float X_DELTA = 0.1F;
uint numTris = 0;
const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint TRIANGLE_BYTE_SIZE = NUM_VERTICES_PER_TRI* NUM_FLOATS_PER_VERTICE*sizeof(float);
const uint VERTEX_BYTE_SIZE =   NUM_FLOATS_PER_VERTICE*sizeof(float);
const uint MAX_TRIS = 20;
GLuint programID;

GLuint cubeNumIndices;
GLuint arrowNumIndices;
GLuint planeNumIndices;
Camera camera;
GLuint cubeVertexbufferID;
GLuint arrowVertexbufferID;
GLuint planeVertexbufferID;
GLuint cubeIndexBufferID;
GLuint arrowIndexBufferID;
GLuint planeIndexBufferID;
GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint planeVertexArrayObjectID;
GLint fullTransformUniformLocation;

void MyGLWindow::sendDataToOpenGL() {
	ShapeData shape = ShapeGenerator::makeCube();

	
	glGenBuffers(1, &cubeVertexbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // 0 = layoput location
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
 

	glGenBuffers(1, &cubeIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	cubeNumIndices = shape.numIndices;
	shape.cleanup();

	shape = ShapeGenerator::makeArrow();

 
	 glGenBuffers(1, &arrowVertexbufferID);
	 glBindBuffer(GL_ARRAY_BUFFER, arrowVertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // 0 = layoput location
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));

 
 
	glGenBuffers(1, &arrowIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrowIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	arrowNumIndices = shape.numIndices;
	shape.cleanup();

	shape = ShapeGenerator::makePlane();


	glGenBuffers(1, &planeVertexbufferID);
	glBindBuffer(GL_ARRAY_BUFFER, planeVertexbufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // 0 = layoput location
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));



	glGenBuffers(1, &planeIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	planeNumIndices = shape.numIndices;
	shape.cleanup();
}

void MyGLWindow::setupVertexArrays(){
	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);
	glGenVertexArrays(1, &planeVertexArrayObjectID);
	
	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID);

	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, arrowVertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrowIndexBufferID);

	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, planeVertexbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeIndexBufferID);
}
bool MyGLWindow::checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType
	)
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
	sendDataToOpenGL();
	setupVertexArrays();
	installShaders();
	  fullTransformUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");

}

void MyGLWindow::paintGL(){

 
	glClearColor(0.2, 0, 0.5, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	mat4 fullTransformMatrix;
	mat4 viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProojectionMatrix = viewToProjectionMatrix* worldToViewMatrix;

	GLuint ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	vec3 ambientLight(0.9f, 0.9f, 0.9f);
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	// cube
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cube1ModelToWorldMatrix = glm::translate(vec3(-1.5f, 0.0f, -3.0f)) * glm::rotate(36.0f, vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProojectionMatrix * cube1ModelToWorldMatrix;

	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	
	mat4 cube2ModelToWorldMatrix = glm::translate(vec3(2.5f, 0.0f, -3.0f)) *  glm::rotate(36.0f, vec3(0.0f, 1.0f, 0.0f));
	fullTransformMatrix = worldToProojectionMatrix * cube2ModelToWorldMatrix;

	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, 0);

	// arrow
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix = glm::translate(0.0f, 2.0f, -5.0f);
	fullTransformMatrix = worldToProojectionMatrix * arrowModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(planeVertexArrayObjectID);
	mat4 planeModelToWorldMatrix = glm::translate(0.0f, 0.0f, 0.0f);
	fullTransformMatrix = worldToProojectionMatrix * planeModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, planeNumIndices, GL_UNSIGNED_SHORT, 0);


	
}
void MyGLWindow::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
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
MyGLWindow::MyGLWindow()
{
}

MyGLWindow::~MyGLWindow()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

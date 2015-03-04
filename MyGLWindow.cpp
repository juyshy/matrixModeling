#include <gl\glew.h>
#include "MyGLWindow.h"
#include <iostream>
using namespace std;
extern const char* vertexShaderCode;
extern  const char* fragmentShaderCode;

void sendDataToOpenGL() {
	GLfloat verts[] = {
		0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
	};
	GLuint mybufferID;
	glGenBuffers(1, &mybufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mybufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	GLushort indices[] = { 0, 1, 2, 0, 3, 4 };
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}
bool checkStatus(
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
bool checkShaderStatus(GLuint shaderID){
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);	 
}

bool checkProgramStatus(GLuint programID){
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);

}
void installShaders(){
	GLuint vertexShaderID= glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* adapter[1];
	adapter[0] = vertexShaderCode;
	glShaderSource(vertexShaderID, 1, adapter,0);
	adapter[0] = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramStatus(programID))
		return;

	glUseProgram(programID);

}
void MyGLWindow::initializeGL(){
	glewInit();
	sendDataToOpenGL();
	installShaders();
}

void MyGLWindow::paintGL(){
	glClearColor(0.2, 0, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

MyGLWindow::MyGLWindow()
{
}


MyGLWindow::~MyGLWindow()
{
}

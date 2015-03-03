#include <gl\glew.h>
#include "MyGLWindow.h"

extern const char* vertexShaderCode;
extern  const char* fragmentShaderCode;

void sendDataToOpenGL() {
	GLfloat verts[] = {
		0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
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

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glUseProgram(programID);

}
void MyGLWindow::initializeGL(){
	glewInit();
	sendDataToOpenGL();
	installShaders();
}

void MyGLWindow::paintGL(){
	glClearColor(0.5, 0, 1, 1);
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

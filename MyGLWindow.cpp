#include <gl\glew.h>
#include "MyGLWindow.h"

void MyGLWindow::initializeGL(){
	glewInit();

	GLfloat verts[] = {
		 0.0f,   0.0f,
		1.0f,   1.0f,
		 -1.0f,  1.0f,
		 -1.0f, -1.0f,
		 1.0f, -1.0f,
	};
	GLuint mybufferID;
	glGenBuffers(1, &mybufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mybufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLushort indices[] = { 0, 1, 2, 0, 3, 4 };
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

#include <gl\glew.h>
#include "MyGLWindow.h"
#include <iostream>
#include <fstream>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <QtCore\qtimer.h>
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
using std::cerr;
using std::endl;

extern const char* vertexShaderCode;
extern  const char* fragmentShaderCode;

GLuint programID;
bool mouseDown = false;

MyGLWindow::MyGLWindow(MyModel * theModel) : theModel(theModel)
{
	//pModel = new ProcModel(theModel);
	angle = 0;
}
void MyGLWindow::updateColor()
{
	materialAmbient = materialDiffuse /* = pModel->color*/ = theModel->color;
	prog.setUniform("Material.Kd", materialDiffuse);
	prog.setUniform("Material.Ka", materialAmbient);
}
void MyGLWindow::update(int elapsed) {
	angle += 0.01f * theModel->sliderPosition.x;
	if (angle >= 360.0f) angle -= 360.0f;
	//pModel->translateVec = vec3(pModel->transXoffset, theModel->sliderPosition.y + pModel->transYoffset, theModel->sliderPosition.z + pModel->transZoffset);
	////arrow.rotation.angle = elapsed / 20.0f;
	//std::cout << angle << std::endl;
}
void MyGLWindow::resizeGL(int width, int height)
{
	projection = glm::perspective(glm::radians(70.0f), (float)width  / height , 0.3f, 300.0f);
	glViewport(0, 0, width , height );
}

void MyGLWindow::sendDataToOpenGL() {
 
	//triangle.Init("cube");
	/////////////////// Create the VBO ////////////////////

	cube.createCube();
	//pModel->createModel();
	//pModel->createCube();
	//pModel->createMultipleCubes();

	//torus = new VBOTorus(0.7f, 0.3f, 50,50);
	//model = mat4(1.0f);
	//model *= glm::rotate(glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
	//model *= glm::rotate(glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	view =camera.getWorldToViewMatrix();
	projection = mat4(1.0f);
	vec4 worldLight = vec4(5.0f, 5.0f, 2.0f, 1.0f);
	materialDiffuse = theModel->color;
	materialAmbient = materialDiffuse;
	prog.setUniform("Material.Kd", materialDiffuse);
	prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Light.Position", view * worldLight);
	prog.setUniform("Material.Ka", materialAmbient);
	prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
	prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
	prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
	prog.setUniform("Material.Shininess", 100.0f);

 
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
	glClearColor(0.2f, 0, 0.5f, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	view = camera.getWorldToViewMatrix();
 
	model = mat4(1.0f);

	model *= glm::translate(cube.translateVec);
 
	model *= glm::rotate(glm::radians(angle), vec3(0.0f, 1.0f, 0.0f));
	setMatrixes();
	//pModel->draw();
	cube.Draw();

	//for (uint x = 0; x < numIntancesOnX; x++) {
	//	for (uint y = 0; y < numIntancesOnY; y++) {
	//		for (uint z = 0; z < numIntancesOnZ; z++) {
	//			model = mat4(1.0f);

	//			model *= glm::translate(pModel->translateVec);
	//			model *= glm::translate(
	//				vec3(x * instancesDistance + multInstancesTransOffsetX,
	//				y * instancesDistance + multInstancesTransOffsetY,
	//				z * instancesDistance + multInstancesTransOffsetZ));
	//			model *= glm::rotate(glm::radians(angle), vec3(0.0f, 1.0f, 0.0f));
	//			setMatrixes();
	//			pModel->draw();
	//		}
	//	}
	//}
 
 
	
}
 
void MyGLWindow::setMatrixes()
{
	mat4 mv = view * model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);
}
void MyGLWindow::compile()
{
	try {
		prog.compileShader("shader/phong.vert");
		prog.compileShader("shader/phong.frag");
		prog.link();
		prog.validate();
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

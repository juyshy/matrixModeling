#include "ShapeModel.h"
#include <ShapeGenerator.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <string>
#include <iostream>


const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint TRIANGLE_BYTE_SIZE = NUM_VERTICES_PER_TRI* NUM_FLOATS_PER_VERTICE*sizeof(float);
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE*sizeof(float);

ShapeModel::ShapeModel()  
{
	rotation.angle = 0.0f;
	rotation.axis = glm::vec3(1.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	//Init();
}
void ShapeModel::Init(char  shapeLabel[]) { //MyGLWindow * myGlWin
	ShapeData shape;
	if (shapeLabel == "cube"){
		  shape = ShapeGenerator::makeCube();
	}
	else if (shapeLabel == "arrow"){
		shape = ShapeGenerator::makeArrow();
	}
	else if (shapeLabel == "plane"){
		shape = ShapeGenerator::makePlane();
	}
	else {
		shape = ShapeGenerator::makeCube();
	}
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // 0 = layoput location
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); // 0 = layoput location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	shapeNumIndices = shape.numIndices;
	shape.cleanup();
 

}

void ShapeModel::Draw(const glm::mat4 * worldToProjectionMatrix, const GLint* fullTransformUniformLocation) {

	glBindVertexArray(vertexArrayObjectID);
	//position = theModel->sliderPosition; // vec3(-1.5f, 0.0f, -3.0f);
	shapeModelToWorldMatrix = glm::translate(position) * glm::rotate(rotation.angle, rotation.axis) * glm::scale(scale);
	fullTransformMatrix = *worldToProjectionMatrix * shapeModelToWorldMatrix;
	glUniformMatrix4fv(*fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, shapeNumIndices, GL_UNSIGNED_SHORT, 0);

}

ShapeModel::~ShapeModel()
{
}

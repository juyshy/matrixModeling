#pragma once
#include <ShapeData.h>
#include <string>

struct Rotation
{
	float angle;
	glm::vec3 axis;
};

class ShapeModel
{
	ShapeData shape;

	GLuint vertexBufferID;
	GLuint indexBufferID;

	glm::mat4 fullTransformMatrix;
public:

	ShapeModel();
	~ShapeModel();
	void ShapeModel::Init(char shapeLabel[]);
	void ShapeModel::Draw(const glm::mat4 * worldToProojectionMatrix,  const GLint* fullTransformUniformLocation);
	void ShapeModel::Draw();
	GLuint vertexArrayObjectID;
	GLuint shapeNumIndices;
	glm::vec3 position;
	Rotation rotation;
	glm::vec3 scale;
	glm::mat4 shapeModelToWorldMatrix;
 
};


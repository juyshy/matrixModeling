#pragma once
#include <ShapeData.h>
class ShapeModel
{
	ShapeData shape;

	GLuint vertexBufferID;
	GLuint indexBufferID;

	glm::mat4 fullTransformMatrix;
public:

	ShapeModel();
	~ShapeModel();
	void ShapeModel::Init();
	void ShapeModel::Draw(const glm::mat4 * worldToProojectionMatrix,  const GLint* fullTransformUniformLocation);
	GLuint vertexArrayObjectID;
	GLuint shapeNumIndices;
	glm::vec3 position;
	glm::mat4 shapeModelToWorldMatrix;
 
};


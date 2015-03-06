#ifndef SHAPE_DATA
#define SHAPE_DATA
#include <GL\glew.h>
#include <Vertex.h>
#include <vector>
class Vertex;
struct ShapeData
{
	ShapeData():
		vertices(0), numVertices(0),
		indices(0), numIndices(0){}
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	std::vector<glm::vec3> vertPositions;
	std::vector<glm::vec3> norlmals;
	std::vector<glm::vec3> colors;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}
	void cleanup()
	{
		delete[] vertices;
		delete[] indices;
		numIndices = numVertices = 0;
	}
};
#endif
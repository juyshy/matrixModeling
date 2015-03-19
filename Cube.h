#pragma once
#include <GL/glew.h> 
#include "glm/glm.hpp"
#include <vector>
using   glm::vec3;
typedef  unsigned int uint;
class Cube
{
	std::vector<glm::vec3> vertexes;
	std::vector<glm::vec3> normals;
	std::vector<uint> indexes;

	std::vector<glm::vec3> verteksit2r;
	std::vector<glm::vec3> normals2r;
	 std::vector<vec3> basenormals ;
	std::vector<uint> normalIndexes;
	void  prepareVertexes();
	void  normalsData();
	void createGeometry();
	void createVbos();

	GLuint vao;
	GLuint normals_vbo;
	GLuint points_vbo;

public:
	
	float cubeSize = 2;
	void  createCube();
	void  Draw();
	glm::vec3 translateVec = glm::vec3(0.0f, -2.0f, -3.0f);
	Cube();
	~Cube();
};


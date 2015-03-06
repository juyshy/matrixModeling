#include "ShapeGenerator.h"
#include <glm\glm.hpp>
#include <Vertex.h>
#include <vector>
#define NUM_ARRAY_ELEMENTS(a)  sizeof(a) / sizeof(*a)

using glm::vec3;

glm::vec3 randomColor()
{
	glm::vec3 ret;
	ret.x = rand() / (float)RAND_MAX;
	ret.y = rand() / (float)RAND_MAX;
	ret.z = rand() / (float)RAND_MAX;
	return ret;
}

ShapeData ShapeGenerator::makeTriangle(){
 
	ShapeData ret;
	Vertex myTri[] = {
		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),

		vec3(-1.0f, -1.0f, +0.0f),
		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),

		vec3(+1.0f, -1.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
 
	};
	ret.numVertices = NUM_ARRAY_ELEMENTS(myTri) ;
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, myTri, sizeof(myTri));
 
	GLushort indices[] = { 0, 1, 2 };
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices) ;
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));
	return ret;
}


ShapeData ShapeGenerator::makeCube(){
	ShapeData ret;

	//ret.vertPositions =
	std::vector<vec3> vertPositions {
		vec3(-1.0f, +1.0f, +1.0f),  // 0
		vec3(+1.0f, +1.0f, +1.0f),  // 1
		vec3(+1.0f, +1.0f, -1.0f),  // 2
		vec3(-1.0f, +1.0f, -1.0f),  // 3
		vec3(-1.0f, +1.0f, -1.0f),  // 4
		vec3(+1.0f, +1.0f, -1.0f),  // 5
		vec3(+1.0f, -1.0f, -1.0f),  // 6
		vec3(-1.0f, -1.0f, -1.0f),  // 7
		vec3(+1.0f, +1.0f, -1.0f),  // 8
		vec3(+1.0f, +1.0f, +1.0f),  // 9
		vec3(+1.0f, -1.0f, +1.0f),  // 10
		vec3(+1.0f, -1.0f, -1.0f),  // 11
		vec3(-1.0f, +1.0f, +1.0f),  // 12
		vec3(-1.0f, +1.0f, -1.0f),  // 13
		vec3(-1.0f, -1.0f, -1.0f),  // 14
		vec3(-1.0f, -1.0f, +1.0f),  // 15
		vec3(+1.0f, +1.0f, +1.0f),  // 16
		vec3(-1.0f, +1.0f, +1.0f),  // 17
		vec3(-1.0f, -1.0f, +1.0f),  // 18
		vec3(+1.0f, -1.0f, +1.0f),  // 19
		vec3(+1.0f, -1.0f, -1.0f),  // 20
		vec3(-1.0f, -1.0f, -1.0f),  // 21
		vec3(-1.0f, -1.0f, +1.0f),  // 22
		vec3(+1.0f, -1.0f, +1.0f),  // 23
	};
	std::vector<vec3> norlmals{
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+0.0f, +1.0f, +0.0f),  // Normal
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+0.0f, +0.0f, -1.0f),  // Normal
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(+1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(-1.0f, +0.0f, +0.0f),  // Normal
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(+0.0f, +0.0f, +1.0f),  // Normal
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
		vec3(+0.0f, -1.0f, +0.0f),  // Normal
	};

	std::vector<vec3> colors;
	for (uint i = 0; i < 24; ++i)
		colors.push_back(randomColor());
	//ret.colors = colors;

	/*std::vector<Vertex[24]> cubes;*/
	uint count = 0;
	Vertex stackVerts[24 /** 100 * 50*/];
	//for (uint i = 0; i < 100; i++){
	//	for (uint j = 0; j < 50; j++){


			//Vertex stackVerts1[24];
			for (uint k = 0; k < 24; ++k){
				stackVerts[k].position = vertPositions.at(k);//  +vec3(i * 10 - 100.0f, 0.0f, j * 10 - 100.0f);
				stackVerts[k].color = colors.at(k);
				stackVerts[k].normal = norlmals.at(k);
				count++;
			}
	/*	}
	}*/
	//Vertex stackVerts[] =
	//{
	//	vec3(-1.0f, +1.0f, +1.0f),  // 0
	//	vec3(+1.0f, +0.0f, +0.0f),	// Color
	//	vec3(+0.0f, +1.0f, +0.0f),  // Normal
	//	vec3(+1.0f, +1.0f, +1.0f),  // 1
	//	vec3(+0.0f, +1.0f, +0.0f),	// Color
	//	vec3(+0.0f, +1.0f, +0.0f),  // Normal
	//	vec3(+1.0f, +1.0f, -1.0f),  // 2
	//	vec3(+0.0f, +0.0f, +1.0f),  // Color
	//	vec3(+0.0f, +1.0f, +0.0f),  // Normal
	//	vec3(-1.0f, +1.0f, -1.0f),  // 3
	//	vec3(+1.0f, +1.0f, +1.0f),  // Color
	//	vec3(+0.0f, +1.0f, +0.0f),  // Normal

	//	vec3(-1.0f, +1.0f, -1.0f),  // 4
	//	vec3(+1.0f, +0.0f, +1.0f),  // Color
	//	vec3(+0.0f, +0.0f, -1.0f),  // Normal
	//	vec3(+1.0f, +1.0f, -1.0f),  // 5
	//	vec3(+0.0f, +0.5f, +0.2f),  // Color
	//	vec3(+0.0f, +0.0f, -1.0f),  // Normal
	//	vec3(+1.0f, -1.0f, -1.0f),  // 6
	//	vec3(+0.8f, +0.6f, +0.4f),  // Color
	//	vec3(+0.0f, +0.0f, -1.0f),  // Normal
	//	vec3(-1.0f, -1.0f, -1.0f),  // 7
	//	vec3(+0.3f, +1.0f, +0.5f),  // Color
	//	vec3(+0.0f, +0.0f, -1.0f),  // Normal

	//	vec3(+1.0f, +1.0f, -1.0f),  // 8
	//	vec3(+0.2f, +0.5f, +0.2f),  // Color
	//	vec3(+1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(+1.0f, +1.0f, +1.0f),  // 9
	//	vec3(+0.9f, +0.3f, +0.7f),  // Color
	//	vec3(+1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(+1.0f, -1.0f, +1.0f),  // 10
	//	vec3(+0.3f, +0.7f, +0.5f),  // Color
	//	vec3(+1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(+1.0f, -1.0f, -1.0f),  // 11
	//	vec3(+0.5f, +0.7f, +0.5f),  // Color
	//	vec3(+1.0f, +0.0f, +0.0f),  // Normal

	//	vec3(-1.0f, +1.0f, +1.0f),  // 12
	//	vec3(+0.7f, +0.8f, +0.2f),  // Color
	//	vec3(-1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(-1.0f, +1.0f, -1.0f),  // 13
	//	vec3(+0.5f, +0.7f, +0.3f),  // Color
	//	vec3(-1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(-1.0f, -1.0f, -1.0f),  // 14
	//	vec3(+0.4f, +0.7f, +0.7f),  // Color
	//	vec3(-1.0f, +0.0f, +0.0f),  // Normal
	//	vec3(-1.0f, -1.0f, +1.0f),  // 15
	//	vec3(+0.2f, +0.5f, +1.0f),  // Color
	//	vec3(-1.0f, +0.0f, +0.0f),  // Normal

	//	vec3(+1.0f, +1.0f, +1.0f),  // 16
	//	vec3(+0.6f, +1.0f, +0.7f),  // Color
	//	vec3(+0.0f, +0.0f, +1.0f),  // Normal
	//	vec3(-1.0f, +1.0f, +1.0f),  // 17
	//	vec3(+0.6f, +0.4f, +0.8f),  // Color
	//	vec3(+0.0f, +0.0f, +1.0f),  // Normal
	//	vec3(-1.0f, -1.0f, +1.0f),  // 18
	//	vec3(+0.2f, +0.8f, +0.7f),  // Color
	//	vec3(+0.0f, +0.0f, +1.0f),  // Normal
	//	vec3(+1.0f, -1.0f, +1.0f),  // 19
	//	vec3(+0.2f, +0.7f, +1.0f),  // Color
	//	vec3(+0.0f, +0.0f, +1.0f),  // Normal

	//	vec3(+1.0f, -1.0f, -1.0f),  // 20
	//	vec3(+0.8f, +0.3f, +0.7f),  // Color
	//	vec3(+0.0f, -1.0f, +0.0f),  // Normal
	//	vec3(-1.0f, -1.0f, -1.0f),  // 21
	//	vec3(+0.8f, +0.9f, +0.5f),  // Color
	//	vec3(+0.0f, -1.0f, +0.0f),  // Normal
	//	vec3(-1.0f, -1.0f, +1.0f),  // 22
	//	vec3(+0.5f, +0.8f, +0.5f),  // Color
	//	vec3(+0.0f, -1.0f, +0.0f),  // Normal
	//	vec3(+1.0f, -1.0f, +1.0f),  // 23
	//	vec3(+0.9f, +1.0f, +0.2f),  // Color
	//	vec3(+0.0f, -1.0f, +0.0f),  // Normal

	//};
	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));
//	std::vector<GLushort> indicesVector 
	GLushort stackIndices[] = { 
		0, 1, 2 , 0, 2, 3, // top
		4,5,6, 4,6,7, // front
		8,9,10, 8,10,11, // right
		12,13,14, 12, 14,15, // left
		16,17, 18, 16, 18, 19, // back
		20,22, 21, 20, 23,22, // bottom
	};
	//GLushort stackIndices[36 * 50 * 100];
	//for (uint i = 0; i < 50 * 100; i++)
	//	for (uint j = 0; j < 36; j++)
	//		stackIndices[i * 36 + j] = indicesVector.at(j) + i*36;

	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));
	return ret;
}

ShapeData ShapeGenerator::makeArrow()
{
	ShapeData ret;
	Vertex stackVerts[] =
	{
		// Top side of arrow head
		vec3(+0.00f, +0.25f, -0.25f),         // 0
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.50f, +0.25f, -0.25f),         // 1
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.00f, +0.25f, -1.00f),         // 2
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.50f, +0.25f, -0.25f),         // 3
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		// Bottom side of arrow head
		vec3(+0.00f, -0.25f, -0.25f),         // 4
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 5
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 6
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 7
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		// Right side of arrow tip
		vec3(+0.50f, +0.25f, -0.25f),         // 8
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.00f, +0.25f, -1.00f),         // 9
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 10
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 11
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(0.83205032f, 0.00f, -0.55470026f), // Normal
		// Left side of arrow tip
		vec3(+0.00f, +0.25f, -1.00f),         // 12
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(-0.50f, +0.25f, -0.25f),         // 13
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(+0.00f, -0.25f, -1.00f),         // 14
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 15
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.55708605f, 0.00f, -0.37139067f), // Normal
		// Back side of arrow tip
		vec3(-0.50f, +0.25f, -0.25f),         // 16
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.50f, +0.25f, -0.25f),         // 17
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(-0.50f, -0.25f, -0.25f),         // 18
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.50f, -0.25f, -0.25f),         // 19
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		// Top side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 20
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 21
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, +1.00f),         // 22
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, -0.25f),         // 23
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +1.00f, +0.00f),         // Normal
		// Bottom side of back of arrow
		vec3(+0.25f, -0.25f, -0.25f),         // 24
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 25
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 26
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, -0.25f),         // 27
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -1.00f, +0.00f),         // Normal
		// Right side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 28
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, -0.25f),         // 29
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 30
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 31
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+1.00f, +0.00f, +0.00f),         // Normal
		// Left side of back of arrow
		vec3(-0.25f, +0.25f, -0.25f),         // 32
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, -0.25f),         // 33
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 34
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		vec3(-0.25f, +0.25f, +1.00f),         // 35
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-1.00f, +0.00f, +0.00f),         // Normal
		// Back side of back of arrow
		vec3(-0.25f, +0.25f, +1.00f),         // 36
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.25f, +0.25f, +1.00f),         // 37
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(-0.25f, -0.25f, +1.00f),         // 38
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
		vec3(+0.25f, -0.25f, +1.00f),         // 39
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.00f, +0.00f, +1.00f),         // Normal
	};

	GLushort stackIndices[] = {
		0, 1, 2, // Top
		0, 2, 3,
		4, 6, 5, // Bottom
		4, 7, 6,
		8, 10, 9, // Right side of arrow tip
		8, 11, 10,
		12, 15, 13, // Left side of arrow tip
		12, 14, 15,
		16, 19, 17, // Back side of arrow tip
		16, 18, 19,
		20, 22, 21, // Top side of back of arrow
		20, 23, 22,
		24, 25, 26, // Bottom side of back of arrow
		24, 26, 27,
		28, 30, 29, // Right side of back of arrow
		28, 31, 30,
		32, 33, 34, // Left side of back of arrow
		32, 34, 35,
		36, 39, 37, // Back side of back of arrow
		36, 38, 39,
	};

	ret.numVertices = sizeof(stackVerts) / sizeof(*stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	ret.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));
	return ret;
}


ShapeData ShapeGenerator::makePlaneVerts(uint dimensions)
{
	ShapeData ret;
	ret.numVertices = dimensions * dimensions;
	int half = dimensions / 2;
	ret.vertices = new Vertex[ret.numVertices];
	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			Vertex& thisVert = ret.vertices[i * dimensions + j];
			thisVert.position.x = j - half;
			thisVert.position.z = i - half;
			thisVert.position.y = 0;
			thisVert.normal = glm::vec3(0, 1, 0);
			thisVert.color = randomColor();
		}
	}
	return ret;
}

ShapeData ShapeGenerator::makePlaneIndices(uint dimensions)
{
	ShapeData ret;
	ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
	ret.indices = new unsigned short[ret.numIndices];
	int runner = 0;
	for (int row = 0; row < dimensions - 1; row++)
	{
		for (int col = 0; col < dimensions - 1; col++)
		{
			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;

			ret.indices[runner++] = dimensions * row + col;
			ret.indices[runner++] = dimensions * row + col + dimensions + 1;
			ret.indices[runner++] = dimensions * row + col + 1;
		}
	}
	assert(runner = ret.numIndices);
	return ret;
}

ShapeData ShapeGenerator::makePlane(uint dimensions)
{
	ShapeData ret = makePlaneVerts(dimensions);
	ShapeData ret2 = makePlaneIndices(dimensions);
	ret.numIndices = ret2.numIndices;
	ret.indices = ret2.indices;
	return ret;
}


ShapeData ShapeGenerator::generateNormals(const ShapeData& data)
{
	ShapeData ret;
	ret.numVertices = data.numVertices * 2;
	ret.vertices = new Vertex[ret.numVertices];
	glm::vec3 white(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < data.numVertices; i++)
	{
		uint vertIndex = i * 2;
		Vertex& v1 = ret.vertices[vertIndex];
		Vertex& v2 = ret.vertices[vertIndex + 1];
		const Vertex& sourceVertex = data.vertices[i];
		v1.position = sourceVertex.position;
		v2.position = sourceVertex.position + sourceVertex.normal;
		v1.color = v2.color = white;
	}

	ret.numIndices = ret.numVertices;
	ret.indices = new GLushort[ret.numIndices];
	for (int i = 0; i < ret.numIndices; i++)
		ret.indices[i] = i;
	return ret;
}

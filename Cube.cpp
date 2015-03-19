#include "Cube.h"


#include  <iostream>

#include <vector>
#include "glm/glm.hpp"
using namespace std;
using   glm::vec3;

Cube::Cube()
{
	

}


// create binarynumber as vector from num
void makeBinaryArray(int num, vector<int> *barray, int bits){

	for (int i = bits - 1; i >= 0; i--) {
		//cout << ((num >> i) & 1);
		int binelem = ((num >> i) & 1);
		barray->push_back(binelem);

	}
}

// create all binarynumbers in the bits range as vector of int vectors 
void makeBinaryList(int bits, vector<vector<int>> *binarylist){
	int range = pow(2, bits);
	for (int i = 0; i < range; i++) {
		vector<int> binary;
		makeBinaryArray(i, &binary, bits);
		binarylist->push_back(binary);

	}
}

void makeCubeVerts(vector<vec3> * vertexes, float cubePointMultiplier)
{
	const int bits = 3;

	vector<vector<int>> binarylist; // list of all binary numbers in bits range
	makeBinaryList(bits, &binarylist);

	const vector<int> plusminus{ 1, -1 };

	for (unsigned int i = 0; i < binarylist.size(); i++) {
		cout << i << ": ";
		for (int j = 0; j < 3; j++) {
			//cout << binarylist.at(i).at(j); 
			//cout <<   ", ";
			cout << plusminus.at(binarylist.at(i).at(j)) * cubePointMultiplier;
			cout << ", ";

		}
		cout << endl;
		vertexes->push_back(
			vec3(plusminus.at(binarylist.at(i).at(0))* cubePointMultiplier,
			plusminus.at(binarylist.at(i).at(1))* cubePointMultiplier,
			plusminus.at(binarylist.at(i).at(2))* cubePointMultiplier)
			);
	}
}


void swapTwoElementsInVectorAt(vector<uint> * vector1, uint swapIndex)
{

	uint temp = vector1->at(swapIndex);
	vector1->at(swapIndex) = vector1->at(swapIndex + 1);
	vector1->at(swapIndex + 1) = temp;
}

void Cube::normalsData()
{
	basenormals = {
		vec3(1, 0, 0), vec3(-1, 0, 0),
		vec3(0, 0, 1), vec3(0, 0, -1),
		vec3(0, 1, 0), vec3(0, -1, 0)
	};
	for (uint i = 0; i < 36; i++)
		normalIndexes.push_back(i / 6);
}
void Cube::createGeometry()
{

 
	float cubePointMultiplier = cubeSize / 2.0f;
	 
	makeCubeVerts(&vertexes, cubePointMultiplier);
	vertexes;

	const vector<uint> baseIndexes{ 0, 1, 2, 3, 4, 5, 6, 7 };
	const vector<uint> baseRIndexes{ 0, 1, 2, 3 };
	const vector<uint> baseLIndexes{ 4, 5, 6, 7 };
	/*

	7 -------- 3
	/ 		/ |
	6-------- 2  |
	|  5      |  1
	|         | /
	4 ------- 0

	*/

	// face indexes: right and left side:
	vector<uint> faceindexes = baseIndexes;

	// add front, back, top, bottom side face indexes:
	const vector<uint> constrctIndexes{ 0, 2, 1, 3, 2, 3, 1, 0 };
	for (auto i : constrctIndexes){
		faceindexes.push_back(
			baseLIndexes.at(i)
			);
		faceindexes.push_back(
			baseRIndexes.at(i)
			);
	}

	// mirror indexes on left side
	swapTwoElementsInVectorAt(&faceindexes, 4);
	swapTwoElementsInVectorAt(&faceindexes, 6);
	// mirror indexes on back side
	swapTwoElementsInVectorAt(&faceindexes, 12);
	swapTwoElementsInVectorAt(&faceindexes, 14);
	// mirror indexes on bottom 
	swapTwoElementsInVectorAt(&faceindexes, 20);
	swapTwoElementsInVectorAt(&faceindexes, 22);
	faceindexes;

	/*

	7 -------- 3
	/ 		   / |
	6-------- 2  |
	|  5      |  1
	|         | /
	4 ------- 0

	*/
	// faceindexes should now be:
	// 0, 1, 2, 3, 5, 4, 7, 6, 
	// 4, 0, 6, 2, 1, 5, 3, 7, 
	// 6, 2, 7, 3, 1, 5, 0, 4	

	const vector<uint> triangleIndexes{ 2, 0, 1, 1, 3, 2 };
	 
	for (uint i = 0; i < 6; i++)
	{
		for (uint indx : triangleIndexes)
			indexes.push_back(faceindexes.at(i * 4 + indx));
	}

	indexes;
	/*
	7 -------- 3
	/ 		   / |
	6-------- 2  |
	|  5      |  1
	|         | /
	4 ------- 0
	*/
	// indexes should now be:
	// 2,0,1,1,3,2,
	// 7,5,4,4,6,7,
	// 6,4,0,0,2,6,
	// 3,1,5,5,7,3,
	// 7,6,2,2,3,7,
	// 0,1,5,5,4,0	


	 
}



void Cube::prepareVertexes() {

	// prepare drawing vertexes and normals from indexes
	glm::vec3 norml;
	 
	// create vector of vertexes and normals
	for (uint i  : indexes) {
		glm::vec3 vrtx1 = vertexes.at(i);
		verteksit2r.push_back(vertexes.at(i));
		// lasketaan normaalit


	}
	for (uint i : normalIndexes) 
		normals2r.push_back(basenormals.at(i));
 
}

void Cube::createCube()
{
	
	  normalsData();
	  createGeometry();
	  prepareVertexes();
	  createVbos();
}

void Cube::createVbos(){
	// VBOs:

	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verteksit2r.size(), &verteksit2r[0], GL_STATIC_DRAW);


	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals2r.size(), &normals2r[0], GL_STATIC_DRAW);

 
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
 

}

void Cube::Draw(){

	glBindVertexArray(vao);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLES, 0,  36*6);
}

Cube::~Cube()
{
}

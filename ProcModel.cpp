
#include "ProcModel.h"
//#include "gl_utils.h"
//#include <GL/glew.h> // include GLEW and new version of GL on Windows
//#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
glm::vec3 computeNormal(glm::vec3 const & a, glm::vec3 const & b, glm::vec3 const & c)
{
	return glm::normalize(glm::cross(c - a, b - a));
}

ProcModel::ProcModel(MyModel * mainParameters) : mainParameters(mainParameters)
{
	
	//this->mainParameters = mainParameters;
	transXoffset = 0;
	transYoffset = -3.5;
	transZoffset = -6.5;

	triangleCount = mainParameters->triangleCount;//  5;
	extrudes = mainParameters->extrudes;// 40;
	
	extrudeRotationAngleStart = mainParameters->extrudeRotationAngleStart;// 0.2f;
	undulatingAmountX = mainParameters->undulatingAmountX;// 0.15f;// extrudeScale
	undulatingAmountZ = mainParameters->undulatingAmountZ;//  0.14f;
	undulatingRateX = mainParameters->undulatingRateX;  0.285f; // extrudeScale
	undulatingRateZ = mainParameters->undulatingRateZ; 0.285f;


	rotaUndulatingRate = mainParameters->rotaUndulatingRate; // 0.285f;
	rotaUndulatingAmount = mainParameters->rotaUndulatingAmount;// 0.07f;//0.15;
	extrudetranslate1 = mainParameters->extrudetranslate1;// glm::vec4(0.0f, 0.2f, 0.0f, 1.0f); // translation for extrudes

	rotaFirst = false; // rotation before translation in extrusion
	firstCap = true; // render first cap
	lastCap = true; // render last cap
	calcAverageNormas = false;
	colorsInVbo = false;
	color = glm::vec3(0.9f, 0.5f, 0.3f);
	// initialize
	initialize();
}

void ProcModel::initialize() {
	
	translateAmount = glm::vec3(0.0f, 0.0f, 0.0f);
	firstcaptriangleNums = firstCap ? (triangleCount * 3) : 0;
	lastcaptriangleNums = lastCap ? ((triangleCount - 2) * 3) : 0;
	vertexCount = firstcaptriangleNums + triangleCount * 3 * extrudes * 2 + lastcaptriangleNums;




}
void ProcModel::createModel() {
	createBase();
	doExtrusions();
	prapareVertexes();
	createVbos();
	ready2render = true;

}

void ProcModel::createCube() {
	extrudes = 1;
	createSquareBase();
	extrudetranslate1 = glm::vec4(0, 2, 0, 1);
	
	doExtrusions();
	prapareVertexes();
	createVbos();
	ready2render = true;

}


void ProcModel::createSquareBase(){
	firstcaptriangleNums = firstCap ? (4 * 3) : 0;
	lastcaptriangleNums = lastCap ? (2 * 3) : 0;
	triangleCount = 4;
	vertexCount = firstcaptriangleNums + triangleCount * 3 * extrudes * 2 + lastcaptriangleNums;
	origo = glm::vec4(0, 0, 0, 1);

	verteksit.push_back(origo);

	vrtx1 = glm::vec4(1, 0, 1, 1);
	verteksit.push_back(vrtx1);
	verteksit.push_back(glm::vec4(1, 0, -1, 1));
	verteksit.push_back(glm::vec4(-1, 0, -1, 1));
	verteksit.push_back(glm::vec4(-1, 0, 1, 1));

	indeksit.push_back(0);
	indeksit.push_back(1);
	indeksit.push_back(2);

	indeksit.push_back(0);
	indeksit.push_back(2);
	indeksit.push_back(3);

	indeksit.push_back(0);
	indeksit.push_back(3);
	indeksit.push_back(4);

	indeksit.push_back(0);
	indeksit.push_back(4);
	indeksit.push_back(1);
}

void ProcModel::createBase() {
	// first two vertexes
	origo = glm::vec4(0, 0, 0, 1);

	verteksit.push_back(origo);
	vrtx1 = glm::vec4(1, 0, 0, 1);
	verteksit.push_back(vrtx1);

	translatedVertex = vrtx1;
	// base vertexes:
	for (UINT i = 1; i < triangleCount; ++i) { // starting from the second vertex
		if (firstCap) {
			indeksit.push_back(0);
			indeksit.push_back(i + 1);
			indeksit.push_back(i);
		}
		rotaz = 360.0 / triangleCount * i * one_deg_in_rad;
		vrxTransMat = glm::rotate(glm::mat4(), (float)rotaz, glm::vec3(0, 1, 0));
		translatedVertex = vrxTransMat *  vrtx1;
		verteksit.push_back(translatedVertex);
	}
	// fill in the last triangle
	if (firstCap) {
		indeksit.push_back(0);
		indeksit.push_back(1);
		indeksit.push_back(triangleCount);
	}
}

void ProcModel::doExtrusions() { 	// extrusions
	glm::vec4	extrudetranslate = extrudetranslate1;
	//UINT xtrudestapes = 2;
	for (UINT j = 0; j < extrudes; ++j) {

		for (UINT i = 1; i < triangleCount + 1; ++i) {

			indeksit.push_back(i + triangleCount*j);
			indeksit.push_back(i + 1 + triangleCount*j);
			indeksit.push_back(triangleCount + i + triangleCount*j);

			if (i < triangleCount) { // not to exceed to vertexes
				indeksit.push_back(i + 1 + triangleCount*j);
				indeksit.push_back(triangleCount + i + 1 + triangleCount*j);
				indeksit.push_back(triangleCount + i + triangleCount*j);
			}
			else { // last triangle using  vertexes from previous round

				indeksit.push_back(i + 1 + triangleCount*j);
				indeksit.push_back(i + triangleCount*j); // i +
				indeksit.push_back(1 + triangleCount*j); // 1 +
			}

			laskuri++;

			extrudeScale = glm::vec3(sinf(j*undulatingRateX)*undulatingAmountX + 1, 1, cosf(j*undulatingRateZ)*undulatingAmountZ + 1);
			extrudeRotationAngle = (extrudeRotationAngleStart + cosf(j*rotaUndulatingRate)*rotaUndulatingAmount)  * static_cast<float>( one_deg_in_rad);
			if (rotaFirst) {
				vrxTransMat = glm::scale(glm::mat4(), extrudeScale);
				vrxTransMat = glm::rotate(vrxTransMat, extrudeRotationAngle, glm::vec3(0, 0, 1));
				vrxTransMat = glm::translate(vrxTransMat, glm::vec3(extrudetranslate.x, extrudetranslate.y, extrudetranslate.z));
			}
			else {
				vrxTransMat = glm::scale(glm::mat4(), extrudeScale);
				vrxTransMat = glm::translate(vrxTransMat, glm::vec3(extrudetranslate.x, extrudetranslate.y, extrudetranslate.z));
				vrxTransMat = glm::rotate(vrxTransMat, extrudeRotationAngle, glm::vec3(0, 0, 1));
			}
			translatedVertex = vrxTransMat *  verteksit[i + triangleCount*j]; // vertexes from previous extrude
			verteksit.push_back(translatedVertex);
		}
	}

	if (lastCap) {
		// different approach for last cap: 
		// fan topology starting from the last edge vertex
		UINT lastVertexIndex = verteksit.size() - 1;
		for (UINT i = 1; i < triangleCount - 1; ++i){

			indeksit.push_back(lastVertexIndex - 1 - i);
			indeksit.push_back(lastVertexIndex - i);
			indeksit.push_back(lastVertexIndex);
		}
	}


}
void ProcModel::prapareVertexes() {

	// prepare drawing vertexes and normals from indexes
	glm::vec3 norml;
	std::map<UINT, std::vector<glm::vec3>> sharedNormals;
	// create vector of vertexes and normals
	for (int i = 0; i < vertexCount; ++i) {
		glm::vec4 vrtx1 = verteksit.at(indeksit.at(i));
		verteksit2r.push_back(glm::vec3(vrtx1.x, vrtx1.y, vrtx1.z));
		// lasketaan normaalit
		if (i % 3 == 0) {
			glm::vec3 v1 = glm::vec3(vrtx1.x, vrtx1.y, vrtx1.z);
			glm::vec4 vrtx2 = verteksit.at(indeksit.at(i + 1));
			glm::vec3 v2 = glm::vec3(vrtx2.x, vrtx2.y, vrtx2.z);
			glm::vec4 vrtx3 = verteksit.at(indeksit.at(i + 2));
			glm::vec3 v3 = glm::vec3(vrtx3.x, vrtx3.y, vrtx3.z);

			norml = computeNormal(v3, v2, v1);
		}
		sharedNormals[indeksit.at(i)].push_back(norml);
		normals2r.push_back(norml);

		colors2r.push_back(color);

	}
	//sharedNormals;
	if (calcAverageNormas) {
		std::map<UINT,  glm::vec3> averagNormals;
		//for (UINT index : sharedNormals){

		for (auto it = sharedNormals.cbegin(); it != sharedNormals.cend(); ++it) {
				 
			std::vector<glm::vec3> normalsInIndex = (*it).second; // sharedNormals[index];
			glm::vec3 sum = glm::vec3(0,0,0);
			for (glm::vec3 normal : normalsInIndex)
				sum += normal;
			averagNormals[(*it).first] = glm::normalize(sum);
		}
		normals2r.clear();
		for (int i = 0; i < vertexCount; ++i) {
		 
			normals2r.push_back(averagNormals[indeksit.at(i)]);
		}
	}
	if (debugtxtsave) {
	std::string debugsisalto;
	std::ostringstream n;
	for (glm::vec3 normal : normals2r)
		n << "normal:" << normal[0] << ", " << normal[1] << ", " << normal[2] << "\n";

	debugsisalto += n.str();
	
	TallennaTiedosto("normaalit.txt", debugsisalto);
	}
}
void ProcModel::TallennaTiedosto(std::string tinimi, std::string sisalto)
{
	std::ofstream a_file(tinimi);
	// Outputs to example.txt through a_file
	a_file << sisalto;
	// Close the file stream explicitly
	a_file.close();
}

void ProcModel::deleteModel(){
	indeksit.clear();
	verteksit.clear();
	normals2r.clear();
	verteksit2r.clear();

}

void ProcModel::rebuid(){
	deleteModel();
	initialize();
	createModel();

}
void ProcModel::draw(){

 
	glBindVertexArray(vao);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void ProcModel::update(double current_seconds){
	elapsedTime = static_cast<float>(current_seconds);

	glUseProgram(shader_programme);

	// animation: rotating and moving the object in space
	double rotax = -sinf(elapsedTime / 4)*125.0 * one_deg_in_rad;
	double rotay = -sinf(elapsedTime / 4)*190.0 * one_deg_in_rad;

	//		glm::vec3 movement(sinf(current_seconds)*2.5, transYoffset, transZoffset + cosf(current_seconds / 4)*1.5);
	glm::vec3 movement(transXoffset, transYoffset, transZoffset);

	//model_mat = glm::scale(glm::mat4(), glm::vec3(0.5,0.5,0.5));
	model_mat = glm::translate(glm::mat4(), movement);
	updateMouse();
}

void ProcModel::rotaLimit(float &value){

	if (maxrota < abs(value)){
		if (value >= 0)
			value = glm::min(static_cast<float>(maxrota), value);
		else
			value = glm::max(-static_cast<float>(maxrota), value);
	}
 
}

void ProcModel::increaseTriagleCount(){
	triangleCount++;

}
void ProcModel::decreaseTriagleCount(){
	triangleCount--;
	if (triangleCount < 3){

		triangleCount = 3;
		std::cout << "3 is the minimum " << std::endl;

	}

}
void ProcModel::updateMouse() {


	//std::cout << "jeeee ";
	//translateAmount = glm::vec3(0.0f, 0.0f, 0.0f);

	translateVec += translateAmount * translateRate * elapsedTime;
	model_mat = glm::translate(model_mat, translateVec);
	translateAmount = glm::vec3(0.0f, 0.0f, 0.0f);

	if (!lmouseActive) {
		// limit axis:
		if (abs(rotationAmount.x) > abs(rotationAmount.y)){
			rotationAmount.y = 0;
		}
		else
		{
			rotationAmount.x = 0;
		}
		// deceleration
		if (abs(rotationAmount.y) > 0)
			rotationAmount.y *= 0.9995f;
		if (abs(rotationAmount.x) > 0)
			rotationAmount.x *= 0.9995f;

		rotaLimit(rotationAmount.x);
		rotaLimit(rotationAmount.y);


		if (maxrotax < abs(rotationAmount.y))
			maxrotax = rotationAmount.y;
		if (maxrotax < abs(rotationAmount.x))
			maxrotax = rotationAmount.x;
	}
 
	if (maxrotax > 0 && preCout != maxrotax) {
		std::cout << maxrotax << std::endl;
		preCout = maxrotax;
	}

	rotationVector += rotationAmount * rotationRate * elapsedTime;
	glm::vec2 rotavecChange = prevRotaVec - rotationVector;
	//if (rotavecChange.x > 0)

	prevRotaVec = rotationVector;
	model_mat = glm::rotate(model_mat, rotationVector.y, glm::vec3(1.0f, 0.0f, 0.0f));
	model_mat = rotate(model_mat, rotationVector.x, glm::vec3(0.0f, 1.0f, 0.0f));

}

void ProcModel::createVbos(){
	// VBOs:
	
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verteksit2r.size(), &verteksit2r[0], GL_STATIC_DRAW);

	
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals2r.size(), &normals2r[0], GL_STATIC_DRAW);

	if (colorsInVbo) {
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors2r.size(), &colors2r[0], GL_STATIC_DRAW);
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	if (colorsInVbo) {
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

}

 

void ProcModel::setShaders(/*glm::mat4 view, glm::mat4 proj*/){
//	//view_mat = view;
//	//proj_mat = proj;
//	  shader_programme = create_programme_from_files(
//		"test_vs.glsl", "test_fs.glsl");
//
//glUseProgram(shader_programme);
//int view_mat_location = glGetUniformLocation(shader_programme, "view_mat");
//glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, &view_mat[0][0]);
//int proj_mat_location = glGetUniformLocation(shader_programme, "projection_mat");
//glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, &proj_mat[0][0]);
//   model_mat_location = glGetUniformLocation(shader_programme, "model_mat");
//glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &model_mat[0][0]);

}

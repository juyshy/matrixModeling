//#include "gl_utils.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
//#include <GLFW/glfw3.h> // GLFW helper library

#include <string> 
#include <iostream>
#include <vector>
#include <cmath>

#define GL_LOG_FILE "gl.log"
#include "glm/glm.hpp"
//#include "glm/gtx/simd_mat4.hpp"
//#include <glm/vec3.hpp>// glm::vec3
//#include <glm/vec4.hpp>// glm::vec4
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm/geometric.hpp>// glm::cross, glm::normalize
#include <MyModel.h>

typedef unsigned int UINT;
const double pi = std::acos(-1);
const double  one_deg_in_rad = (2.0 * pi) / 360.0; // 0.017444444 // 


__declspec(align(16)) class ProcModel {
public:
	ProcModel();
	ProcModel(MyModel * mainParameters);
	//ProcModel(UINT triangles , UINT extrudes) : transZoffset(-7), transYoffset(-4), 
	//	triangleCount(triangles),
	//	extrudes(extrudes), extrudeRotationAngleStart(0.2){}
	void initialize();
	void createBase();
	void createSquareBase();
	void createCube();
	void createMultipleCubes();
	void  doExtrusions();
	void  prepareVertexes();
	void createVbos();
	void createMultiVbo();
	void setShaders(/*glm::mat4 view, glm::mat4 proj*/);
	void  draw();
	void update(double current_seconds);
	void updateMouse();
	std::vector<glm::vec4> get_verteksit() { return verteksit; };
	void createModel();
	void deleteModel();
	void rebuid();
	void setTriagleCount(UINT val) { triangleCount = val; };
	UINT getTriagleCount() { return triangleCount; };
	void increaseTriagleCount();
	void decreaseTriagleCount();
	void rotaLimit(float &value);

	void ProcModel::TallennaTiedosto(std::string tinimi, std::string sisalto);

	float transZoffset    ;
	float transYoffset    ; // translation in world coordinates
	float transXoffset;

	glm::vec3	extrudeScale; // (1.1, 1, 0.95); // translation for extrudes	
	UINT extrudes  ; // num of extrudes
	float extrudeRotationAngleStart  ; // agle for first extrude
	//float extrRotaAngleCounterMult = 0.01; // multiplier for updating angle in successive extrudes
	float undulatingRateX ; // extrudeScale
	float undulatingRateZ;
	float undulatingAmountX;
	float undulatingAmountZ ;

	float rotaUndulatingRate;
	float rotaUndulatingAmount ;//0.15;
	glm::vec4	extrudetranslate1; // // translation for extrudes

	bool rotaFirst ; // rotation before translation in extrusion
	bool firstCap; // render firs cap
	bool lastCap ; // render last cap
	std::vector<glm::vec3> verteksit2r; // collection of vertexes 2 render
	std::vector<glm::vec3> normals2r; // collection of normals 2 render
	std::vector<glm::vec3> colors2r;
	glm::mat4 model_mat = glm::mat4();
	GLuint shader_programme; 
	glm::mat4 view_mat;
	glm::mat4 proj_mat;
	int model_mat_location;
	//void setViewMat(glm::mat4 view);
	// mouse control:
	glm::vec3 translateAmount = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 rotationAmount = glm::vec2(0.0f, 0.0f);
	bool lmouseActive = false;
	glm::vec3 translateVec = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 color; 
	bool calcAverageNormas ;
	bool debugtxtsave = false;

	bool ready2render = false; // flag indicating when model is ready for render
	MyModel *mainParameters;
	bool colorsInVbo;

	uint num_cubes;
	uint num_cubesx  ;

	uint num_cubesy ;
	uint num_cubesz  ;
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
		void operator delete(void* p)
	{
		_mm_free(p);
	}
private:
	
	UINT triangleCount; // triangles in the base
	float elapsedTime;
	GLuint vao;
	GLuint normals_vbo;
	GLuint points_vbo;
	GLuint colors_vbo;
	double rotaz;
	std::vector<glm::vec4> verteksit;
	std::vector<glm::vec4> verteksit2;
	uint extrStartIndex;
	std::vector<UINT> indeksit;
	std::vector<UINT> indeksit2;
	glm::vec3 suunta;
	glm::mat4 vrxTransMat;
	UINT laskuri = 0;
	float extrudeRotationAngle;
	int lastcaptriangleNums;
	int firstcaptriangleNums;
	glm::vec4  origo;
	int vertexCount;
	glm::vec4  vrtx1;
	glm::vec4 translatedVertex;

	const float rotationRate = 0.02f;
	const float translateRate = 0.05f;
	glm::mat4 rotationMatrix;
	
	glm::vec2 rotationVector = glm::vec2(0.0f, 0.0f);
	glm::vec2 prevRotaVec = glm::vec2(0.0f, 0.0f);
	double maxrotax = 0;
	double maxrota = 0.01;
	double preCout = 0; // for debugging

};

 
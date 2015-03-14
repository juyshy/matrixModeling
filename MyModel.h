#pragma once
#include <glm\glm.hpp>
typedef unsigned int uint;

class MyModel
{
	public:
		glm::vec3 lightPosition;
		glm::vec3 sliderPosition;
 

		uint	triangleCount = 5;
		uint	extrudes = 40;

		float	extrudeRotationAngleStart = 0.2f;
		float	undulatingAmountX = 0.15f;// extrudeScale
		float	undulatingAmountZ = 0.14f;
		float	undulatingRateX = 0.285f; // extrudeScale
		float	undulatingRateZ = 0.285f;


		float	rotaUndulatingRate = 0.285f;
		float	rotaUndulatingAmount = 0.07f;//0.15;
		glm::vec4	extrudetranslate1 = glm::vec4(0.0f, 0.2f, 0.0f, 1.0f); // translation for extrudes

		bool	rotaFirst = false; // rotation before translation in extrusion
		bool	firstCap = true; // render first cap
		bool	lastCap = true; // render last cap
		bool	calcAverageNormas = false;
		glm::vec3	color = glm::vec3(0.9f, 0.5f, 0.3f);

		glm::vec2 scaleUndlAmountXSliderRange = glm::vec2(0.0f, 0.5f);

			

};
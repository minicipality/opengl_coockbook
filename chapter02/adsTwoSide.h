#ifndef ADS_TWO_REFLECTION_H
#define ADS_TWO_REFLECTION_H

#include "scene.h"
#include "glslprogram.h"
#include "teapot.h"

#include "cookbookogl.h"

#include "glm/gtc/matrix_transform.hpp"

using glm::vec4;
using glm::vec3;
using glm::mat4;

class ADSTwoReflection : public Scene
{
public:
	ADSTwoReflection();

	struct LightInfo {
		vec4 LightPosition;				// позиция источника света в видимых координатах
		vec3 La;						// интенсивность фонового света (ambient)
		vec3 Ld;						// интенсивность рассеянного свет (diffuse)
		vec3 Ls;						// интенсивность отраженного света (specular)
	};

	struct MaterialInfo {
		vec3 Ka;						// коэффициент отражения фонового света
		vec3 Kd;						// коэффициент отражения рассеянного света
		vec3 Ks;						// коэффициент отражения отраженного света
		float Shininess;				// показатель степени зеркального отражения
	};

	void initScene();
	void render();
	void resize(int, int);
	void update(float t);

	glm::mat4 model, view, projection;
private:
	GLSLProgram program;
	GLuint vaoHandle;
	Teapot teapot;

	LightInfo m_lightInfo;
	MaterialInfo m_materialInfo;

	void initShaders();

	void setMatrices();
};

#endif // ADS_TWO_REFLECTION_H

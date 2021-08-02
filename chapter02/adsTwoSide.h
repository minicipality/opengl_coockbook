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
		vec4 LightPosition;				// ������� ��������� ����� � ������� �����������
		vec3 La;						// ������������� �������� ����� (ambient)
		vec3 Ld;						// ������������� ����������� ���� (diffuse)
		vec3 Ls;						// ������������� ����������� ����� (specular)
	};

	struct MaterialInfo {
		vec3 Ka;						// ����������� ��������� �������� �����
		vec3 Kd;						// ����������� ��������� ����������� �����
		vec3 Ks;						// ����������� ��������� ����������� �����
		float Shininess;				// ���������� ������� ����������� ���������
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

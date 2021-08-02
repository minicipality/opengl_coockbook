#ifndef ADS_REFLECTION_H
#define ADS_REFLECTION_H

#include "scene.h"
#include "glslprogram.h"
#include "torus.h"

#include "cookbookogl.h"

#include "glm/gtc/matrix_transform.hpp"

using glm::vec4;
using glm::vec3;

class ADSReflection : public Scene
{
public:
	ADSReflection();

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
	Torus torus;
	
	LightInfo m_lightInfo;
	MaterialInfo m_materialInfo;

	void initShaders();

	void setMatrices();
};

#endif // ADS_REFLECTION_H

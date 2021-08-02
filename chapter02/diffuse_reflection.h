#ifndef DIFFUSE_REFLECTION_H
#define DIFFUSE_REFLECTION_H

#include "scene.h"
#include "glslprogram.h"
#include "torus.h"

#include "cookbookogl.h"

#include "glm/gtc/matrix_transform.hpp"

class DiffuseReflection: public Scene
{
public:
	DiffuseReflection();

	void initScene();
	void render();
	void resize(int, int);
	void update(float t);

	glm::mat4 model, view, projection;
private:

	GLSLProgram program;
	GLuint vaoHandle;
	Torus torus;

	void initShaders();

	void setMatrices();
};

#endif // DIFFUSE_REFLECTION_H

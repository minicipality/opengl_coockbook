#pragma once
#include "load_shader.h"
#include "glm/glm.hpp"

const double PI = 3.141592653589793; // 15 знаков после точки

class Introduction
{
private:
	GLuint vaoHandle;
	GLuint program;
	void init();
	void loadShaders();
	void loadShaders_uniform();
public:

	Introduction() {
		//loadShaders();
		loadShaders_uniform();
		init();
	};

	~Introduction() {};

	void render()
	{
		glBindVertexArray(vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//glBindVertexArray(0); // TODO - ??
	}
};
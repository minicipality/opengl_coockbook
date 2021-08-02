#include <iostream>

#include "adsTwoSide.h"

ADSTwoReflection::ADSTwoReflection() : teapot(13, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f)))
{}

void ADSTwoReflection::update(float t)
{

}

void ADSTwoReflection::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void ADSTwoReflection::initShaders()
{
	try
	{
		program.compileShader("shader/ads_two_reflection.vert");
		program.compileShader("shader/ads_two_reflection.frag");

		program.link();
		program.validate();
		program.use();
	}
	catch (GLSLProgramException& e)
	{
		std::cout << "Error create GLSL program: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	program.printActiveUniforms();
	program.printActiveAttribs();
}

void ADSTwoReflection::initScene()
{
	initShaders();

	glEnable(GL_DEPTH_TEST);

	// Видовая матрица
	// vec3(0.0f, 0.0f, 3.0f) - позиция камеры в мировом пространстве
	// vec3(0.0f, 0.0f, 0.0f) - координата цели в мировом пространстве
	// vec3(0.0f, 1.0f, 0.0f) - вектор, направленный вверх 
	view = glm::lookAt(glm::vec3(2.0f, 4.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	projection = glm::mat4(1.0f);

	m_lightInfo.Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	m_lightInfo.La = glm::vec3(0.4f, 0.4f, 0.4f);
	m_lightInfo.Ls = glm::vec3(0.1f, 0.1f, 0.1f);

	//
	m_materialInfo.Kd = glm::vec3(0.9f, 0.5f, 0.3f);
	m_materialInfo.Ka = glm::vec3(0.9f, 0.5f, 0.3f);
	m_materialInfo.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	m_materialInfo.Shininess = 100.f;

	program.setUniform("Material.Kd", m_materialInfo.Kd);
	program.setUniform("Material.Ka", m_materialInfo.Ka);
	program.setUniform("Material.Ks", m_materialInfo.Ks);
	program.setUniform("Material.Shininess", m_materialInfo.Shininess);
	//
	program.setUniform("Light.Ld", m_lightInfo.Ld);
	//program.setUniform("Light.Position", m_lightInfo.LightPosition);
	program.setUniform("Light.La", m_lightInfo.La);
	program.setUniform("Light.Ls", m_lightInfo.Ls);

	//program.setUniform("Light", &m_lightInfo);
	//program.setUniform("Material", &m_materialInfo);
}

void ADSTwoReflection::setMatrices()
{
	glm::mat4 ModelViewMatrix = view * model;
	program.setUniform("ModelViewMatrix", ModelViewMatrix);	        // матрица вида модели		

	// нормальная матрица - транспонированная обратная матрица , полученная на основе подматрицы 3х3 из верхнего левого угла матрицы вида модели
	glm::mat3 normalMatrix = glm::mat3(glm::vec3(ModelViewMatrix[0]), glm::vec3(ModelViewMatrix[1]), glm::vec3(ModelViewMatrix[2]));
	program.setUniform("NormalMatrix", normalMatrix);	// матрица нормалей
	//program.setUniform("ProjectionMatrix", ProjectionMatrix);	        // матрица проекции
	program.setUniform("MVP", projection * ModelViewMatrix);
}

void ADSTwoReflection::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec4 worldLight = glm::vec4(2.0f, 4.0f, 2.0f, 1.0f);
	
	model = glm::rotate(mat4(), glm::radians(20.f), vec3(0.f, 1.f, 0.f));
	m_lightInfo.LightPosition = view * model * worldLight; // позиция источника света в видимых координатах
	program.setUniform("Light.Position", m_lightInfo.LightPosition);

	model = mat4(1.f);
	model = glm::translate(model, vec3(0.0, -1.0, 0.0));
	model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));

	setMatrices();
	teapot.render();
}


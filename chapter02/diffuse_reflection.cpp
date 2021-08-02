#include <iostream>

#include "diffuse_reflection.h"

DiffuseReflection::DiffuseReflection(): torus(0.7f, 0.3f, 30, 30)
{}

void DiffuseReflection::update(float t)
{

}

void DiffuseReflection::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

void DiffuseReflection::initShaders()
{
	try
	{
		program.compileShader("shader/diffuse_reflection.vert");
		program.compileShader("shader/diffuse_reflection.frag");

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

void DiffuseReflection::initScene()
{
	initShaders();

	glEnable(GL_DEPTH_TEST);

	// матрица модели
	model = glm::mat4(1.0f);
	// поворот 3D вектора на заданный угол вокруг оси
	model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Видовая матрица
	// vec3(0.0f, 0.0f, 3.0f) - позиция камеры в мировом пространстве
	// vec3(0.0f, 0.0f, 0.0f) - координата цели в мировом пространстве
	// vec3(0.0f, 1.0f, 0.0f) - вектор, направленный вверх 
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	projection = glm::mat4(1.0f);
	//projection = glm::perspective<float>(glm::radians(10.0), 0.5, 0.1f, 100.f);

	glm::vec4 LightPosition = view * glm::vec4(5.0f, 5.0f, 2.0f, 1.0f);		// позиция источника света в видимых координатах
	glm::vec3 Kd = glm::vec3(0.9f, 0.5f, 0.3f);								// коэффициент рассеивания
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);								// интенсивность источника света

	program.setUniform("LightPosition", LightPosition);
	program.setUniform("Kd", Kd);						// коэффициент рассеивания
	program.setUniform("Ld", Ld);						// интенсивность источника света
}

void DiffuseReflection::setMatrices()
{
	glm::mat4 ModelViewMatrix = view * model;
	program.setUniform("ModelViewMatrix", ModelViewMatrix);	        // матрица вида модели		

	// нормальная матрица - транспонированная обратная матрица , полученная на основе подматрицы 3х3 из верхнего левого угла матрицы вида модели
	glm::mat3 normalMatrix = glm::mat3(glm::vec3(ModelViewMatrix[0]), glm::vec3(ModelViewMatrix[1]), glm::vec3(ModelViewMatrix[2]));
	program.setUniform("NormalMatrix", normalMatrix);	// матрица нормалей
   // program.setUniform("ProjectionMatrix", ProjectionMatrix);	        // матрица проекции
	program.setUniform("MVP", projection * ModelViewMatrix);
}

void DiffuseReflection::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setMatrices();
	torus.render();
}


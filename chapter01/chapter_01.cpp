#include "charpter_01.h"

#include "GL/glew.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cmath>

using namespace glm;

void Introduction::init()
{
#if 1
	float positionData[] = {
		-0.8f, -0.8f, 0.f,
		0.8f, -0.8f, 0.f,
		0.8f, 0.8f, 0.f,
		0.8f, 0.8f, 0.f,
		-0.8f, -0.8f, 0.f, 
		-0.8f, 0.8f, 0.f};

	float tcData[] = {
	  0.0f, 0.0f,
	  1.0f, 0.0f,
	  1.0f, 1.0f,
	  0.0f, 0.0f,
	  1.0f, 1.0f,
	  0.0f, 1.0f
	};

	//float colorData[] = {
	//	1.f, 0.f, 0.f,
	//	0.f, 1.f, 0.f,
	//	0.f, 0.f, 1.f };

	// создание и заполнение буфферных объектов
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint texBufferHandle = vboHandles[1];
	//GLuint colorBufferHandle = vboHandles[1];

	// заполнение буффера координат
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * 2 * sizeof(float), positionData, GL_STATIC_DRAW);

	// заполнение буффера цветов
	glBindBuffer(GL_ARRAY_BUFFER, texBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), tcData, GL_STATIC_DRAW);
 
	// создать обхект массива вершин
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	// активировать массивы вершин атрибутов
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
#if 1
	// закрепить индекс 0 за буфером с координатами
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// закрепить индекс 1 за буфером с цветами
	glBindBuffer(GL_ARRAY_BUFFER, texBufferHandle);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
#else
	glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(float) * 6);
	glBindVertexBuffer(1, texBufferHandle, 0, sizeof(float) * 6);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	// ROTATE
	//float angle = 30.f;
	//float cos_rotation = cos(angle);
	//float sin_rotation = sin(angle);
	//
	//float rotation[] = {
	//	cos_rotation, -sin_rotation, 0.f, 0.f,
	//	sin_rotation, cos_rotation, 0.f, 0.f,
	//	0.f, 0.f, 1.f, 0.f,
	//	0.f, 0.f, 0.f, 1.f
	//};
	//
	//mat4 rot = rotate(mat4(1.f), angle, vec3(0.f, 0.f, 1.f));
	//
	//GLuint location = glGetUniformLocation(program, "RotationMatrix");
	//if (location >= 0)
	//	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(rot));
	//	//glUniformMatrix4fv(location, 1, GL_TRUE, &rotation[0]);//&rot[0][0]);

	// получить индекс uniform блока
	GLuint blockIndex = glGetUniformBlockIndex(program, "BlobSettings");
	// выделить в памяти буфер
	GLint blockSize;
	glGetActiveUniformBlockiv(program, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
	GLubyte *blockBuffer;
	blockBuffer = (GLubyte *)malloc(blockSize);
	// получить смещение каждой переменной в блоке - узнать индексу всех переменных в блоке
	const GLchar* names[] = {"BlobSettings.InnerColor", "BlobSettings.OuterColor", 
							 "BlobSettings.RadiusInner", "BlobSettings.RadiusOuter"};

	GLuint indices[4];
	glGetUniformIndices(program, 4, names, indices);

	GLint offset[4];
	glGetActiveUniformsiv(program, 4, indices, GL_UNIFORM_OFFSET, offset);

	// записать требуемые данные ф буыер по соответсвующим индексам
	GLfloat outerColor[] = {0.f, 0.f, 0.f, 0.f};
	GLfloat innerColor[] = {1.f, 1.f, 0.75f, 1.f};
	GLfloat innerRadius = 0.25f, outerRadius = 0.45f;

	memcpy(blockBuffer + offset[0], innerColor, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[1], outerColor, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[2], &innerRadius, sizeof(GLfloat));
	memcpy(blockBuffer + offset[3], &outerRadius, sizeof(GLfloat));

	// создать буфферный обхект и скопировать в него данные
	GLuint uboHandle;
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboHandle);
}

void Introduction::loadShaders()
{
	ShaderInfo shaders[3];
	shaders[0].filename = "../glsl/basic.vert";
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].filename = "../glsl/basic.frag";
	shaders[1].type = GL_FRAGMENT_SHADER;
	shaders[2].type = GL_NONE;
	program = LoadShaders(shaders);
}

void Introduction::loadShaders_uniform()
{
	ShaderInfo shaders[3];
	shaders[0].filename = "../glsl/basic.vert";
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].filename = "../glsl/uniform_block.frag";
	shaders[1].type = GL_FRAGMENT_SHADER;
	shaders[2].type = GL_NONE;
	program = LoadShaders(shaders);
}
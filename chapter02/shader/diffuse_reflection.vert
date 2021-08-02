layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition;				// позиция источника света в видимых координатах
uniform vec3 Kd;						// коэффициент рассеивания
uniform vec3 Ld;						// интенсивность источника света

uniform mat4 ModelViewMatrix;	        // матрица вида модели		
uniform mat3 NormalMatrix;		        // матрица нормалей
//uniform mat4 ProjectionMatrix;	        // матрица проекции
uniform mat3 MVP;						// ProjectionMatrix * ModelViewMatrix

void main()
{
	// преобразовать нормаль и позицию в видимые координаты
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords = ModelViewMatrix * vec4(VertexPosition, 1.f);

	vec3 s = normalize(vec3(LightPosition - eyeCoords));

	// решить уравнение рассеянного отражения
	LightIntensity = Ld * Kd * max(dot(s, tnorm), 0.f);

	// преобразовать позицию в усеченные координаты и передать дальше
	gl_Position = MVP * vec4(VertexPosition, 1.f);
}
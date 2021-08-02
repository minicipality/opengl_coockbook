#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FrontColor;
out vec3 BackColor;

struct LightInfo {
	vec4 Position;				// позиция источника света в видимых координатах
	vec3 La;						// интенсивность фонового света (ambient)
	vec3 Ld;						// интенсивность рассеянного свет (diffuse)
	vec3 Ls;						// интенсивность отраженного света (specular)
};

uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka;						// коэффициент отражения фонового света
	vec3 Kd;						// коэффициент отражения рассеянного света
	vec3 Ks;						// коэффициент отражения отраженного света
	float Shininess;				// показатель степени зеркального отражения
};

uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;	        // матрица вида модели		
uniform mat3 NormalMatrix;		        // матрица нормалей
//uniform mat4 ProjectionMatrix;	    // матрица проекции
uniform mat4 MVP;						// ProjectionMatrix * ModelViewMatrix

void getEyeSpace(out vec3 norm, out vec4 position)
{
	norm = normalize(NormalMatrix * VertexNormal);
	position =  ModelViewMatrix * vec4(VertexPosition, 1.f);
}

vec3 phongModel(vec4 position, vec3 norm)
{
	// вектор на источник свет
	vec3 s = normalize(vec3(Light.Position - position));

	// направление на наблюдателя
	vec3 v = normalize(-position.xyz); // vec3(0.f, 0.f, 1.f);
	vec3 r = reflect(-s, norm); // отражает первый аргумент относительно второго

	// фоновый свет
	vec3 ambient = Light.La * Material.Ka;

	float sDotN = max(dot(s, norm), 0.f);
	// рассеянный свет
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;

	// отраженный свет
	vec3 specular = vec3(0.f);
	if(sDotN > 0.f)
		specular = Light.Ls * Material.Ks * 
					pow(max(dot(r, v), 0.f), Material.Shininess);
	
	//LightIntensity = ambient + diffuse + specular;
	return  ambient + diffuse + specular;
}

void main()
{
	// преобразовать нормаль и позицию в видимые координаты
	vec3 tnorm;        // = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords;    // = ModelViewMatrix * vec4(VertexPosition, 1.f);
	getEyeSpace(tnorm, eyeCoords);

	FrontColor = phongModel(eyeCoords, tnorm);
	BackColor = phongModel(eyeCoords, -tnorm);

	// преобразовать позицию в усеченные координаты и передать дальше
	gl_Position = MVP * vec4(VertexPosition, 1.f);
}
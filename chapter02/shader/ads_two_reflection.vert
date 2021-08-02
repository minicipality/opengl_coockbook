#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FrontColor;
out vec3 BackColor;

struct LightInfo {
	vec4 Position;				// ������� ��������� ����� � ������� �����������
	vec3 La;						// ������������� �������� ����� (ambient)
	vec3 Ld;						// ������������� ����������� ���� (diffuse)
	vec3 Ls;						// ������������� ����������� ����� (specular)
};

uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka;						// ����������� ��������� �������� �����
	vec3 Kd;						// ����������� ��������� ����������� �����
	vec3 Ks;						// ����������� ��������� ����������� �����
	float Shininess;				// ���������� ������� ����������� ���������
};

uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;	        // ������� ���� ������		
uniform mat3 NormalMatrix;		        // ������� ��������
//uniform mat4 ProjectionMatrix;	    // ������� ��������
uniform mat4 MVP;						// ProjectionMatrix * ModelViewMatrix

void getEyeSpace(out vec3 norm, out vec4 position)
{
	norm = normalize(NormalMatrix * VertexNormal);
	position =  ModelViewMatrix * vec4(VertexPosition, 1.f);
}

vec3 phongModel(vec4 position, vec3 norm)
{
	// ������ �� �������� ����
	vec3 s = normalize(vec3(Light.Position - position));

	// ����������� �� �����������
	vec3 v = normalize(-position.xyz); // vec3(0.f, 0.f, 1.f);
	vec3 r = reflect(-s, norm); // �������� ������ �������� ������������ �������

	// ������� ����
	vec3 ambient = Light.La * Material.Ka;

	float sDotN = max(dot(s, norm), 0.f);
	// ���������� ����
	vec3 diffuse = Light.Ld * Material.Kd * sDotN;

	// ���������� ����
	vec3 specular = vec3(0.f);
	if(sDotN > 0.f)
		specular = Light.Ls * Material.Ks * 
					pow(max(dot(r, v), 0.f), Material.Shininess);
	
	//LightIntensity = ambient + diffuse + specular;
	return  ambient + diffuse + specular;
}

void main()
{
	// ������������� ������� � ������� � ������� ����������
	vec3 tnorm;        // = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords;    // = ModelViewMatrix * vec4(VertexPosition, 1.f);
	getEyeSpace(tnorm, eyeCoords);

	FrontColor = phongModel(eyeCoords, tnorm);
	BackColor = phongModel(eyeCoords, -tnorm);

	// ������������� ������� � ��������� ���������� � �������� ������
	gl_Position = MVP * vec4(VertexPosition, 1.f);
}
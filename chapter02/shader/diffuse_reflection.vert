layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition;				// ������� ��������� ����� � ������� �����������
uniform vec3 Kd;						// ����������� �����������
uniform vec3 Ld;						// ������������� ��������� �����

uniform mat4 ModelViewMatrix;	        // ������� ���� ������		
uniform mat3 NormalMatrix;		        // ������� ��������
//uniform mat4 ProjectionMatrix;	        // ������� ��������
uniform mat3 MVP;						// ProjectionMatrix * ModelViewMatrix

void main()
{
	// ������������� ������� � ������� � ������� ����������
	vec3 tnorm = normalize(NormalMatrix * VertexNormal);
	vec4 eyeCoords = ModelViewMatrix * vec4(VertexPosition, 1.f);

	vec3 s = normalize(vec3(LightPosition - eyeCoords));

	// ������ ��������� ����������� ���������
	LightIntensity = Ld * Kd * max(dot(s, tnorm), 0.f);

	// ������������� ������� � ��������� ���������� � �������� ������
	gl_Position = MVP * vec4(VertexPosition, 1.f);
}
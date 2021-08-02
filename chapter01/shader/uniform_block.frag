#version 430

in vec3 TexCoord;
//out vec4 FragColor;
layout (location = 0) out vec4 FragColor;

layout (binding = 1) uniform BlobSettings {
	vec4 InnerColor;	// ���� � ������ �����
	vec4 OuterColor;	// ���� �� ��������� �����
	float RadiusInner;	// ������ ���������� �����
	float RadiusOuter;	// ������ ������� �����
} Blob;

void main()
{
	float dx = TexCoord.x - 0.5f;
	float dy = TexCoord.y - 0.5f;
	float dist = sqrt(dx * dx + dy * dy);
	FragColor = 
				mix(Blob.InnerColor, Blob.OuterColor, 
					smoothstep(Blob.RadiusInner, Blob.RadiusOuter, dist));

   //FragColor = vec4(1.0f, 0.f, 0.f, 1.0);
}
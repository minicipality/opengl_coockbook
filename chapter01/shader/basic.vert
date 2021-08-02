#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexColor;

//in vec3 VertexPosition;
//in vec3 VertexColor;
//in vec2 VertexTexCoord;

//out vec3 Color;
out vec3 TexCoord;

//uniform mat4 RotationMatrix;

void main()
{
	TexCoord = VertexColor;
	//Color = VertexColor;
	gl_Position = vec4(VertexPosition, 1.0);
	//gl_Position = RotationMatrix * vec4(VertexPosition, 1.0);
}
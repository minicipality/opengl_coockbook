#version 430

in vec3 FrontColor;
in vec3 BackColor;

layout (location = 0) out vec4 FragColor;

void main()
{
	if(gl_FrontFacing) 
		FragColor = vec4(FrontColor, 1.f);
	else 
		FragColor = mix(vec4(BackColor, 1.f), 
						vec4(1.f, 0.f, 0.f, 1.f), 0.7f);	
}
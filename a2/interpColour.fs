// The ShadedIdentity Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 410

out vec4 vFragColor;
in vec4 vVaryingColor;

void main(void)
{ 
	vFragColor = vVaryingColor;
}

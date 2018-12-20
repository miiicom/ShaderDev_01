#version 430
out vec4 FragmentColor;
in vec3 fragColor;
in vec4 vertexPositionWorld;
in vec3 normalWorld;

uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;

void main()
{	
	FragmentColor = vec4(fragColor,0.0);
}

#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec3 fragColor;

uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;

void main()
{	

	FragmentColor = vec4(fragColor,0.0);
}

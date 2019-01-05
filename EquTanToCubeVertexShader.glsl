#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentWorld;

uniform mat4 viewToProjectionMatrix;
uniform mat4 worldToViewMatrix;

out vec3 FragmentPositionWorld;

//Assume the object lies on world center, we can assume the model position is the world position

void main()
{
	gl_Position =viewToProjectionMatrix * worldToViewMatrix * vertexPositionModel;
	FragmentPositionWorld = vertexPositionModel.xyz;
}
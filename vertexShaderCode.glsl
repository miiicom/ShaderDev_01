#version 430

in layout(location=0) vec2 position;
in layout(location=1) vec3 vertexColor;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;

out vec3 theColor;

void main()
{
	vec4 Position = vec4(position, 0.0, 1.0);
	vec4 TranslatedPosition = modelTransformMatrix *  Position;
	vec4 ProjectedPositiopn = projectionMatrix * TranslatedPosition;

	gl_Position = ProjectedPositiopn;
	theColor = vertexColor;
}
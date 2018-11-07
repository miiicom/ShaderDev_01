#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normal;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPosition;
uniform mat4 fullTransformMatrix;

uniform mat4 modelToWorldTransMatrix;

out vec3 theNormal;
out vec3 thePosition;
out vec3 fragColor;

void main()
{
	vec4 Position = vec4(position, 1.0);
	gl_Position = fullTransformMatrix *  Position;
	theNormal = vec3(modelToWorldTransMatrix * vec4(normal,0));
	thePosition = vec3(modelToWorldTransMatrix * Position);
	fragColor = vertexColor;
}
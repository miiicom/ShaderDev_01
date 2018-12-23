#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentModel;

uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;

out vec3 fragColor;
out vec3 vertexPositionWorld;
out vec3 normalWorld;

void main()
{
	vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
	normalWorld = vec3(modelToWorldMatrix * vec4(normalModel,0.0));
	gl_Position = modelToProjectionMatrix * vertexPositionModel;
	fragColor = vertexColorModel.xyz;
}
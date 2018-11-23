#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentWorld;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPosition;
uniform mat4 modelToProjectionMatrix;
uniform mat3 WorldToViewMatrix;
uniform mat4 modelToWorldTransMatrix;

out vec3 NormalWorld;
out vec3 VertexPositionWorld;
out vec3 fragColor;
out vec2 fragmentUV0;

void main()
{
	
	gl_Position = modelToProjectionMatrix *  vertexPositionModel;
	NormalWorld = vec3(modelToWorldTransMatrix * vec4(normalModel,0));
	VertexPositionWorld = vec3(modelToWorldTransMatrix * vertexPositionModel);
	fragColor = vertexColorModel.xyz;
	fragmentUV0 = vertexUV0;
}
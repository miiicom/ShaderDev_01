#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentModel;

uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;
uniform sampler2D displacementMap;

out vec3 fragColor;
out vec3 vertexPositionWorld;
out vec3 normalWorld;
out vec2 uv0;

void main()
{
	//calculate and apply displacementlMap------------------------
	vec4 texel = texture2D(displacementMap, vertexUV0);
	float displacementAmount =5 *( 0.30 * texel.x + 0.59*texel.y + 0.11 * texel.z);
	vec4 vertexPositionOffsetted = vec4(vertexPositionModel.x,vertexPositionModel.y +displacementAmount,vertexPositionModel.z,vertexPositionModel.w);

	//-----------------------------------------------------

	normalWorld = vec3(modelToWorldMatrix * vec4(normalModel, 0));
	vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionOffsetted);

	gl_Position = modelToProjectionMatrix * vertexPositionOffsetted;
	fragColor = vertexColorModel.xyz;
	uv0 = vertexUV0;
}
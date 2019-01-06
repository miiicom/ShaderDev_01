#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentWorld;

out vec3 fragmentPositionWorld;

uniform mat4 viewToProjectionMatrix;
uniform mat4 worldToViewMatrix;

// assume the obj sits on world center so its world position is its model position 
void main()
{
	fragmentPositionWorld = vertexPositionModel.xyz;

	mat4 rotView = mat4(mat3(worldToViewMatrix)); // truncate the translation information
	vec4 clippedPosition = viewToProjectionMatrix * rotView * vertexPositionModel;

	gl_Position = clippedPosition.xyww;
}
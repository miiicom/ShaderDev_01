#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec3 fragColor;

uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;
uniform vec3 CameraDirectionWorld;
uniform vec3 lightPositionWorld;

void main()
{	
	vec3 normal = normalize(normalWorld);
	vec3 ViewDirectionWorld = normalize(CameraDirectionWorld - vertexPositionWorld);
	vec3 halfwayVector = normalize(ViewDirectionWorld + )

	FragmentColor = vec4(fragColor,0.0);
}

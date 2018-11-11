#version 430

out vec4 FragmentColor;
in vec3 NormalWorld;
in vec3 VertexPositionWorld;
in vec3 fragColor;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPositionWorld;

void main()
{
	vec3 lightVectorWorld = normalize(pointLightPositionWorld - VertexPositionWorld);
	float Intensity = dot(lightVectorWorld,normalize(NormalWorld));
	FragmentColor = vec4(Intensity,0.0,0.0,1.0);
}
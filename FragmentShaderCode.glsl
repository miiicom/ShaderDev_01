#version 430

out vec4 FragmentColor;

in vec3 NormalWorld;
in vec3 VertexPositionWorld;
in vec3 fragColor;
in vec2 vertexUV0;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPositionWorld;
uniform vec3 eyePositionWorld;

void main()
{	// diffuse
	vec3 lightVectorWorld = normalize(pointLightPositionWorld - VertexPositionWorld);
	float diffuseIntensity = dot(lightVectorWorld,normalize(NormalWorld));
	vec4 diffuseLight = vec4(diffuseIntensity,0.0,0.0,1.0);

	//specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, NormalWorld);
	vec3 eyeToWorld = normalize(eyePositionWorld - VertexPositionWorld);
	float SpecIntensity =  dot(eyeToWorld,reflectedLightVectorWorld);
	SpecIntensity = pow(SpecIntensity,16);
	vec4 specLight = vec4(SpecIntensity,SpecIntensity,0.0,1.0);
	FragmentColor = clamp(diffuseLight,0,1) + vec4(ambientLightUniform,0.0) +  clamp(specLight,0,1);
}
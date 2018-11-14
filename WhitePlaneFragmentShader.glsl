#version 430

out vec4 FragmentColor;
in vec3 NormalWorld;
in vec3 VertexPositionWorld;
in vec3 fragColor;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPositionWorld;
uniform vec3 eyePositionWorld;
uniform sampler2D normalTextureTC;

void main()
{	//readTexture 
	vec4 normalTextureInfo = texture()

	// diffuse
	vec3 lightVectorWorld = normalize(pointLightPositionWorld - VertexPositionWorld);
	float diffuseIntensity = dot(lightVectorWorld,normalize(NormalWorld));
	vec4 diffuseLight = vec4(diffuseIntensity,diffuseIntensity,diffuseIntensity,1.0);

	//specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, NormalWorld);
	vec3 eyeToWorld = normalize(eyePositionWorld - VertexPositionWorld);
	float SpecIntensity =  dot(eyeToWorld,reflectedLightVectorWorld);
	SpecIntensity = pow(SpecIntensity,20);
	vec4 specLight = vec4(0.0,SpecIntensity,SpecIntensity,1.0);
	//FragmentColor = clamp(diffuseLight,0,1) + vec4(ambientLightUniform,0.0) +  clamp(specLight,0,1);
}
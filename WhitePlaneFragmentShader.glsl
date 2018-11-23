#version 430

out vec4 FragmentColor;
in vec3 NormalWorld;
in vec3 VertexPositionWorld;
in vec3 fragColor;
in vec2 fragmentUV0;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPositionWorld;
uniform vec3 eyePositionWorld;
uniform sampler2D normalTextureTC;
uniform float time;
uniform vec2 SpriteOffset;

void main()
{	//Panner 
	//vec2 timeVector = vec2(time/60.0,0);
	//vec2 MovedFragmentUV0 = fragmentUV0 + timeVector;

	//SpriteLoc
	//vec2 ShrinkFragUV0 = vec2(fragmentUV0.x / 8,fragmentUV0.y/ 8);
	//vec2 MovedFragmentUV0 = ShrinkFragUV0 + SpriteOffset;

	//read Texture
	vec4 normalTextureInfo = texture(normalTextureTC,fragmentUV0);

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
	FragmentColor = clamp(diffuseLight,0,1) + vec4(ambientLightUniform,0.0) +  clamp(specLight,0,1);
	//FragmentColor = normalTextureInfo;
}
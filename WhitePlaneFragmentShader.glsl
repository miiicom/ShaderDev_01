#version 430

out vec4 FragmentColor;

in vec3 LightDirectionTangentSpace;
in vec3 ViewDirectionTangentSpace;
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
	float diffuseIntensity = dot(LightDirectionTangentSpace,normalTextureInfo.xyz);
	vec4 diffuseLight = vec4(diffuseIntensity,diffuseIntensity,diffuseIntensity,1.0);
	//specular
	vec3 reflectedLightVectorTangent = reflect(-LightDirectionTangentSpace, normalTextureInfo.xyz);
	float SpecIntensity =  dot(reflectedLightVectorTangent,ViewDirectionTangentSpace);
	SpecIntensity = pow(SpecIntensity,20);
	vec4 specLight = vec4(0.0,SpecIntensity,SpecIntensity,1.0);
	FragmentColor = clamp(diffuseLight,0,1) + vec4(ambientLightUniform,0.0) +  clamp(specLight,0,1);
	//FragmentColor = normalTextureInfo;
}
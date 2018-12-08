#version 430

out vec4 FragmentColor;

in mat3 TBNtangentToModel;
in vec3 vertexPositionWorld;
in vec3 fragColor;
in vec2 fragmentUV0;
in vec3 normalWorld;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPositionWorld;
uniform vec3 eyePositionWorld;
uniform mat4 modelToWorldTransMatrix;
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

	//read Texture and apply TBN matrix to sampled normal vector
	vec2 newfragmentUV0 = vec2(fragmentUV0.x, -fragmentUV0.y);
	vec4 normalTextureInfo = texture(normalTextureTC,newfragmentUV0) * 2.0 - 1.0;
	vec4 testNormalTangent = vec4(0.0,0.0,1.0,0.0);
	vec3 normalTextureInfoInObj = TBNtangentToModel * normalTextureInfo.xyz;
	vec3 normalTextureInfoInWorld = vec3(modelToWorldTransMatrix * vec4(normalTextureInfoInObj,1.0));

	//

	// diffuse
	vec3 lightVectorWorld = normalize(pointLightPositionWorld - vertexPositionWorld);
	float DiffuseIntensity = dot(lightVectorWorld, normalize(normalTextureInfoInWorld));
	vec4 diffuseLight = vec4(DiffuseIntensity, DiffuseIntensity,DiffuseIntensity,1.0);


	//specular
	vec3 reflectedLightVectorWorld = reflect( -pointLightPositionWorld,normalTextureInfoInWorld);
	vec3 eyeVectorWorld =  normalize(eyePositionWorld - vertexPositionWorld);
	float specularIntensity = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld),0,1);
	specularIntensity = pow(specularIntensity,50);
	vec4 speculatLight = vec4(0,0,specularIntensity,0);

	FragmentColor = vec4(ambientLightUniform,0.0) + clamp(diffuseLight,0,1) + speculatLight;
	//FragmentColor = vec4(normalTextureInfoInWorld.xyz,0.0);
	//FragmentColor = vec4( 1.0,1.0,1.0,0.0);
	//FragmentColor = normalTextureInfo;
}
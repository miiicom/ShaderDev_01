#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec3 fragColor;
in vec2 uv0;
in mat3 TBNtangentToModel;

struct PBR_parameters {
	vec3 albedo;
	float metallic;
	float roughness;
	float AO;
};
uniform PBR_parameters parameter;
uniform mat4 modelToProjectionMatrix; // MVP
uniform mat4 modelToWorldMatrix;
uniform vec3 CameraDirectionWorld;
uniform vec3 lightPositionWorld;
uniform float useNormal;

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   BRDFLUT;  
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;
uniform sampler2D metallicMap;
uniform sampler2D aoMap;


float PI = 3.141592653;

float  GeometrySchlickGGX(float DotProduct, float roughness){//check
	float r = (roughness + 1.0);
	float remappedRoughness = (r * r)/8.0;
	float nom = DotProduct;
	float denom = DotProduct * (1.0 - remappedRoughness) + remappedRoughness;

	return nom / denom;
}

float GeometrySmith(vec3 Normal, vec3 ViewDirection, vec3 LightDirection, float roughness){//check
	float NdotV = max(dot(Normal, ViewDirection), 0.0);
    float NdotL = max(dot(Normal, LightDirection), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) // check
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) // check
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}   

float DistributionGGX(vec3 normal, vec3 halfway, float Roughness) //check
{
    float RoughnessPower2 = Roughness*Roughness;
	float RoughnessPower4 = RoughnessPower2*RoughnessPower2;
    float NdotH  = max(dot(normal, halfway), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = max(RoughnessPower4,0.00001);
    float denom  = (NdotH2 * (RoughnessPower4 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

vec3 getNormalFromMap()				// translate from tangent space to world space should be done per vertex, let GPU do interpolation on NTB and then pass it down to fragment shader
{
    vec3 tangentNormal = texture(normalMap, uv0).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(vertexPositionWorld); //dFdx, dFdy — return the partial derivative of an argument with respect to x or y
    vec3 Q2  = dFdy(vertexPositionWorld);
    vec2 st1 = dFdx(uv0);				
    vec2 st2 = dFdy(uv0);

    vec3 N   = normalize(normalWorld);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);		//get tangent 
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec3 useTBNgetNormalMap(sampler normalMap, vec2 uv0){
	//read Texture and apply TBN matrix to sampled normal vector
	//vec2 newfragmentUV0 = vec2(uv0.x, -uv0.y);
	vec4 normalTextureInfo = texture(normalMap,uv0) * 2.0 - 1.0;
	vec4 testNormalTangent = vec4(0.0,0.0,1.0,0.0);
	vec3 normalTextureInfoInObj = TBNtangentToModel * normalTextureInfo.xyz;
	vec3 normalTextureInfoInWorld = vec3(modelToWorldMatrix * vec4(normalTextureInfoInObj,1.0));
	return normalTextureInfoInWorld;
}

void main()
{	
	vec3 albedo;
	vec3 normal;
	float roughness;
	float metallic;
	float ao;
	if(parameter.albedo.x == -1.0 && parameter.albedo.y == -1.0 && parameter.albedo.z == -1.0){
			albedo = pow(texture(albedoMap, uv0).xyz, vec3(2.2));
		}
		else{
			albedo = parameter.albedo;
		}

	if(parameter.roughness == -1.0){
			roughness = texture(roughnessMap,uv0).r;
		}
		else{
			roughness = parameter.roughness;
		}

	if(parameter.metallic == -1.0){
			metallic = texture(metallicMap,uv0).r;
		}
		else{
			metallic = parameter.metallic;
		}

	if(parameter.AO == -1.0){
			ao = texture(aoMap,uv0).r;
		}
		else{
			ao = parameter.AO;
		}

	//vec3 normalizedNormalWorld = normalize(normalWorld);
	//vec3 normal = normalize(normalWorld);
	if(useNormal == -1.0){
			normal = normalize(normalWorld);
		}
		else{
			normal = getNormalFromMap();
		}

	vec3 ViewDirectionWorld = normalize(CameraDirectionWorld- vertexPositionWorld);
	vec3 reflectVector = normalize(reflect(-ViewDirectionWorld, normal));
	//-----------------------
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 Lo = vec3(0.0);
	//-------------------------------------------------------------------------
	
	vec3 lightDirection = normalize(lightPositionWorld - vertexPositionWorld);
	vec3 halfwayVector = normalize(ViewDirectionWorld + lightDirection);
	
	// radiance
	float lightdistance = length(lightPositionWorld - vertexPositionWorld);
	float attenuation = 1.0 / (lightdistance * lightdistance);
	vec3 radiance = vec3(255.0,244.0,229.0) * attenuation;

	// BRDF
	vec3 FrenelValue = fresnelSchlick(max(dot(halfwayVector,ViewDirectionWorld),0.0),F0);
	float NormalDistribution = DistributionGGX(normal, halfwayVector, roughness);
	float GeometryFunction = GeometrySmith(normal, ViewDirectionWorld, lightDirection,roughness);

	vec3 numerator = NormalDistribution * GeometryFunction * FrenelValue;
	float denominator = 4.0 * max(dot(normal,ViewDirectionWorld), 0.0) * max(dot(normal, lightDirection),0.0) + 0.001;
	vec3 specular = numerator / denominator;
	
	vec3 kS = FrenelValue;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;

	float NormalLightDot = max(dot(normal, lightDirection), 0.0);
	Lo += (kD * albedo / PI + specular) *  radiance * NormalLightDot;

	//calculate amibent based on IBL
	FrenelValue = fresnelSchlickRoughness(max(dot(normal,ViewDirectionWorld),0.0),F0,roughness);
	kS = FrenelValue;
	kD = 1.0 - kS;
	kD *= 1.0 - metallic;
	vec3 irradiance = texture(irradianceMap,normal).xyz;
	vec3 diffuse = irradiance * albedo;
	const float MAX_REFLECTION_LOD = 4.0;
	vec3 preFilteredColor = textureLod(prefilterMap, reflectVector * 0.1,  roughness * MAX_REFLECTION_LOD).xyz;    
	//vec3 preFilteredColor = vec3(0.0,1.0,0.0);
	vec2 BRDF = texture(BRDFLUT, vec2(max(dot(normal,ViewDirectionWorld),0.0),roughness)).xy;
	specular = preFilteredColor * (FrenelValue * BRDF.x + BRDF.y);

	vec3 ambient = (kD * diffuse + specular) * ao;


	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

	FragmentColor = vec4(color,1.0);

	//FragmentColor = vec4(ao,0.0,0.0,0.0);
	//FragmentColor = vec4(GeometryFunction,GeometryFunction,GeometryFunction,0.0);
	//FragmentColor = vec4(NormalDistribution,NormalDistribution,NormalDistribution,0.0);
	//FragmentColor = vec4(FrenelValue,0.0);
	//FragmentColor = vec4(fragColor,0.0);
}


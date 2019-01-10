#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec2 uv0;

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

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;
uniform sampler2D metallicMap;
uniform sampler2D aoMap;

float PI = 3.14159265359;

float  GeometrySchlickGGX(float DotProduct, float roughness){
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float nom = DotProduct;
	float denom = DotProduct * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 Normal, vec3 ViewDirection, vec3 LightDirection, float roughness){
	float NdotV = max(dot(Normal, ViewDirection), 0.0);
    float NdotL = max(dot(Normal, LightDirection), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 normal, vec3 halfway, float Roughness)
{
    float RoughnessPower2 = Roughness*Roughness;
	float RoughnessPower4 = RoughnessPower2*RoughnessPower2;
    float NdotH  = max(dot(normal, halfway), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = RoughnessPower4;
    float denom  = (NdotH2 * (RoughnessPower4 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

void main()
{	

	vec3 albedo;
	float roughness;
	float metallic;
	float ao;
	if(parameter.albedo.x == -1.0 && parameter.albedo.y == -1.0 && parameter.albedo.z == -1.0){
			albedo = pow(texture(albedoMap, uv0).xyz, vec3(2.2));
		}
		else{
			albedo = parameter.albedo;
		}

	vec3 normalmap = texture(normalMap, uv0).xyz;

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

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);

	vec3 normal = normalWorld;
	vec3 ViewDirectionWorld = normalize(CameraDirectionWorld - vertexPositionWorld);
	vec3 lightDirection = normalize(lightPositionWorld - vertexPositionWorld);
	vec3 halfwayVector = normalize(ViewDirectionWorld + lightDirection);

	// radiance
	float lightdistance = length(lightPositionWorld - vertexPositionWorld);
	float attenuation = 1.0 / (lightdistance * lightdistance);
	vec3 radiance = vec3(0.8,0.8,0.8) * attenuation;

	// BRDF
	vec3 FrenelValue = fresnelSchlick(max(dot(halfwayVector,ViewDirectionWorld),0.0),F0);
	float NormalDistribution = DistributionGGX(normal, halfwayVector, roughness);
	float GeometryFunction = GeometrySmith(normal, ViewDirectionWorld, lightDirection,roughness);
	
	vec3 kS = FrenelValue;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;

	vec3 numerator = NormalDistribution * GeometryFunction * FrenelValue;
	float denominator = 4.0 * max(dot(normal,ViewDirectionWorld), 0.0) * max(dot(normal, lightDirection),0.0);
	vec3 specular = numerator / max(denominator, 0.001);

	float NormalLightDot = max(dot(normal, lightDirection), 0.0);
	Lo += (kD * albedo / PI + specular) *  radiance * NormalLightDot;

	vec3 ambinent = vec3(0.03) * albedo * ao;
	vec3 color = ambinent + Lo;

	color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

	FragmentColor = vec4(color,1.0);

	//FragmentColor = vec4(ao,0.0,0.0,0.0);
	//FragmentColor = vec4(GeometryFunction,GeometryFunction,GeometryFunction,0.0);
	//FragmentColor = vec4(NormalDistribution,NormalDistribution,NormalDistribution,0.0);
	//FragmentColor = vec4(FrenelValue,0.0);
	//FragmentColor = vec4(fragColor,0.0);
}


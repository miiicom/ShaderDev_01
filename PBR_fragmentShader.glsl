#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec3 fragColor;

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

float PI = 3.141592653;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 normal, vec3 halfway, float Roughness)
{
    float RoughnessPower2 = Roughness*Roughness;
    float NdotH  = max(dot(normal, halfway), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = RoughnessPower2;
    float denom  = (NdotH2 * (RoughnessPower2 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

void main()
{	
	vec3 F0 = vec3(0.04);

	vec3 normal = normalWorld;
	vec3 ViewDirectionWorld = normalize(CameraDirectionWorld - vertexPositionWorld);
	vec3 lightDirection = normalize(lightPositionWorld - vertexPositionWorld);
	vec3 halfwayVector = normalize(ViewDirectionWorld + lightDirection);

	vec3 FrenelValue = fresnelSchlick(max(dot(halfwayVector,ViewDirectionWorld),0.0),F0);

	float NormalDistribution = DistributionGGX(normal, halfwayVector, parameter.roughness);
	
	FragmentColor = vec4(NormalDistribution,NormalDistribution,NormalDistribution,0.0);
	//FragmentColor = vec4(FrenelValue,0.0);
	//FragmentColor = vec4(fragColor,0.0);
}


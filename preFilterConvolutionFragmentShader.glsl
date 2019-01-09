#version 430

out vec4 FragmentColor;
in vec3 FragmentPositionWorld;
in vec2 fragmentUV0;

uniform samplerCube Cubemap;
uniform sampler2D roughnessMap;
uniform float parameter_roughness;

const float PI = 3.141592653;
float roughness;
// DistributioGGX we use on PBR fragment shader
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
//fancy way to generate a low discrepancy sequence. I don't know how it works...
float RadicalInverse_VdC(uint bits) 
{
     bits = (bits << 16u) | (bits >> 16u);
     bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
     bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
     bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
     bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
     return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}
//Add weight to each sample 
vec2 Hammersley(uint i, uint N)
{
	return vec2(float(i)/float(N), RadicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness)
{
    float a = roughness*roughness;
	
    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float sinTheta = sqrt(1.0 - cosTheta*cosTheta);
	
    // from spherical coordinates to cartesian coordinates
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;
	
    // from tangent-space vector to world-space sample vector
    vec3 up        = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);
	
    vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVec);
}  

void main()
{	
	if(parameter_roughness == -1.0){
			roughness = texture(roughnessMap,fragmentUV0).r;
		}
		else{
			roughness = parameter_roughness;
		}

	vec3 normal = normalize(FragmentPositionWorld);
	vec3 Reflection = normal;
	vec3 viewDriection = normal;

	const uint SAMPLE_COUNT = 1024u;
	float totalWeight = 0.0;
	vec3 prefilteredColor = vec3(0.0);
	for(uint i = 0u; i < SAMPLE_COUNT; ++i){
		vec2 Xi = Hammersley(i,SAMPLE_COUNT);
		vec3 H = ImportanceSampleGGX(Xi, normal, roughness);
		vec3 L = normalize(2.0 * dot(viewDriection, H) * H - viewDriection);

		float NdotL = max(dot(normal, L), 0.0);
		if(NdotL > 0.0){
			prefilteredColor += texture(Cubemap, L).xyz * NdotL;
			totalWeight += NdotL;
		}
	}
	prefilteredColor = prefilteredColor / totalWeight;
	FragmentColor = vec4(prefilteredColor, 1.0);
}



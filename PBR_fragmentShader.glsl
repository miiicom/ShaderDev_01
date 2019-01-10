#version 430
out vec4 FragmentColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;
in vec3 fragColor;
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

float PI = 3.141592653;

<<<<<<< HEAD
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
=======
float RemapRoughness(float Roughness, bool isIBL){
	if(isIBL){
		return Roughness * Roughness / 2.0;
	}else{
		return (Roughness + 1.0) * (Roughness + 1.0) / 8.0;
	}
}

float  GeometrySchlickGGX(float DotProduct, float roughness){
	float r = (roughness + 1.0);
	float remappedRoughness = (r*r) / 8.0;

	float nom = DotProduct;
	float denom = DotProduct * (1.0 - remappedRoughness) + remappedRoughness;
>>>>>>> parent of 170ec41... update

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------

void main()
{	
<<<<<<< HEAD
<<<<<<< HEAD
	
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

=======
	vec3 albedo = pow(texture(albedoMap, uv0).xyz, vec3(2.2));
>>>>>>> parent of 170ec41... update
=======
	vec3 albedo = texture(albedoMap, uv0).xyz;
>>>>>>> parent of 96bca73... gamma correction to make to color look right
	vec3 normalmap = texture(normalMap, uv0).xyz;
	float roughness = texture(roughnessMap,uv0).r;
	float metallic = texture(metallicMap,uv0).r;
	float ao = texture(aoMap,uv0).r;

    vec3 N = normalWorld;
    vec3 V = normalize(CameraDirectionWorld - vertexPositionWorld);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);

    // calculate per-light radiance
    vec3 L = normalize(lightPositionWorld - vertexPositionWorld);
    vec3 H = normalize(V + L);
    float distance = length(lightPositionWorld - vertexPositionWorld);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = vec3(0.8,0.8,0.8) * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
       
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3 specular = nominator / denominator;
    
    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallic;	  

    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0);        

    // add to outgoing radiance Lo
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
  
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo * ao;
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragmentColor = vec4(color, 1.0);
}
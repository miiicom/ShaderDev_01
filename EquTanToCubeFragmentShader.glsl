#version 430

out vec4 FragmentColor;
in vec3 FragmentPositionWorld;

uniform sampler2D equirectangularMap;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{	
	vec2 uv = SampleSphericalMap(normalize(FragmentPositionWorld));
	vec3 color = clamp(texture(equirectangularMap, uv).xyz,0.0,1.0);
	FragmentColor = vec4(color, 1.0);
}



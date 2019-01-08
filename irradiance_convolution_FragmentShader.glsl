#version 430

out vec4 FragmentColor;
in vec3 FragmentPositionWorld;

uniform samplerCube Cubemap;

const float PI = 3.141592653;

void main()
{	
	//Assume working on a hemi spher, so position information can be used as normal

	vec3 Normal = normalize(FragmentPositionWorld);

	vec3 irradiance = vec3(0.0);

	// here calcualate three canonical vertors for tangent space . tangent and binormal are on Tangent space
	vec3 UpVectorWorld = vec3(0.0,1.0,0.0);
	vec3 Tangent = cross(UpVectorWorld, Normal);
	vec3 Binormal = cross(Normal, Tangent);

	float sampleDelta = 0.025;
	float numSamples = 0.0;
	for(float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
			// spherical to cartesian (in tangent space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            // tangent space to world
            vec3 sampleVec = tangentSample.x * Tangent + tangentSample.y * Binormal + tangentSample.z * Normal; // could be buggy

			irradiance += texture(Cubemap, sampleVec).rgb * cos(theta) * sin(theta);
			numSamples++;
		}
	}
	irradiance = PI * irradiance * (1.0 / float(numSamples));

	FragmentColor = vec4(irradiance, 1.0);
}



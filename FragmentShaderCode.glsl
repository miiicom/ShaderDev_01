#version 430

out vec4 FragmentColor;
in vec2 fragmentUV0;

uniform sampler2D frameBufferTexture;

const float offset = 1.0 / 300.0;

void main()
{	
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0f, offset),
		vec2(offset, offset),
		vec2(-offset, 0.0f),
		vec2(0.0f, 0.0f),
		vec2(offset, 0.0f),
		vec2(-offset, -offset),
		vec2(0.0f, -offset),
		vec2(offset, -offset)
	) ;

	float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

	vec3 sampleTex[9];

	for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(frameBufferTexture, fragmentUV0 + offsets[i]));
    }
	vec3 col = vec3(0.0);

	for(int i = 0; i < 9; i++){
		col += sampleTex[i] * kernel[i];
	}
	FragmentColor = vec4(texture(frameBufferTexture, fragmentUV0).xy,0.0,1.0);
	//FragmentColor = vec4(0.0,texture(frameBufferTexture, fragmentUV0).y,0.0,1.0);
	//FragmentColor = vec4(texture(frameBufferTexture, fragmentUV0).x,0.0,0.0,1.0);
	//FragmentColor = vec4(col, 1.0);
	//FragmentColor = vec4(vec3(1.0 - texture(frameBufferTexture, fragmentUV0)), 1.0);
}
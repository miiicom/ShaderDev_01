#version 430

out vec4 FragmentColor;
in vec2 fragmentUV0;

uniform sampler2D frameBufferTexture;

void main()
{	
	FragmentColor = vec4(vec3(1.0 - texture(frameBufferTexture, fragmentUV0)), 1.0);
}
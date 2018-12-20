#version 430
in vec3 fragColor;

out vec4 FragmentColor;
void main()
{	
	FragmentColor = vec4(fragColor,0.0);
}
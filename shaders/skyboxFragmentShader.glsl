#version 430

out vec4 FragmentColor;
in vec3 fragmentPositionWorld;

uniform samplerCube environmentMap;

void main()
{
    vec3 envColor = texture(environmentMap,fragmentPositionWorld).xyz;
    
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));  // gamma correction
  
    FragmentColor = vec4(envColor, 1.0);
}
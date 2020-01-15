#version 440

uniform float bIsModel;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBNMatrix;

out vec4 FragmentColour;

void main()
{
	FragmentColour = vec4(1, 0, 0, 1);
}
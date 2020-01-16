#version 440

uniform float bIsModel;

uniform vec3 LightPosition;
uniform vec3 CameraPosition;
uniform vec3 Colour;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBNMatrix;

out vec4 FragmentColour;

float Attenuation;
vec3 N;

void main()
{
	vec3 LightVector = normalize(LightPosition - Position);
	Attenuation = 1.f;

	N = normalize(Normal);

	//Diffuse Light
	vec3 PositionToLight = normalize(LightPosition - Position);
	vec3 DiffuseConstant = vec3(1.f, 0.f, 0.f);
	vec3 DiffuseColour = DiffuseConstant * (clamp(dot(PositionToLight, N), 0, 1));

	//Specular
	vec3 LightToPosition = normalize(Position - LightPosition);
	vec3 PositionToView = normalize(CameraPosition - Position);
	vec3 HalvedDirection = normalize(LightToPosition + PositionToView);
	vec3 SpecularColour = vec3(1,1,1) * pow(max(dot(N, HalvedDirection), 0), 30); //Blinn-Phong 

	//Final Colour
	FragmentColour = vec4(Colour, 1);// *vec4(SpecularColour, 1) * Attenuation;
}

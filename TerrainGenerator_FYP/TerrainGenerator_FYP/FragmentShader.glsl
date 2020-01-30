#version 440

struct Material
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	sampler2D DiffuseTexture;
	sampler2D NormalTexture;
	sampler2D MetallicTexture;
	sampler2D RoughnessTexture;
};

uniform float bIsModel;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;
uniform vec3 Colour;
uniform Material MeshMaterial;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBNMatrix;

out vec4 FragmentColour;

float Attenuation = 1.f;
vec3 N;
vec3 Grey = vec3(0.7, 0.7, 0.7);

vec3 CalculateAmbience();
vec3 CalculateDiffuse();
vec3 CalculateNormal();
vec3 CalculateSpecular();

void main()
{
	N = normalize(Normal);

	vec3 AmbientColour = CalculateAmbience();
	vec3 DiffuseColour = CalculateDiffuse();
	vec3 SpecularColour = CalculateSpecular();

	//Final Colour
	FragmentColour = vec4(vec4(AmbientColour, 1) + vec4(DiffuseColour, 1) + vec4(SpecularColour, 1)) * Attenuation;
}


vec3 CalculateAmbience()
{
	return MeshMaterial.Ambient;
}


vec3 CalculateDiffuse()
{
	//Diffuse Light
	vec3 PositionToLight = normalize(LightPosition - Position);
	float DiffuseColour = (clamp(dot(PositionToLight, N), 0, 1));

	return DiffuseColour * MeshMaterial.Diffuse * texture(MeshMaterial.DiffuseTexture, TexCoords).rgb;
}


vec3 CalculateNormal()
{
	vec3 Normal = normalize(TBNMatrix * (255.f / 128.f * texture2D(MeshMaterial.NormalTexture, TexCoords).xyz - 1));

	return Normal;
}


vec3 CalculateSpecular()
{
	//Specular
	vec3 LightToPosition = normalize(Position - LightPosition);
	vec3 PositionToView = normalize(CameraPosition - Position);
	vec3 HalvedDirection = normalize(LightToPosition + PositionToView);
	float SpecularColour = pow(max(dot(N, HalvedDirection), 0), 30);

	return MeshMaterial.Specular * SpecularColour * texture(MeshMaterial.MetallicTexture, TexCoords).rgb;
}
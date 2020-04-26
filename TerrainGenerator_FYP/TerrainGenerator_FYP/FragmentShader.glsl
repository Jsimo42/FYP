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
uniform vec3 LightRotation;
uniform vec3 CameraPosition;
uniform vec3 Colour;
uniform Material MeshMaterial;
uniform int LightingSetting;

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
	if (bIsModel == 2.f)
	{
		FragmentColour = vec4(0.5f, 0.5f, 0.5f, 1.f);
		return;
	}

	N = normalize(Normal);

	switch (LightingSetting)
	{
	case 1: //No Lighting
		FragmentColour = vec4(MeshMaterial.Diffuse * texture(MeshMaterial.DiffuseTexture, TexCoords).rgb, 1.f);
		return;
		break;
	case 2: //Spot Lighting
		Attenuation = 1.f;

		vec3 LightVector = normalize(LightPosition - Position);

		vec3 ConeDirection = normalize(LightRotation);

		vec3 RayDirection = -LightVector;

		float LightToSurfaceAngle = degrees(acos(dot(RayDirection, ConeDirection)));

		if (LightToSurfaceAngle > 45.f)
		{
			Attenuation = 0.f;
		}

		break;
	case 3: //Point Lighting
		Attenuation = smoothstep(20.f, 5.f / 2, distance(LightPosition, Position));
		break;
	case 4: //Global Lighting
		Attenuation = 1.f;
		break;
	}

	vec3 AmbientColour = CalculateAmbience();
	vec3 DiffuseColour = CalculateDiffuse();
	vec3 SpecularColour = CalculateSpecular();

	//Final Colour
	vec3 FinalColour = AmbientColour + DiffuseColour + SpecularColour;
	FragmentColour = vec4(FinalColour * Attenuation, 1);
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

	return MeshMaterial.Diffuse * texture(MeshMaterial.DiffuseTexture, TexCoords).rgb;
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

	return MeshMaterial.Specular * texture(MeshMaterial.MetallicTexture, TexCoords).rgb;
}
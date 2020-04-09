#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <glew.h>
#include <glfw3.h>

#include <opencv2/core/core_c.h>
#include <opencv2/imgcodecs.hpp>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Vertex.h"
#include "JSMath.h"

enum EDirection
{
	EForward = 0,
	EBack,
	ELeft,
	ERight,
	EUp,
	EDown
};

enum EEntityType
{
	EModel = 0,
	ECube,
	EPyramid,
	ENone
};

enum EColour
{
	EWhite = 0,
	EYellow,
	EOrange,
	ERed,
	EPink,
	EPurple,
	EDarkBlue,
	EBlue,
	ELightBlue,
	ELightGreen,
	EGreen,
	EBlack
};

const std::vector<std::string> ColourNames{ "White", "Yellow", "Orange", "Red", "Pink", "Purple", "DarkBlue", "Blue", "LightBlue", "LightGreen", "Green", "Black" };

struct Agent
{
	Agent(EColour LayerColourIn, cv::Vec3b ColourIn, bool bIsMeshIn, EEntityType MeshTypeIn, std::string FileNameIn = "") : LayerColour(LayerColourIn), Colour(ColourIn), bIsMesh(bIsMeshIn), MeshType(MeshTypeIn), FileName(FileNameIn) {};

	EColour LayerColour;
	cv::Vec3b Colour;

	bool bIsMesh = true;
	EEntityType MeshType = EEntityType::ENone;

	std::string FileName = "";
};
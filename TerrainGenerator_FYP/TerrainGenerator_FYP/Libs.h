#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <SOIL2.h>

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
	ERight
};

enum EEntityType
{
	EModel = 0,
	ECube,
	EPyramid,
	ENone
};
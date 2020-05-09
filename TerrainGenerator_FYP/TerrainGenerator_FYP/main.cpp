#include "pch.h"
#include <iostream>

#include "WorldEngine.h"

//Check for memory leaks
#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

int main()
{
	WorldEngine Engine = WorldEngine();

	Engine.Initialise();
	Engine.Run();
}

/*
TODO List
-Use Photo to Generate Level
	-Read Photo
	-Edit Size of Photo
	-Find Edges of Paper in Photo
	-Detect Colours


-Add Lights through UI
-Scale or Rotate Models in Real Time
-Advanced Lighting eg Shadows
*/
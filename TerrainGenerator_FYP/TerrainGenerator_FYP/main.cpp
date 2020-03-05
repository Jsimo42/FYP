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
	WorldEngine* Engine = new WorldEngine;

	Engine->Initialise();
	Engine->Run();
}
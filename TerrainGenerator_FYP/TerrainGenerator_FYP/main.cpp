#include "pch.h"
#include <iostream>

#include "WorldEngine.h"

int main()
{
	WorldEngine* Engine = new WorldEngine;

	Engine->Initialise();
	Engine->Run();
}
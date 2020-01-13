#include "pch.h"
#include <iostream>

#include "WorldEngine.h"

int main()
{
	WorldEngine* Engine = new WorldEngine;

	Engine->CreateLevel("FilePath", 1);

	Engine->Render();
}
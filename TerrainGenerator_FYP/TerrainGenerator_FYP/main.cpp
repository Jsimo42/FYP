#include "pch.h"
#include <iostream>

#include "WorldEngine.h"

int main()
{
    std::cout << "Hello World!\n";

	WorldEngine* Engine = new WorldEngine;

	Engine->CreateLevel("FilePath", 1);

	Engine->Render();
}
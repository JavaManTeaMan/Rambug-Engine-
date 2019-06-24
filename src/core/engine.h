#pragma once 

// System includes (Windows build)
// todo: put this in a platform dependent header
#include <Windows.h>
#include <stdint.h>	
#include <stdlib.h>
#include <chrono>
#include <thread>	
#include <iostream>
#include <intrin.h>

// Other necessary system defines
#define _CRT_SECURE_NO_WARNINGS

#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//todo: make a platform dependent header of this stuff
// Typedefs to avoid using _t
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

namespace Rambug
{
	namespace Core
	{
		namespace Engine {

			// Returns a boolean: whether or not initialization was successful
			void Initialize()
			{
				// Initialize the Engine 
				AllocConsole();
				freopen("CONOUT$", "w", stdout);
				printf("Initializing the Rambug Engine...");
			}
		}
	}
}
#pragma once

#include "engine.h"

/* 
Struct that runs on one and only one thread
All other instances of the clock class will retrieve their time functions from this struct by inheriting this struct
This is done so that only one thread is required for all clock instances
As opposed to one thread per clock instance.
*/

namespace Rambug
{
	namespace Core
	{
		namespace Masterclock
		{
			std::thread m_thread;

			
		}
	}
}
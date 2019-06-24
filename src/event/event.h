#pragma once

#include "../engine.h"
#include "eventtypeenum.h"
#include "resizeevent.h"

namespace Rambug
{
	namespace Core
	{
		typedef union
		{
			// type of event
			uint8 type;

			// todo: add more events here
			ResizeEvent displayEvent;

		} Event;
	}
}
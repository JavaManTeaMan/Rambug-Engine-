#pragma once

#include "../engine.h"
#include "eventtypeenum.h"

namespace Rambug
{
	namespace Core
	{
		typedef struct
		{
			uint8 type = R_EVENT_DISPLAY_RESIZE;

			// Store the old width and height 
			int32 oldWidth;
			int32 oldHeight;

			// Store the new width and height
			int32 newWidth;
			int32 newHeight;

		} ResizeEvent;

	}
}
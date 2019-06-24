#pragma once

#include "../core/engine.h"

#include "bitmap.h"
#include "display.h"

// Defines whether or not to use BitBlt or StretchDIBits
#define RAMBUG_DISPLAY_USE_BITBLT 1 
#define RAMBUG_DISPLAY_USE_STRETCHDIBITS 0 

#ifdef RAMBUG_DISPLAY_USE_BITBLT
#define RAMBUG_DISPLAY_USE_STRETCHDIBITS 0
#endif

#ifdef RAMBUG_DISPLAY_USE_STRETCHDIBITS
#define RAMBUG_DISPLAY_USE_BITBLT 0 
#endif

namespace Rambug
{
	namespace Graphics
	{
		class Screenbuffer : protected Bitmap
		{
		public:
			// Public variables
			
		private:
			// Private variables
			Display* m_display;
		
		public:
			// Public functions
			Screenbuffer();
			Screenbuffer(Display* display);

			~Screenbuffer();

			// Functions to use in display
			void update();
			void render();

			void setDisplay(Display* display);

		private:
			// Private functions

		};
	}
}
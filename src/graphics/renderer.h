#pragma once

#include "../core/engine.h"
#include "display.h"

namespace Rambug
{
	namespace Graphics
	{
		struct Renderer
		{
		public:
			// Public variables
			
		private:
			// Private variables
			HDC m_hdc;
			HWND m_hwnd;
			Display m_display;

		public:
			// Public functions
			Renderer(Display display);
			Renderer(HDC hdc);
			Renderer(HWND hwnd);
			Renderer();

			~Renderer();
			
			void render();
			void addNewBitmap();

			void setHdc(HDC hdc) { m_hdc = hdc; }
			HDC getHdc() { return m_hdc; }

		private:
			// Private functions

		};
	}
}

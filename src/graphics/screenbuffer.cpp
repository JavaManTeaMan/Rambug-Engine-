#include "screenbuffer.h"

namespace Rambug
{
	namespace Graphics
	{
		Screenbuffer::Screenbuffer()
		{

		}

		Screenbuffer::Screenbuffer(Display* display)
			: Bitmap(display->getWidth(), display->getHeight())
		{
			m_display = display;
		}

		Screenbuffer::~Screenbuffer()
		{

		}

		void Screenbuffer::update()
		{
			
		}

		void Screenbuffer::render()
		{

#ifdef RAMBUG_DISPLAY_USE_BITBLT
			// Bitblt
			BitBlt
			(
				m_display->getDc(),
				0,
				0,
				m_display->getWidth(),
				m_display->getHeight(),
				m_Dc,
				0,
				0,
				SRCCOPY
			);
#endif
			
#ifdef RAMBUG_DISPLAY_USE_STRETCHDIBITS
			// StretchDIBits
			StretchDIBits
			(
				m_display->getDc(),
				0,
				0,
				m_display->getWidth(),
				m_display->getHeight(),
				0,
				0,
				m_width,
				m_height,
				m_memory,
				&m_info,
				DIB_RGB_COLORS,
				SRCCOPY
			);
#endif
		
		}

		void Screenbuffer::setDisplay(Display* display)
		{
			m_display = display;
		}

	}
}
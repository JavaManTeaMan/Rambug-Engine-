#include "Renderer.h"

namespace Rambug
{
	namespace Graphics
	{
		Renderer::Renderer(Display display)
		{
			m_display = display;
			m_hwnd = display.getHwnd();
			m_hdc = display.getDc();
		}
		
		Renderer::Renderer(HDC hdc)
		{
			m_hdc = hdc;
		}

		Renderer::Renderer(HWND hwnd)
		{
			m_hwnd = hwnd;
		}

		Renderer::Renderer()
		{

		}

		Renderer::~Renderer()
		{

		}



	}
}
#include "display.h"

namespace Rambug
{
	namespace Graphics
	{
		Display::Display()
		{
				
		}
		
		Display::Display(int width, int height, int x, int y, const char* title, const char* displayClassName, int flags, LPCTSTR lpIconName, LPCTSTR lpCursorName, bool defaultIcon, bool defaultCursor) : AbstractDisplay()
		{
			m_displayClassName = displayClassName;
			m_title = title;
			
			m_x = x;
			m_y = y;

			m_width = width;
			m_height = height;

			m_hInstance = ::GetModuleHandle(NULL);

			m_flags = flags;
		}


		Display::~Display()
		{

		}

		void Display::lock()
		{
			// Set AbstractDisplay's CreateWindowEx parameters
			dwExStyle = 0;
			lpClassName = m_displayClassName;
			lpWindowName = m_title;
			dwStyle = m_flags; 
			x = m_x;
			y = m_y;
			nWidth = m_width;
			nHeight = m_height;
			hWndParent = 0;
			hMenu = 0;
			hInstance = m_hInstance;
		}

		void Display::show()
		{
			::ShowWindow(hwnd, SW_SHOW);
		}

		void Display::enable()
		{
			::EnableWindow(hwnd, true);
		}

		void Display::update()
		{
			::UpdateWindow(hwnd);
		}

		bool Display::enableFlag(int flag)
		{
			DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
			// todo: check if the flag is legit
			DWORD dwRemove = flag;
			DWORD dwNewStyle = dwStyle & dwRemove;
			::SetWindowLong(hwnd, GWL_STYLE, dwNewStyle);

			return true;
		}

		bool Display::disableFlag(int flag)
		{
			DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
			// todo: check if the flag is legit
			DWORD dwRemove = flag;
			DWORD dwNewStyle = dwStyle & ~dwRemove;
			::SetWindowLong(hwnd, GWL_STYLE, dwNewStyle);

			return true;
		}

		bool Display::isFlagActive(int flag)
		{
			DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
			if (dwStyle & flag)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void Display::addEventFunction(void(*functionPointer) (const char* eventName, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam))
		{
			eventFunction = functionPointer;
		}

		void Display::removeEventFunction()
		{
			// Set the eventFunction to default
			eventFunction = m_defaultEventFunctionPointer;
		}

		// Window procedure
		LRESULT CALLBACK Display::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{

			case WM_CREATE:
			{
				this->onCreate(hwnd, message, wParam, lParam);
				break;
			}

			case WM_SIZE:
			{
				this->onSize(hwnd, message, wParam, lParam);
				return 0; 
				break;
			}

			case WM_ERASEBKGND:
			{
				this->onEraseBackground(hwnd, message, wParam, lParam);
				return 1;
				break;
			}

			case WM_PAINT:
			{
				this->onPaint(hwnd, message, wParam, lParam);
				break;
			}

			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}

			case WM_QUIT:
			{
				this->onQuit(hwnd, message, wParam, lParam);
				break;
			}

			case WM_DESTROY:
			{
				this->onDestroy(hwnd, message, wParam, lParam);
				break;
			}

			case WM_TIMER:
			{

				break;
			}

			// todo: implement wm_size, UseGetClientRect to calculate resolution (x2 - x1) etc. update resolution. scale = old resolution / new resolution or new / old (dont know) probably new/old

			default:
			{
				return this->onDefault(hwnd, message, wParam, lParam);
			}

			}
		}

		// Display Message OnEvent calls
		void Display::onCreate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			m_hdc = ::GetDC(hwnd);

			// Init ScreenBuffers
			m_bitmap = Bitmap(m_width, m_height);
		}

		void Display::onSize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (wParam == SIZE_RESTORED)
			{
				RECT displayDimension = { 0, 0, m_width, m_height };
				GetClientRect(hwnd, &displayDimension);
				m_width = displayDimension.right;
				m_height = displayDimension.bottom;
			}
		}

		void Display::onEraseBackground(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			
		}

		void Display::onPaint(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
		
		}

		void Display::onQuit(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			PostQuitMessage(0);
		}

		void Display::onDestroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			::ReleaseDC(hwnd, m_hdc);
			PostQuitMessage(0);
		}

		LRESULT Display::onDefault(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::DefWindowProc(hwnd, message, wParam, lParam);
		}

		void Display::m_defaultEventFunction(const char* eventName)
		{

		}

	}
}
#include "abstractdisplay.h"

namespace Rambug
{
	namespace Graphics
	{
		AbstractDisplay::AbstractDisplay()
		{

		}

		AbstractDisplay::~AbstractDisplay()
		{

		}

		bool AbstractDisplay::CreateDisplay()
		{
			OutputDebugString("Creating Display... \n");
			std::cout << "Creating Display.. \n";

			hwnd = ::CreateWindowEx
			(
				dwExStyle,
				lpClassName,
				lpWindowName,
				dwStyle,
				x,
				y,
				nWidth,
				nHeight,
				hWndParent,
				hMenu,
				hInstance,
				this
			);

			//OutputDebugString("Display Error Detected:");
			//OutputDebugString(GetLastErrorAsString().c_str());
			//OutputDebugString("\n");

			// Returns true if hwnd is not null (has been created)
			// Returns false if hwnd is null (has not been created: ERROR)
			if (!hwnd) { return false; }
			else { return true; }
		}

		LRESULT CALLBACK AbstractDisplay::MessageRouter(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			// Pointer to the display that receives the message
			AbstractDisplay *display = 0;
			
			// Check for the message that is sent when a new window has been created
			if (message == WM_NCCREATE)
			{
				// Associate its handle with the AbstractDisplay instance pointer
				::SetWindowLong(hwnd, GWL_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));
				//OutputDebugString("WM_NCCREATE! \n");
			}

			// Retrieve instance of AbstractDisplay that matches with the destination window's HWND
			display = (AbstractDisplay*) (::GetWindowLong(hwnd, GWL_USERDATA));

			// Route message to the WindowProcedure method that is in the derived AbstractDislay class
			if (display)
			{
				display->WindowProcedure(hwnd, message, wParam, lParam);
			}
			else
			{
				// Messages that arrive before WM_NCCREATE
				// HWND AbstractDisplay* association not made
				return ::DefWindowProc(hwnd, message, wParam, lParam);
			}
		}
	}
}
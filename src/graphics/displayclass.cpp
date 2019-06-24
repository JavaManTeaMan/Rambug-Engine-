#include "displayclass.h"
#include "abstractdisplay.h"
#include <string>
#include <cstring>

namespace Rambug
{
	namespace Graphics
	{
		DisplayClass::DisplayClass(HINSTANCE hInst, const TCHAR* className) 
		{
			ZeroMemory(this, sizeof(WNDCLASSEX));
			hInstance = hInst;
			
			// All messages for windows that belong to this Window Class will be sent to Message Router
			lpfnWndProc = AbstractDisplay::MessageRouter;
			lpszClassName = className;

			// Set values for the rest of the WNDCLASSEX structure

			lpszMenuName = 0;
			cbSize = sizeof(WNDCLASSEX);
			cbClsExtra = 0;
			cbWndExtra = 0;
			hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
			hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);
			hCursor = ::LoadCursor(NULL, IDC_ARROW);
			style = CS_HREDRAW | CS_VREDRAW;
			hbrBackground = /*(HBRUSH)GetStockObject(WHITE_BRUSH) */ 0;
		}
		
		DisplayClass::DisplayClass()
		{

		}

		DisplayClass::~DisplayClass()
		{

		}

		bool DisplayClass::Register()
		{	
			if (::RegisterClassEx(this) != 0)
			{
				return true;
			}
			else
			{
				// todo: failed; debug
				//OutputDebugString("ERROR CODE BE LIKE:");
				//OutputDebugString(GetLastErrorAsString().c_str());
				//OutputDebugString("\n");
				return false;
			}
		}
		
	

	}
}
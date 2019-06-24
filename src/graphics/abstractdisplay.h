#pragma once

#include <Windows.h>
#include <string>

#include "../utils/debug.h"

#include "../core/engine.h"

namespace Rambug
{
	namespace Graphics
	{
		class AbstractDisplay
		{
		public:
			// Public variables

		private:
			// Private variables

		protected:
			// Protected variables
			// Window handle
			HWND hwnd;
			
			// CreateWindowEx parameters:
			DWORD dwExStyle = 0;	
			LPCTSTR lpClassName = 0;
			LPCTSTR lpWindowName = 0;
			DWORD dwStyle = 0;
			int x = 0;
			int y = 0;
			int nWidth = 0;
			int nHeight = 0;
			HWND hWndParent = 0;
			HMENU hMenu = 0;
			HINSTANCE hInstance = 0;
			LPVOID lpParam = 0;

		public:
			// Public functions
			AbstractDisplay();
			~AbstractDisplay();

			// WNDCLASSEX::lpfnWndProc
			static LRESULT CALLBACK MessageRouter(HWND, UINT, WPARAM, LPARAM);
			
			// Actual window procedure
			// Will be in derived classes and be called my MessageRouter
			virtual LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM) = 0;

			//	Will Call CreateWindowEx
			virtual bool CreateDisplay();

			// Getters
			HWND getHwnd()
			{
				return hwnd;
			}

			// Setters

		private:
			// Private functions

		protected:
			// Protected functions

		};
	}
}
#pragma once

#include <Windows.h>

#include <stdlib.h>

// #include <vector>

#include "../core/engine.h"
#include "../core/clock.h"

#include "displayclass.h"
#include "abstractdisplay.h"

#include "renderer.h"
//#include "screenbuffer.h"
#include "bitmap.h"

#include "../utils/debug.h"

#include "win32windowmap.h"

namespace Rambug
{
	namespace Graphics
	{
		class Display : public AbstractDisplay
		{
			// Friend classes:
			// friend class Clock;
	
		public:
			// Public variables
			
		private:
			// Private variables

			// Variables to pass into AbstractDisplay
			DisplayClass m_displayClass;
			int m_width, m_height, m_x, m_y;
			const char* m_title;
			const char* m_displayClassName;
			HINSTANCE m_hInstance;

			Bitmap m_bitmap;
			
			// Handle to the Device Context for rendering
			HDC m_hdc;

			// Flags for the custom window styles (WS_)
			int m_flags = 0;

			//todo: delete this below
			int m_xOffSet = 0;
			int m_yOffSet = 0;

			// Other
			LPCTSTR m_lpIconName;
			LPCTSTR m_lpCursorName;

			bool m_defaultIcon;
			bool m_defaultCursor;

			// Delete this:
			//Screenbuffer* m_screenbuffer;

		protected:
			// Protected variables

		public:
			// Public functions
			Display(int width, int height, int x, int y, const char* title, const char* displayClassName, int flags, LPCTSTR lpIconName, LPCTSTR lpCursorName, bool defaultIcon, bool defaultCursor);
			Display();
			~Display();

			virtual LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
			void lock();
			void show(); // Counter to WS_VISIBLE
			void enable(); // Counter to WS_DISABLED
			void update();

			// Getters 
			int getWidth() { return m_width; }
			int getHeight() { return m_height; }
			int getX() { return m_x; }
			int getY() { return m_y; }
			const char* getTitle() { return m_title; }
			const char* getWindowClassName() { return m_displayClassName; }

			// Functions to operate with the WS_ styles and flags
			bool isFlagActive(int flag);
			int getFlag() { return m_flags; }

			bool enableFlag(int flag);
			bool disableFlag(int flag);

			// Function (pointer) to add a event catcher function
			void (*eventFunction) (const char* eventName, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

			// Function to add a event catcher function
			void addEventFunction(void (*functionPointer) (const char* eventName, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam));

			void removeEventFunction();

			// Getters
			LPCTSTR getLpIconName() { return m_lpIconName; }
			LPCTSTR getLpCursorName() { return m_lpCursorName; }

			bool getDefaultIcon() { return m_defaultIcon; }
			bool getDefaultCursor() { return m_defaultCursor; }

			HDC getDc() { return m_hdc; }

		private:
			// Private functions
			// Display Message OnEvent calls
			void onCreate(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			void onSize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			void onEraseBackground(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			void onPaint(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			void onQuit(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			void onDestroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			LRESULT onDefault(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
			
			void m_defaultEventFunction(const char* eventName);
			void (*m_defaultEventFunctionPointer) (const char* eventName, HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

		protected:
			// Protected functions
		};
	}
}
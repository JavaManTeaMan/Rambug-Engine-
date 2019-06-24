#pragma once

#include <Windows.h>
#include "abstractdisplay.h"

namespace Rambug
{
	namespace Graphics
	{
		class DisplayClass : protected WNDCLASSEX
		{
			public:
				// Public variables 
			
			private:
				// Private variables

			protected:
				// Protected variables

			public:
				// Public functions
				DisplayClass(HINSTANCE hInst, const TCHAR* className);
				DisplayClass();
				~DisplayClass();

				// Registers the class

				// Get the class name
				virtual const TCHAR* getClassName() const { return lpszClassName; }
				virtual bool Register();

			private:
				// Private functions

			protected:
				// Protected functions

			};
		}
	}

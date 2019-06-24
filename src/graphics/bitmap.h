#pragma once

#include "../core/engine.h"

// Defines whether or not to use BitBlt or StretchDIBits
#define RAMBUG_DISPLAY_USE_BITBLT 

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
		class Bitmap 
		{
		public:
			// Public variables

		private:
			// Private variables

		protected:
			// Protected variables
			// Private variables
			uint32 m_width;
			uint32 m_height;

			// Variables to fill in the structures
			uint32 m_bitCount = 32;

			// Variables to help with memory
			uint32 m_bytesPerPixel;
			uint32 m_memorySize;

			// Actual memory to the bitmap bits
			void* m_memory;

			// Pitch is the number of bytes needed per row for pixel information 
			uint32 m_pitch;

			// Structures to hold bitmap information
			BITMAPINFOHEADER m_infoHeader = { 0 };
			BITMAPINFO m_info = { 0 };

			// Compatible device context with the display that is used in CreateDIBSection 
			HDC m_Dc;

			// Handle to the bitmap, returned by CreateDIBSection()
			HBITMAP m_handle;

		public:
			// Public functions
			Bitmap();
			Bitmap(const uint32& bitmapWidth, const uint32& bitmapHeight);

			~Bitmap();

			// Calls CreateDIBSection with modified BITMAPINFOHEADER width and height attributes
			HBITMAP resize(const uint32& newWidth, const uint32& newHeight); 

			// Calls either BitBlt or StretchDIBits
			void render(HDC hdc);

			// Render functions
			void setPixel(const int64& x, const int64& y, const uint8& red, const uint8& blue, const uint8& green);

			void drawCircle(const int32& originX, const int32& originY ,const int32& radius, const uint8& red, const uint8& blue, const uint8& green);
			void drawEllipse(const int32& originX, const int32& originY, const int32& width, const int32& height, const uint8& red, const uint8& blue, const uint8& green);

			void drawLine();

			void drawSquare();

			// Getters
			uint32 getWidth() { return m_width; }
			uint32 getHeight() { return m_height; }
			
			void* getMemory() { return m_memory; }

			uint32 getPitch() { return m_pitch; }

			BITMAPINFOHEADER getInfoHeader() { return m_infoHeader; }
			BITMAPINFO getInfo() { return m_info; }

			HDC getDc() { return m_Dc; }

			HBITMAP getHandle() { return m_handle; }

		private:
			// Private functions

		protected:
			// Protected functions

			// Function to fillout BITMAPINFOHEADER information
			BITMAPINFOHEADER m_fillInfoHeader();

			// Function to fillout BITMAPINFO information
			BITMAPINFO m_fillInfo();

			// Function to calculate pitch
			uint32 m_calculatePitch();

			// Function to call CreateDIBSection and GdiFlush
			HBITMAP m_create();

		};
	}
}



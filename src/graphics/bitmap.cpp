#include "bitmap.h"

namespace Rambug
{
	namespace Graphics
	{

		Bitmap::Bitmap()
		{

		}

		Bitmap::Bitmap(const uint32& bitmapWidth, const uint32& bitmapHeight)
		{
			// Set our own variables so we can call getters and setters:
			m_width = bitmapWidth;
			m_height = bitmapHeight;
			
			this->m_fillInfoHeader();
			this->m_fillInfo();

			// Set variable(s) of BITMAPINFO Structure -> this bitmap class already inherits it:
			// m_info.bmiHeader = m_infoHeader;

			// Set up variables for memory allocation
			m_bytesPerPixel = m_infoHeader.biBitCount / 8; // Take total amount of bits that are needed, an divide by 8 bits to get number of bytes
			m_memorySize = (m_width * m_height) * m_bytesPerPixel;

			// Allocate memory
			m_memory = VirtualAlloc(0, m_memorySize, MEM_COMMIT, PAGE_READWRITE); // Ask for block of memory anywhere, of size m_memorySize, that windows will track, and we can read and write to 

			// No device context created yet: make a new, default one that is to the current display
			m_Dc = CreateCompatibleDC(0);

			// Set a default BitmapHandle
			m_handle = CreateDIBSection
			(
					m_Dc,
					&m_info,
					DIB_RGB_COLORS,
					&m_memory,
					0,
					0
			);

			// Synchronize access to the bitmap before drawing to it
			GdiFlush();
		}

		Bitmap::~Bitmap()	
		{
		
		}

		HBITMAP Bitmap::m_create()
		{
			HBITMAP hbitmap = CreateDIBSection
			(
					m_Dc,
					&m_info,
					DIB_RGB_COLORS,
					&m_memory,
					0,
					0
			);

			// Synchronize access to the bitmap before drawing to it
			GdiFlush();

			m_handle = hbitmap;

			return hbitmap;
		}

		BITMAPINFOHEADER Bitmap::m_fillInfoHeader()
		{
			BITMAPINFOHEADER infoHeader = { 0 };

			// Set variables of BITMAPINFOHEADER Structure:
			infoHeader.biSize = sizeof(BITMAPINFOHEADER); // Size of this structure
			infoHeader.biWidth = (LONG)m_width;
			infoHeader.biHeight = -(LONG)m_height; // Make negative because we want a top down bitmap
			infoHeader.biPlanes = 1; // Must be 1
			// todo: maybe let the dev be able to change this; however, 32 will provide 8 padding bits that will make it nice for DWORD allignment (DWORDS have 4 8 byte!)
			infoHeader.biBitCount = m_bitCount /*(32 by default) */; 
			infoHeader.biCompression = BI_RGB; // Not compressed, therefore use B_RGB
			infoHeader.biSizeImage = 0; // 0 because no compression is used
			infoHeader.biXPelsPerMeter = 0;
			infoHeader.biYPelsPerMeter = 0;
			infoHeader.biClrUsed = 0; // Use all colors specified in biBitCount
			infoHeader.biClrImportant = 0; // All colors are required that are specified in biBitCount

			m_infoHeader = infoHeader;

			return infoHeader;
		}

		BITMAPINFO Bitmap::m_fillInfo()
		{
			BITMAPINFO info = { 0 };
			
			// Set variable(s) of BITMAPINFO Structure 
			info.bmiHeader = m_infoHeader;
			
			m_info = info;

			return info;
		}

		uint32 Bitmap::m_calculatePitch()
		{
			uint32 pitch = m_width * m_bytesPerPixel;
			m_pitch = pitch;
			return pitch;
		}

		HBITMAP Bitmap::resize(const uint32& newWidth, const uint32& newHeight)
		{
			// Deallocate the memory
			
			// Set new height and width attributes
			m_width = newWidth;
			m_height = newHeight;

			// Fill structures with new width and height information
			this->m_fillInfoHeader();
			this->m_fillInfo();
			
			// Calculate new pitch value
			m_calculatePitch();

			// Create new bitmap
			return this->m_create();
		}

		void Bitmap::render(HDC hdc)
		{
#ifdef RAMBUG_DISPLAY_USE_BITBLT
				// Bitblt
				BitBlt
				(
					hdc,
					0,
					0,
					m_height,
					m_width,
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
					hdc,
					0,
					0,
					m_width,
					m_height,
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

		void Bitmap::setPixel(const int64& x, const int64& y, const uint8& red, const uint8& blue, const uint8& green)
		{
			int pitch = m_width * m_bytesPerPixel;

			uint8* row = (uint8*) m_memory + (y * pitch);
			uint8* pixel = (uint8*) row;
			pixel += x * 4;

			*pixel = red;
			++pixel;

			*pixel = green;
			++pixel;

			*pixel = blue;
			++pixel;

			// Padding
			*pixel = 0;
			++pixel;

		}

		void Bitmap::drawCircle(const int32& originX, const int32& originY, const int32& radius, const uint8& red, const uint8& blue, const uint8& green)
		{
			for (int y = -radius; y <= radius; y++)
			{
				for (int x = -radius; x <= radius; x++)
				{
					if (x * x + y * y <= radius * radius)
					{
						setPixel(originX + x, originY + y, red, green, blue);
					}
				}
			}
		}

		void Bitmap::drawEllipse(const int32& originX, const int32& originY, const int32& width, const int32& height, const uint8& red, const uint8& blue, const uint8& green)
		{
			int hh = height * height;
			int ww = width * width;
			int hhww = hh * ww;
			int x0 = width;
			int dx = 0;

			for (int x = -width; x <= width; x++)
			{
				setPixel(originX + x, originY, red, green, blue);
			}

			for (int y = 1; y <= height; y++)
			{
				int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
				for (; x1 > 0; x1--)
					if (x1*x1*hh + y*y*ww <= hhww)
						break;
				dx = x0 - x1;  // current approximation of the slope
				x0 = x1;

				for (int x = -x0; x <= x0; x++)
				{
					setPixel(originX + x, originY - y, red, green, blue);
					setPixel(originX + x, originY + y, red, green, blue);
				}
			}

		}
	}
}
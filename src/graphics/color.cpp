#include "color.h"

namespace Rambug
{
	namespace Graphics
	{

		Color::Color(unsigned char red, unsigned char blue, unsigned char green)
		{
			m_red = red;
			m_blue = blue;
			m_green = green;
		}

		Color::Color(unsigned char alpha, unsigned char red, unsigned char blue, unsigned char green)
		{
			m_alpha = alpha;
			m_red = red;
			m_blue = blue;
			m_green = green;
		}


		Color::Color(Math::vec4 color)
		{
			m_alpha = (unsigned char) color.x;
			m_red = (unsigned char) color.y;
			m_blue = (unsigned char) color.z;
			m_green = (unsigned char) color.w;
		}

		Color::Color(Math::vec3 color)
		{
			m_red = (unsigned char) color.x;
			m_green = (unsigned char) color.y;
			m_blue = (unsigned char) color.z;
		}

	}
}
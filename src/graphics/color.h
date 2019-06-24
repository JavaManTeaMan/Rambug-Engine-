#pragma once

#include "../core/engine.h"

#include "../Maths/vec4.h"
#include "../Maths/vec3.h"

namespace Rambug
{
	namespace Graphics
	{
		class Color
		{
		public:
			// Public variables

		private:
			// Private variables
			uint8 m_red;
			uint8 m_green;
			uint8 m_blue;
			uint8 m_alpha;

		public:
			// Public functions
			Color(uint8 red, uint8 green, uint8 blue);
			Color(uint8 alpha, uint8 red, uint8 green, uint8 blue);

			Color(Math::vec4 color);
			Color(Math::vec3 color);
		

		private:
			// Private functions

		};
	}
}
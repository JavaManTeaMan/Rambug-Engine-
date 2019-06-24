/*
DO NOT DELETE THIS COMMENT:
The ROM(Rambug Optical Mathematics) Library:
This software is written by Danyil Blyschak, 8/2015 (1st Build).
For any permissions, questions, or bug fixes, email the
support email that came with your distribution of this software.
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Rambug
{
	namespace Math
	{
		static float ToRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}

		static float ToDegrees(float radians)
		{
			return radians * (180 / M_PI);
		}
	}
}
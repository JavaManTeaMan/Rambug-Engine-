/*
The MIT License(MIT)

Copyright(c) 2016 Danyil Blyschak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CXXTEST_H
#define CXXTEST_H

#include <Windows.h> /* Using MSDN's implementation of rdtsc (x86 Assembler Instruction) and to use GetTickCount */
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef struct cxxtst
{
	uint64 beginningCpuTicks;
	uint64 endCpuTicks;
	uint64 resultCpuTicks;

	DWORD beginningTickCount;
	DWORD endTickCount;
	DWORD resultTickCount;

	uint64 analyze_cpu_ticks( void (*functionTo) ())
	{
		beginningCpuTicks = __rdtsc();
		functionTo();
		endCpuTicks = __rdtsc();
		/* Store the values first, and then do calculations to be as accurate as possible */
		resultCpuTicks = endCpuTicks - beginningCpuTicks;
		return resultCpuTicks;
	}

	DWORD analyze_tick_count( void (*functionTo) ())
	{
		beginningTickCount = GetTickCount();
		functionTo();
		endTickCount = GetTickCount();
		/* Store the values first, and then do calculations to be as accurate as possible */
		resultTickCount = endTickCount - beginningTickCount;
		return resultTickCount;
	}

	void reset()
	{
		beginningCpuTicks = 0;
		endCpuTicks = 0;
		resultCpuTicks = 0;

		beginningTickCount = 0;
		endTickCount = 0;
		resultTickCount = 0;
	}

} cxxtst;

#endif
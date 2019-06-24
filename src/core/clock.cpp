#include "clock.h"

namespace Rambug
{
	namespace Core
	{
		
		Clock::Clock(uint32 timeout, void(*function)())
		{
			m_timeout = timeout;
			m_function = function;

			m_thread = std::thread(&Clock::start, this);
			m_thread.detach();
		}

		void Clock::start()
		{
			/*
			// OutputDebugString("CALLING CLOCK.START \n");
			m_ticking = true;
			m_lastTickCount = GetTickCount();
			// m_lastTickCount = time(NULL);

			while(m_ticking)
			{
				// New time - old time = difference between them (timeout)
				if (((GetTickCount() - m_lastTickCount) == m_timeout))
				//if(time(NULL) - m_lastTickCount == m_timeout)
				{
					// Call Tick
					//OutputDebugString("JACKPOT! WE HIT THE TICK CALL \n");
					m_tick();
					return; // Return out of the function, only to be called at the end of tick()
				}
				else
				{
					// Not yet to call tick()
				}
			}
			*/

			m_ticking = true;

			//std::this_thread::sleep_for(std::chrono::milliseconds(m_timeout));

			/*
			LARGE_INTEGER startingTime = { 0 };
			LARGE_INTEGER endingTime = { 0 };

			LARGE_INTEGER frequency = { 0 };

			QueryPerformanceFrequency(&frequency);

			QueryPerformanceCounter(&startingTime);

			LARGE_INTEGER nowTime = { 0 };
			*/

			/*
			while (m_ticking)
			{
				QueryPerformanceCounter(&nowTime);
				if (((nowTime.QuadPart - startingTime.QuadPart * 1000000) / frequency.QuadPart) / 1000000 == m_timeout)
				{
					// Happened
					this->m_tick();
					return;
				}
				else
				{
					
				}
			}
			*/

				

			/*

			while (m_ticking)
			{
			}
			*/
			/*while (m_ticking)
			{
				std::chrono::system_clock::time_point start = std::chrono::system_clock::now();


				std::chrono::duration<double> time_taken = std::chrono::system_clock::now() - start;
			}	
			*/

		}

		void Clock::stop()
		{
			m_ticking = false;
		}

		void Clock::m_tick()
		{
			// Call the function pointer that was given
			OutputDebugString("Calling m_tick()");
			(*m_function)();
			if (m_ticking)
			{
				this->start();
			}
		}
	}
}
#pragma once

#include "engine.h"

namespace Rambug
{
	//todo: figure out where clock goes
	namespace Core
	{
		//todo: make a 64bit version that extends more than just 47.5 days (check msdn)
		class Clock
		{
		public:
			// Public variables

		private:
			// Private variables
			// Amount of time to wait for
			uint32 m_timeout;

			// Function to call when tick occurs
			void(*m_function)();

			// Boolean to determine whether the clock is running
			bool m_ticking = false;

			// Last value gotten from GetTickCount()
			uint32 m_lastTickCount;

			// Thread for this to run start() on -> first call of start() will be run on the main thread. After the first call, the thread will be initialized and start() will run on this thread
			std::thread m_thread;

		public:
			// Public functions
			Clock(uint32 timeout, void(*function)());
			//~Clock();

			// Starts the clock to run
			void start();

			// Stops the clock
			void stop();

			// Getters
			uint32 getTimeout() { return m_timeout; }


		private:
			// Private funtions
			// Called when timeout occurs
			void m_tick();
		};
	}
}
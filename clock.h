#pragma once

#include <chrono>

using namespace std::chrono;

namespace RN
{
	// Class used for measuring timeout.
	class Clock
	{
		public:
		// Default constructor which sets time to 0.
		Clock();
		// Elasped time since last measurement or reset.
		// Returns elapsed time [second].
		double Now();

		// Reset time and starting counting.
		void Reset();

		// Elapsed time since system startup.
		// Returns elapsed time [second].
		static double Total();

		private:

		high_resolution_clock::time_point _t1;
		high_resolution_clock::time_point _t2;
	};
};


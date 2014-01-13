#include <Timer.hpp>

#include <unistd.h>
#include <time.h>

namespace Raster
{
	RAS_BOOL StartTime( )
	{
		static RAS_UINT64 TimeStart = 0ULL;
		static timespec TimeSpec;

		clock_gettime( CLOCK_REALTIME, &TimeSpec );

		RAS_UINT64 Seconds, Nanoseconds;
		Seconds = TimeSpec.tv_sec * 1000000ULL;
		Nanoseconds = TimeSpec.tv_nsec;

		if( TimeStart == 0ULL )
		{
			TimeStart = Seconds + Nanoseconds;
			return 0ULL;
		}

		return RAS_TRUE;
	}

	RAS_UINT64 GetTimeInMicroseconds( )
	{
		static RAS_UINT64 TimeStart = 0ULL;
		struct timespec TimeSpec;

		clock_gettime( CLOCK_REALTIME, &TimeSpec );

		RAS_UINT64 Seconds, Microseconds;

		Seconds = TimeSpec.tv_sec * 1000000ULL;
		Microseconds = TimeSpec.tv_nsec;

		return Seconds + ( ( Microseconds / 1000ULL ) );
	}
}


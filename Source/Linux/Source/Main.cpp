#include <iostream>
#include <Rasteriser.hpp>
#include <Window.hpp>
#include <unistd.h>
#include <Timer.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	Raster::Rasteriser TestRasteriser;
	Raster::Window TestWindow;
	TestWindow.CreateWindow( 0, 0, 800, 600, RAS_NULL );
	Raster::StartTime( );

	if( TestRasteriser.CreateSurfaces( 800, 600, Raster::COLOUR_FORMAT_RGB8,
		2, TestWindow.GetWindow( ), TestWindow.GetDisplay( ) ) != RAS_OK )
	{
		return RAS_FAIL;
	}

	RAS_BYTE *pBufferPtr = RAS_NULL;
	pBufferPtr = pBufferPtr = TestRasteriser.GetCurrentBuffer( );
	TestRasteriser.SetClearColour( 0x20, 0, 0x20 );
	TestRasteriser.Clear( );
	Raster::COLOUR Pixel;
	Pixel.Red = 0x00;
	Pixel.Green = 0xFF;
	Pixel.Blue = 0x00;
	for( int i = 0; i < 200; ++i )
	{
		TestRasteriser.PlotPixel( 400, 300+i, Pixel );
	}

	Raster::POINT Point1, Point2;
	Point1.X = 800;
	Point1.Y = 0;
	Point2.X = 0;
	Point2.Y = 600;
	TestRasteriser.DrawLine( Point1, Point2, Pixel );
	Point1.X = 800;
	Point1.Y = 600;
	Point2.X = 0;
	Point2.Y = 0;
	TestRasteriser.DrawLine( Point1, Point2, Pixel );


	bool Run = true;

	RAS_SINT32 XSpeed = 1, YSpeed = 1;

	RAS_UINT64 TotalRunTime = Raster::GetTimeInMicroseconds( );

	while( Run )
	{
		XEvent Event;
		int Pending = XPending( TestWindow.GetDisplay( ) );
		for( int i = 0; i < Pending; ++i )
		{
			XNextEvent( TestWindow.GetDisplay( ), &Event );

			switch( Event.type )
			{
				case KeyPress:
				{
					KeySym Key = XLookupKeysym( &Event.xkey, 0 );
					if( Key == XK_Escape )
					{
						Run = false;
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}

		// The window should be updated here along with any rasterisation
		// operations
		TestRasteriser.Clear( );
		TestRasteriser.DrawLine( Point1, Point2, Pixel );
		Point1.X += XSpeed;
//		Point1.Y += YSpeed;
/*		if( Point1.X > 800 )
		{
			XSpeed -= XSpeed;
		}
		if( Point1.X <= 0 )
		{
			XSpeed -= XSpeed;
		}*/

		TestRasteriser.SwapBuffers( );
	}

	RAS_UINT64 CompleteRunTime = Raster::GetTimeInMicroseconds( ) - TotalRunTime;

	std::cout << std::endl << std::endl <<
		"-- Post render information ---------------------------------"
		"-------------------" << std::endl;
	std::cout << "Runtime: " << CompleteRunTime << " microseconds" <<
		std::endl;
	std::cout << "Minimum frame time: " <<
		TestRasteriser.GetMinimumFrameTime( ) << " microseconds" << std::endl;
	std::cout << "Maximum frame time: " <<
		TestRasteriser.GetMaximumFrameTime( ) << " microseconds" << std::endl;
	std::cout << "Total rendered frames: " <<
		TestRasteriser.GetFrameCount( ) << std::endl;
	std::cout << "------------------------------------------------------------"
		"-------------------" << std::endl;

	return 0;
}


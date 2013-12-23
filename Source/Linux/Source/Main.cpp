#include <iostream>
#include <Rasteriser.hpp>
#include <Window.hpp>
#include <unistd.h>

int main( int p_Argc, char **p_ppArgv )
{
	Raster::Rasteriser TestRasteriser;

	if( TestRasteriser.CreateSurfaces( 800, 600, Raster::COLOUR_FORMAT_RGB8,
		2 ) != RAS_OK )
	{
		return RAS_FAIL;
	}

	RAS_BYTE *pBufferPtr = RAS_NULL;
	pBufferPtr = pBufferPtr = TestRasteriser.GetCurrentBuffer( );

	Raster::Window TestWindow;
	TestWindow.CreateWindow( 1920, 800, 800, 600 );
	sleep( 3 );

	return 0;
}


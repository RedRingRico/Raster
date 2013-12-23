#include <iostream>
#include <Rasteriser.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	Raster::Rasteriser TestRasteriser;

	if( TestRasteriser.CreateSurfaces( 800, 600, Raster::COLOUR_FORMAT_RGB8,
		2 ) != RAS_OK )
	{
		return RAS_FAIL;
	}
	return 0;
}


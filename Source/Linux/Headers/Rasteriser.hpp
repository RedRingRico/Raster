#ifndef __RASTER_RASTERISER_HPP__
#define __RASTER_RASTERISER_HPP__

#include <DataTypes.hpp>

namespace Raster
{
	typedef enum __R_COLOUR_FORMAT
	{
		COLOUR_FORMAT_RGB8,
		COLOUR_FORMAT_ARGB8,
		COLOUR_FORMAT_RGB565,
		COLOUR_FORMAT_COUNT
	}COLOUR_FORMAT;

	class Rasteriser
	{
	public:
		Rasteriser( );
		~Rasteriser( );

	private:
		Rasteriser( const Rasteriser & );
		Rasteriser &operator=( const Rasteriser & );

		RAS_BYTE	**m_ppRenderBuffers;
		RAS_UINT32	m_BufferCount;
		RAS_UINT32	m_Width;
		RAS_UINT32	m_Height;
		COLOUR_FORMAT	m_ColourFormat;
	};
}

#endif // __RASTER_RASTERISER_HPP__


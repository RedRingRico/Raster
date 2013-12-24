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

	typedef struct __R_COLOUR
	{
		RAS_BYTE	Red;
		RAS_BYTE	Green;
		RAS_BYTE	Blue;
	}COLOUR;

	typedef struct __R_POINT
	{
		RAS_UINT32	X;
		RAS_UINT32	Y;
	}POINT;

	class Rasteriser
	{
	public:
		Rasteriser( );
		~Rasteriser( );

		RAS_UINT32 CreateSurfaces( const RAS_UINT32 p_Width,
			const RAS_UINT32 p_Height, const COLOUR_FORMAT p_ColourFormat,
			const RAS_UINT32 p_BufferCount );

		void SetClearColour( const RAS_BYTE p_Red = 255,
			const RAS_BYTE p_Green = 255,
			const RAS_BYTE p_Blue = 255 );

		void PlotPixel( const RAS_UINT32 p_X, const RAS_UINT32 p_Y,
			const COLOUR &p_Colour );

		void DrawLine( const POINT &p_Point1, const POINT &p_Point2,
			const COLOUR &p_Colour );

		void Clear( );

		void SwapBuffers( );

		RAS_BYTE * const &GetCurrentBuffer( ) const;

	private:
		Rasteriser( const Rasteriser & );
		Rasteriser &operator=( const Rasteriser & );

		RAS_BYTE		**m_ppRenderBuffers;
		RAS_UINT32		m_BufferCount;
		RAS_UINT32		m_CurrentBuffer;
		RAS_UINT32		m_Width;
		RAS_UINT32		m_Height;
		COLOUR_FORMAT	m_ColourFormat;
		RAS_UINT32		m_BytesPerPixel;
		COLOUR			m_ClearColour;
	};
}

#endif // __RASTER_RASTERISER_HPP__


#include <Rasteriser.hpp>
#include <Memory.hpp>
#include <iostream>
#include <cstring>
#include <cmath>
#include <OpenGLExtensionBinder.hpp>
#include <Timer.hpp>

namespace Raster
{
	Rasteriser::Rasteriser( ) :
		m_ppRenderBuffers( RAS_NULL ),
		m_BufferCount( 0 ),
		m_CurrentBuffer( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_ColourFormat( COLOUR_FORMAT_COUNT ),
		m_BytesPerPixel( 0 ),
		m_FrameCount( 0 ),
		m_MinimumFrameTime( 0ULL ),
		m_MaximumFrameTime( 0ULL ),
		m_pDisplay( RAS_NULL ),
		m_Window( 0 )
	{
	}

	Rasteriser::~Rasteriser( )
	{
		SafeDelete2DArray( m_ppRenderBuffers, m_BufferCount );
		rglDeleteBuffers( 1, &m_RenderBuffer );
	}

	RAS_UINT32 Rasteriser::CreateSurfaces( const RAS_UINT32 p_Width,
		const RAS_UINT32 p_Height, const COLOUR_FORMAT p_ColourFormat,
		const RAS_UINT32 p_BufferCount, Window p_Window,
		Display * const &p_pDisplay )
	{
		switch( p_ColourFormat )
		{
			case COLOUR_FORMAT_RGB8:
			{
				m_BytesPerPixel = 3;
				break;
			}
			default:
			{
				std::cout << __FILE__ << " [ " << __LINE__ <<
					" ] Unknown colour format" << std::endl;
				return RAS_FAIL;
			}
		}

		if( p_Width == 0 )
		{
			return RAS_FAIL;
		}

		if( p_Height == 0 )
		{
			return RAS_FAIL;
		}

		if( p_BufferCount == 0 )
		{
			return RAS_FAIL;
		}

		m_Width = p_Width;
		m_Height = p_Height;
		m_BufferCount = p_BufferCount;
		m_ColourFormat = p_ColourFormat;

		std::cout << "Allocating " << m_BufferCount <<
			" renderbuffers of size " << m_Width*m_Height*m_BytesPerPixel <<
			" bytes [ " <<
				static_cast< float >( m_Width*m_Height*m_BytesPerPixel )
					/ 1024.0f / 1024.0f << " MiB ] ... ";
			
		m_ppRenderBuffers = new RAS_BYTE*[ p_BufferCount ];

		for( RAS_UINT32 i = 0; i < m_BufferCount; ++ i )
		{
			m_ppRenderBuffers[ i ] =
				new RAS_BYTE[ m_Width*m_Height*m_BytesPerPixel ];
			memset( m_ppRenderBuffers[ i ], 0xAA,
				m_Width*m_Height*m_BytesPerPixel*sizeof( RAS_BYTE ) );
		}

		std::cout << "[OK]" << std::endl;
		
		rglGenBuffers( 1, &m_RenderBuffer );
		rglBindBuffer( GL_PIXEL_PACK_BUFFER_ARB, m_RenderBuffer );
		rglBufferData( GL_PIXEL_PACK_BUFFER_ARB,
			p_Width*p_Height*m_BytesPerPixel, 0, GL_STREAM_READ_ARB );

		m_pDisplay = p_pDisplay;
		m_Window = p_Window;

		StartTime( );
		m_PreviousTime = GetTimeInMicroseconds( );
		m_MinimumFrameTime = 1000000ULL;
		
		return RAS_OK;
	}

	void Rasteriser::SetClearColour( const RAS_BYTE p_Red,
		const RAS_BYTE p_Green, const RAS_BYTE p_Blue )
	{
		m_ClearColour.Red = p_Red;
		m_ClearColour.Green = p_Green;
		m_ClearColour.Blue = p_Blue;
	}

	void Rasteriser::PlotPixel( const RAS_UINT32 p_X, const RAS_UINT32 p_Y,
		const COLOUR &p_Colour )
	{
		m_ppRenderBuffers[ m_CurrentBuffer ]
			[ ( p_X + ( p_Y*m_Width ) ) * 3 ] = p_Colour.Red;
		m_ppRenderBuffers[ m_CurrentBuffer ]
			[ ( p_X + ( p_Y*m_Width ) )* 3 + 1 ] = p_Colour.Green;
		m_ppRenderBuffers[ m_CurrentBuffer ]
			[ ( p_X + ( p_Y*m_Width ) )* 3 + 2 ] = p_Colour.Blue;
	}

	void Rasteriser::DrawLine( const POINT &p_Point1, const POINT &p_Point2,
		const COLOUR &p_Colour )
	{
		RAS_SINT32 dX, dY, sdX, sdY, dXAbs, dYAbs, X, Y, PointX, PointY;

		dX = p_Point2.X - p_Point1.X;
		dY = p_Point2.Y - p_Point1.Y;

		dXAbs = abs( dX );
		dYAbs = abs( dY );

		sdX = dX > 0 ? 1 : -1;
		sdY = dY > 0 ? 1 : -1;

		X = dYAbs >> 1;
		Y = dXAbs >> 1;

		PointX = p_Point1.X;
		PointY = p_Point1.Y;

		if( dXAbs >= dYAbs )
		{
			for( RAS_SINT32 i = 0; i < dXAbs; ++i )
			{
				Y += dYAbs;
				if( Y >= dXAbs )
				{
					Y -= dXAbs;
					PointY += sdY;
				}
				PointX += sdX;
				this->PlotPixel( PointX, PointY, p_Colour );
			}
		}
		else
		{
			for( RAS_SINT32 i = 0; i < dYAbs; ++i )
			{
				X += dXAbs;
				if( X >= dYAbs )
				{
					X -= dYAbs;
					PointX += sdX;
				}
				PointY += sdY;
				this->PlotPixel( PointX, PointY, p_Colour );
			}
		}
	}

	void Rasteriser::Clear( )
	{
		for( RAS_UINT32 Row = 0; Row < m_Height; ++Row )
		{
			for( RAS_UINT32 Column = 0; Column < ( m_Width * 3 ); )
			{
				m_ppRenderBuffers[ m_CurrentBuffer ]
					[ Column + ( Row * m_Width * 3 ) ] = m_ClearColour.Red;
				++Column;

				m_ppRenderBuffers[ m_CurrentBuffer ]
					[ Column + ( Row * m_Width * 3 ) ] = m_ClearColour.Green;
				++Column;

				m_ppRenderBuffers[ m_CurrentBuffer ]
					[ Column + ( Row * m_Width * 3 ) ] = m_ClearColour.Blue;
				++Column;
			}
		}

	}

	void Rasteriser::SwapBuffers( )
	{
		RAS_UINT64 TheTime = GetTimeInMicroseconds( );

		rglBindBuffer( GL_PIXEL_PACK_BUFFER_ARB, m_RenderBuffer );
		GLubyte *pBufferData = ( GLubyte * )rglMapBuffer(
			GL_PIXEL_PACK_BUFFER_ARB, GL_WRITE_ONLY_ARB );
		if( pBufferData )
		{
			memcpy( pBufferData, m_ppRenderBuffers[ 0 ],
				m_Width * m_Height * m_BytesPerPixel );
			rglUnmapBuffer( GL_PIXEL_PACK_BUFFER_ARB );
		}
		rglBindBuffer( GL_PIXEL_PACK_BUFFER_ARB, 0 );
		glDrawPixels( m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE,
			pBufferData );

		glXSwapBuffers( m_pDisplay, m_Window );

		RAS_UINT64 TimeDifference = TheTime - m_PreviousTime;

		if( TimeDifference < m_MinimumFrameTime )
		{
			m_MinimumFrameTime = TimeDifference;
		}

		if( TimeDifference > m_MaximumFrameTime )
		{
			m_MaximumFrameTime = TimeDifference;
		}

		m_PreviousTime = TheTime;

		++m_FrameCount;

		std::cout << "Took " << TimeDifference << " microseconds to render "
			"frame " << m_FrameCount << std::endl;
	}

	RAS_BYTE * const &Rasteriser::GetCurrentBuffer( ) const
	{
		return m_ppRenderBuffers[ m_CurrentBuffer ];
	}

	RAS_UINT32 Rasteriser::GetFrameCount( ) const
	{
		return m_FrameCount;
	}

	RAS_UINT64 Rasteriser::GetMinimumFrameTime( ) const
	{
		return m_MinimumFrameTime;
	}

	RAS_UINT64 Rasteriser::GetMaximumFrameTime( ) const
	{
		return m_MaximumFrameTime;
	}
}


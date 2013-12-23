#include <Rasteriser.hpp>
#include <Memory.hpp>
#include <iostream>

namespace Raster
{
	Rasteriser::Rasteriser( ) :
		m_ppRenderBuffers( RAS_NULL ),
		m_BufferCount( 0 ),
		m_CurrentBuffer( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_ColourFormat( COLOUR_FORMAT_COUNT ),
		m_BytesPerPixel( 0 )
	{
	}

	Rasteriser::~Rasteriser( )
	{
		SafeDelete2DArray( m_ppRenderBuffers, m_BufferCount );
	}

	RAS_UINT32 Rasteriser::CreateSurfaces( const RAS_UINT32 p_Width,
		const RAS_UINT32 p_Height, const COLOUR_FORMAT p_ColourFormat,
		const RAS_UINT32 p_BufferCount )
	{
		switch( p_ColourFormat )
		{
			case COLOUR_FORMAT_RGB8:
			{
				m_BytesPerPixel = 24;
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
		}

		std::cout << "[OK]" << std::endl;

		return RAS_OK;
	}
}


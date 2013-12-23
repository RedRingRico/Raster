#include <Rasteriser.hpp>
#include <Memory.hpp>

namespace Raster
{
	Rasteriser::Rasteriser( ) :
		m_ppRenderBuffers( RAS_NULL ),
		m_BufferCount( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_ColourFormat( COLOUR_FORMAT_COUNT )
	{
	}

	Rasteriser::~Rasteriser( )
	{
		SafeDelete2DArray( m_ppRenderBuffers, m_BufferCount );
	}
}


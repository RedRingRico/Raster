#include <Window.hpp>

namespace Raster
{
	Window::Window( ) :
		m_Window( 0 ),
		m_pDisplay( RAS_NULL ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_GLContext( RAS_NULL )
	{
	}

	Window::~Window( )
	{
		glXMakeCurrent( m_pDisplay, 0, 0 );
		glXDestroyContext( m_pDisplay, m_GLContext );
		XDestroyWindow( m_pDisplay, m_Window );
		XCloseDisplay( m_pDisplay );
	}
}


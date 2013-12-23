#ifndef __RASTER_WINDOW_HPP__
#define __RASTER_WINDOW_HPP__

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glxext.h>
#include <DataTypes.hpp>

namespace Raster
{
	class Window
	{
	public:
		Window( );
		~Window( );

		RAS_UINT32 CreateWindow( const RAS_UINT32 p_X, const RAS_UINT32 p_Y,
			const RAS_UINT32 p_Width, const RAS_UINT32 p_Height,
			RAS_BYTE * const &p_pPixelData );
		Display * const &GetDisplay( ) const;

	private:
		Window( const Window & );
		Window &operator=( const Window & );

		::Window	m_Window;
		::Display	*m_pDisplay;
		RAS_UINT32	m_X;
		RAS_UINT32	m_Y;
		RAS_UINT32	m_Width;
		RAS_UINT32	m_Height;
		GLXContext	m_GLContext;
		GLuint		m_RenderBuffer;
	};
}

#endif // __RASTER_WINDOW_HPP__


#include <Window.hpp>

namespace Raster
{
	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = RAS_NULL;

	Window::Window( ) :
		m_Window( 0 ),
		m_pDisplay( RAS_NULL ),
		m_X( 0 ),
		m_Y( 0 ),
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

	RAS_UINT32 Window::CreateWindow( const RAS_UINT32 p_X,
		const RAS_UINT32 p_Y, const RAS_UINT32 p_Width,
		const RAS_UINT32 p_Height )
	{
		m_pDisplay = XOpenDisplay( 0 );

		if( !m_pDisplay )
		{
			return RAS_FAIL;
		}

		int VisualAttributes [ ] =
		{
			GLX_X_RENDERABLE,	True,
			GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,	GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
			GLX_RED_SIZE,		8,
			GLX_GREEN_SIZE,		8,
			GLX_BLUE_SIZE,		8,
			GLX_ALPHA_SIZE,		8,
			GLX_DEPTH_SIZE,		24,
			GLX_STENCIL_SIZE,	8,
			GLX_DOUBLEBUFFER,	True,
			None
		};

		int FrameBufferCount = 0;
		GLXFBConfig *pFBC = glXChooseFBConfig( m_pDisplay,
			DefaultScreen( m_pDisplay ), VisualAttributes, &FrameBufferCount );

		if( !FrameBufferCount )
		{
			return RAS_FAIL;
		}

		GLXFBConfig FBConfig = pFBC[ 0 ];

		XFree( pFBC );

		XVisualInfo *pVisualInfo = glXGetVisualFromFBConfig( m_pDisplay,
			FBConfig );

		XSetWindowAttributes WindowAttributes;

		WindowAttributes.colormap = XCreateColormap( m_pDisplay,
			RootWindow( m_pDisplay, pVisualInfo->screen ),
			pVisualInfo->visual, AllocNone );

		WindowAttributes.background_pixmap = None;
		WindowAttributes.border_pixel = 0;
		WindowAttributes.event_mask = StructureNotifyMask;

		m_X = p_X;
		m_Y = p_Y;
		m_Width = p_Width;
		m_Height = p_Height;

		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, pVisualInfo->screen ), m_X, m_Y, m_Width,
			m_Height, 0, pVisualInfo->depth, InputOutput, pVisualInfo->visual,
			CWBorderPixel | CWColormap | CWEventMask, &WindowAttributes );

		XStoreName( m_pDisplay, m_Window, "Raster" );
		XMapWindow( m_pDisplay, m_Window );
		XRaiseWindow( m_pDisplay, m_Window );

		glXCreateContextAttribsARB =
			( PFNGLXCREATECONTEXTATTRIBSARBPROC )glXGetProcAddress(
				( const GLubyte * )"glXCreateContextAttribsARB" );

		int GLContextAttribs [ ] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB,	3,
			GLX_CONTEXT_MINOR_VERSION_ARB,	0,
			None
		};

		m_GLContext = glXCreateContextAttribsARB( m_pDisplay, FBConfig, 0,
			True, GLContextAttribs );

		glXMakeCurrent( m_pDisplay, m_Window, m_GLContext );
		glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glXSwapBuffers( m_pDisplay, m_Window );

		return RAS_OK;
	}
}


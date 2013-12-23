#include <Window.hpp>
#include <Memory.hpp>
#include <GitVersion.hpp>
#include <cstring>
#include <cstdio>

namespace Raster
{
	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = RAS_NULL;
	PFNGLMAPBUFFERARBPROC glMapBufferARB = RAS_NULL;
	PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB = RAS_NULL;
	PFNGLBINDBUFFERARBPROC glBindBufferARB = RAS_NULL;
	PFNGLGENBUFFERSARBPROC glGenBuffersARB = RAS_NULL;
	PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = RAS_NULL;
	PFNGLBUFFERDATAARBPROC glBufferDataARB = RAS_NULL;

	Window::Window( ) :
		m_Window( 0 ),
		m_pDisplay( RAS_NULL ),
		m_X( 0 ),
		m_Y( 0 ),
		m_Width( 0 ),
		m_Height( 0 ),
		m_GLContext( RAS_NULL ),
		m_RenderBuffer( 0 )
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
		const RAS_UINT32 p_Height, RAS_BYTE * const &p_pPixelData )
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

		// You never know, we may run out of stack space...
		char *pTitle = new char[ 1024 ];
		memset( pTitle, '\0', sizeof( char )*1024 );
		sprintf( pTitle, "Raster | Ver. %s [ %s ]", GIT_BUILD_VERSION,
			GIT_TAG_NAME );
		XStoreName( m_pDisplay, m_Window, pTitle );
		SafeDeleteArray( pTitle );

		XMapWindow( m_pDisplay, m_Window );
		XRaiseWindow( m_pDisplay, m_Window );

		glXCreateContextAttribsARB =
			( PFNGLXCREATECONTEXTATTRIBSARBPROC )glXGetProcAddress(
				( const GLubyte * )"glXCreateContextAttribsARB" );

		glMapBufferARB = ( PFNGLMAPBUFFERARBPROC )glXGetProcAddress(
			( const GLubyte * )"glMapBufferARB" );
		
		glUnmapBufferARB = ( PFNGLUNMAPBUFFERARBPROC )glXGetProcAddress(
			( const GLubyte * )"glUnmapBufferARB" );
		glBindBufferARB = ( PFNGLBINDBUFFERARBPROC )glXGetProcAddress(
			( const GLubyte * )"glBindBufferARB" );
		glGenBuffersARB = ( PFNGLGENBUFFERSARBPROC )glXGetProcAddress(
			( const GLubyte * )"glGenBuffersARB" );
		glDeleteBuffersARB = ( PFNGLDELETEBUFFERSARBPROC )glXGetProcAddress(
			( const GLubyte * )"glDeleteBuffersARB" );
		glBufferDataARB = ( PFNGLBUFFERDATAARBPROC )glXGetProcAddress(
			( const GLubyte * )"glBufferDataARB" );

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
		glGenBuffersARB( 1, &m_RenderBuffer );
		glBindBufferARB( GL_PIXEL_PACK_BUFFER_ARB, m_RenderBuffer );
		glBufferDataARB( GL_PIXEL_PACK_BUFFER_ARB, 800*600*3, 0,
			GL_STREAM_READ_ARB );
		GLubyte *pBufferData = ( GLubyte * )glMapBufferARB(
			GL_PIXEL_PACK_BUFFER_ARB, GL_WRITE_ONLY_ARB );
		// Copy pixel data
		if( pBufferData )
		{
			memcpy( pBufferData, p_pPixelData, 800*600*3 );
			glUnmapBufferARB( GL_PIXEL_PACK_BUFFER_ARB );
		}
		glBindBufferARB( GL_PIXEL_PACK_BUFFER_ARB, 0 );
		// Deprecated in GL 3.0, this should be replaced with using a PBO
		// to transfer data to a texture
		glDrawPixels( 800, 600, GL_RGB, GL_UNSIGNED_BYTE, pBufferData );
		glXSwapBuffers( m_pDisplay, m_Window );

		glDeleteBuffersARB( 1, &m_RenderBuffer );

		return RAS_OK;
	}
}


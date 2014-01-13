#include <OpenGLExtensionBinder.hpp>

PFNGLXCREATECONTEXTATTRIBSARBPROC	__rglXCreateContextAttribs = RAS_NULL;
PFNGLMAPBUFFERARBPROC				__rglMapBuffer = RAS_NULL;
PFNGLUNMAPBUFFERARBPROC				__rglUnmapBuffer = RAS_NULL;
PFNGLBINDBUFFERARBPROC				__rglBindBuffer = RAS_NULL;
PFNGLGENBUFFERSARBPROC				__rglGenBuffers = RAS_NULL;
PFNGLDELETEBUFFERSARBPROC			__rglDeleteBuffers = RAS_NULL;
PFNGLBUFFERDATAARBPROC				__rglBufferData = RAS_NULL;

namespace Raster
{
	RAS_BOOL InitialiseOpenGLExtensions( )
	{
		RAS_BOOL GLStatus = RAS_FALSE;

		GLStatus = ( ( __rglMapBuffer =
			( PFNGLMAPBUFFERARBPROC )rglGetProcAddress(
				"glMapBufferARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglUnmapBuffer =
			( PFNGLUNMAPBUFFERARBPROC )rglGetProcAddress(
				"glUnmapBufferARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglBindBuffer =
			( PFNGLBINDBUFFERARBPROC )rglGetProcAddress(
				"glBindBufferARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglGenBuffers =
			( PFNGLGENBUFFERSARBPROC )rglGetProcAddress(
				"glGenBuffersARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglDeleteBuffers =
			( PFNGLDELETEBUFFERSARBPROC )rglGetProcAddress(
				"glDeleteBuffersARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglBufferData =
			( PFNGLBUFFERDATAARBPROC )rglGetProcAddress(
				"glBufferDataARB" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglXCreateContextAttribs =
			( PFNGLXCREATECONTEXTATTRIBSARBPROC )rglGetProcAddress(
				"glXCreateContextAttribsARB" ) ) == RAS_NULL ) || GLStatus;

		return GLStatus;
	}
}


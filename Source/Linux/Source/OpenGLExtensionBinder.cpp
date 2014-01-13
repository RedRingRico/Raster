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
				"glMapBuffer" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglUnmapBuffer =
			( PFNGLUNMAPBUFFERARBPROC )rglGetProcAddress(
				"glUnmapBuffer" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglBindBuffer =
			( PFNGLBINDBUFFERARBPROC )rglGetProcAddress(
				"glBindBuffer" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglGenBuffers =
			( PFNGLGENBUFFERSARBPROC )rglGetProcAddress(
				"glGenBuffers" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglDeleteBuffers =
			( PFNGLDELETEBUFFERSARBPROC )rglGetProcAddress(
				"glDeleteBuffers" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglBufferData =
			( PFNGLBUFFERDATAARBPROC )rglGetProcAddress(
				"glBufferData" ) ) == RAS_NULL ) || GLStatus;

		GLStatus = ( ( __rglXCreateContextAttribs =
			( PFNGLXCREATECONTEXTATTRIBSARBPROC )rglGetProcAddress(
				"glXCreateContextAttribsARB" ) ) == RAS_NULL ) || GLStatus;

		return GLStatus;
	}
}


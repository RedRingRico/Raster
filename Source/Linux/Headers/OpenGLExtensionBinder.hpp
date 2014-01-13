#ifndef __RASTER_OPENGLEXTENSIONBINDER_HPP__
#define __RASTER_OPENGLEXTENSIONBINDER_HPP__

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <GL/glext.h>
#include <DataTypes.hpp>

extern "C"
{
extern PFNGLXCREATECONTEXTATTRIBSARBPROC	__rglXCreateContextAttribs;
extern PFNGLMAPBUFFERARBPROC				__rglMapBuffer;
extern PFNGLUNMAPBUFFERARBPROC				__rglUnmapBuffer;
extern PFNGLBINDBUFFERARBPROC				__rglBindBuffer;
extern PFNGLGENBUFFERSARBPROC				__rglGenBuffers;
extern PFNGLDELETEBUFFERSARBPROC			__rglDeletebuffers;
extern PFNGLBUFFERDATAARBPROC				__rglBufferData;
}

#define rglGetProcAddress( p_Proc )\
	glXGetProcAddressARB( ( const GLubyte * )p_Proc )
#define rglMapBuffer	__rglMapBuffer

namespace Raster
{
	RAS_BOOL InitialiseOpenGLExtensions( );
}

#endif // __RASTER_OPENGLEXTENSIONBINDER_HPP__


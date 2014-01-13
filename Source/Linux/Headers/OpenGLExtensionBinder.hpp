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
extern PFNGLDELETEBUFFERSARBPROC			__rglDeleteBuffers;
extern PFNGLBUFFERDATAARBPROC				__rglBufferData;
}

#define rglGetProcAddress( p_Proc )\
	glXGetProcAddressARB( ( const GLubyte * )p_Proc )

#define rglXCreateContextAttribs	__rglXCreateContextAttribs
#define rglMapBuffer				__rglMapBuffer
#define rglUnmapBuffer				__rglUnmapBuffer
#define rglBindBuffer				__rglBindBuffer
#define rglGenBuffers				__rglGenBuffers
#define rglDeleteBuffers			__rglDeleteBuffers
#define rglBufferData				__rglBufferData

namespace Raster
{
	RAS_BOOL InitialiseOpenGLExtensions( );
}

#endif // __RASTER_OPENGLEXTENSIONBINDER_HPP__


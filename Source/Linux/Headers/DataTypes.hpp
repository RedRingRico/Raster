#ifndef __RASTER_DATATYPES_HPP__
#define __RASTER_DATATYPES_HPP__

#include <cstddef>

typedef unsigned int		RAS_UINT32;
typedef signed int			RAS_SINT32;
typedef unsigned char		RAS_BYTE;
#define RAS_NULL nullptr
typedef size_t				RAS_MEMSIZE;
typedef RAS_UINT32			RAS_BOOL;

const RAS_UINT32 RAS_TRUE	= 1;
const RAS_UINT32 RAS_FALSE	= 0;

const RAS_UINT32	RAS_OK		= 0x1;
const RAS_UINT32	RAS_FAIL	= 0x2;

#endif // __RASTER_DATATYPES_HPP__


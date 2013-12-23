#ifndef __RASTER_DATATYPES_HPP__
#define __RASTER_DATATYPES_HPP__

#include <cstddef>

typedef unsigned int		RAS_UINT32;
typedef unsigned char		RAS_BYTE;
#define RAS_NULL nullptr
typedef size_t				RAS_MEMSIZE;

const RAS_UINT32	RAS_OK		= 0x1;
const RAS_UINT32	RAS_FAIL	= 0x2;

#endif // __RASTER_DATATYPES_HPP__


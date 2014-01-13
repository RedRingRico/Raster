#ifndef __RASTER_DATATYPES_HPP__
#define __RASTER_DATATYPES_HPP__

#include <cstddef>
#include <stdint.h>

typedef unsigned int		RAS_UINT32;
typedef signed int			RAS_SINT32;
typedef uint64_t			RAS_UINT64;
typedef int64_t				RAS_SINT64;
typedef unsigned char		RAS_BYTE;
typedef float				RAS_FLOAT32;
typedef double				RAS_FLOAT64;
#define RAS_NULL nullptr
typedef size_t				RAS_MEMSIZE;
typedef RAS_UINT32			RAS_BOOL;

const RAS_UINT32 RAS_TRUE	= 1;
const RAS_UINT32 RAS_FALSE	= 0;

const RAS_UINT32	RAS_OK		= 0x1;
const RAS_UINT32	RAS_FAIL	= 0x2;

#endif // __RASTER_DATATYPES_HPP__


#ifndef __RASTERISER_MEMORY_HPP__
#define __RASTERISER_MEMORY_HPP__

#include <DataTypes.hpp>

namespace Raster
{
#define SafeDelete( Pointer )\
	{ if( Pointer != RAS_NULL )\
		{ delete Pointer; Pointer = RAS_NULL; }\
	}

#define SafeDeleteArray( Pointer )\
	{ if( Pointer != RAS_NULL )\
		{ delete [ ] Pointer; Pointer = RAS_NULL; }\
	}

#define SafeDelete2DArray( Pointer, Size )\
	{ if( Pointer != RAS_NULL )\
		{ for( RAS_MEMSIZE i = 0; i < Size; ++i )\
			{ if( Pointer[ i ] != RAS_NULL )\
				{ delete [ ] Pointer[ i ]; Pointer[ i ] = RAS_NULL; }\
			}\
			delete [ ] Pointer;\
			Pointer = RAS_NULL;\
		}\
	}
}

#endif // __RASTERISER_MEMORY_HPP__


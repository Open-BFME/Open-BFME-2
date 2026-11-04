// ?rva000AC4C6@WorldHeightMap@@QAEHH@Z
// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// 0x000AC4C6 78B binary-search-free interval lookup over the height map's
// per-interval table. Retail walks the table with a pointer anchored on each
// element's start field (lea edx,[ecx+0x80d0] / mov esi,[edx] / mov ebp,[edx+4])
// and fetches the result through a separate base+index access
// (imul eax,eax,0x28 / mov eax,[eax+ecx+0x80cc]) after returning from the
// loop, so the struct is result@+0, start@+4, extent@+8, size 0x28, and the
// array base sits at this+0x80cc with the count at this+0x80c8.
typedef int Int;
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
Int WorldHeightMap::rva000AC4C6(Int coord)
{
	struct E { Int result; Int start; Int extent; unsigned char pad[0x28-12]; };
	E *intervals = reinterpret_cast<E *>(m_field80CC);
	coord >>= 2;
	Int intervalCount = m_numTextureClasses;
	for (Int intervalIndex = 0; intervalIndex < intervalCount; ++intervalIndex) {
		Int *intervalBounds = &intervals[intervalIndex].start;
		Int s = intervalBounds[0];
		if (s >= 0) {
			if (coord >= s) {
				Int intervalEnd = s + intervalBounds[1];
				if (coord < intervalEnd)
					return intervals[intervalIndex].result;
			}
		}
	}
	return -1;
}
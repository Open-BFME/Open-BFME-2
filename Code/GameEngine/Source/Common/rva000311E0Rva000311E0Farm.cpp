// cl: /O2
// ?rva000311E0@GeneralAllocator@Allocator@EA@@QAEIPBXIPADPAGI@Z
// PPMalloc GeneralAllocator hex/ASCII dump-line formatter (memory_pool.cpp declares it and calls it
// for the "data: %s" field of its block description). Kept in its own unit: the method is self-contained (memset only) and
// compiles exact under its region's /O2; its siblings stay rowed in Common/System/memory_pool.cpp.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include <string.h>

#include "../../Include/Common/GeneralAllocator.h"
namespace EA
{
namespace Allocator
{

unsigned int GeneralAllocator::rva000311E0(const void *src_, unsigned int count, char *ascii, unsigned short *wide, unsigned int cap)
{
	const unsigned char *src = (const unsigned char *)src_;
	if (cap < 5)
	{
		if (cap != 0 && 0 != ascii)
			*ascii = 0;
		if (cap != 0 && wide != 0)
			*wide = 0;
		return 0;
	}
	unsigned short *w_hold = wide;
	unsigned char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	int limit = (cap - 2) >> 2;
	char *a_hold = ascii;
	if (limit > count)
		limit = count;
	if (0 != a_hold)
	{
		memset(a_hold, ' ', cap);
		a_hold[cap - 1] = 0;
	}
	if (w_hold != 0)
	{
		memset(w_hold, ' ', cap * 2);
		w_hold[cap - 1] = 0;
	}
	if (a_hold != 0)
		a_hold[limit * 3 - 1] = '\t';
	if (0 != w_hold)
	{
		_ReadWriteBarrier();
		*(unsigned short *)((char *)w_hold + limit * 6 - 2) = '\t';
	}
	unsigned int i = 0;
	while (i < limit)
	{
		char ci = (char)src[i];
		unsigned char highByte = (unsigned char)ci;
		char hi = hex[highByte >> 4];
		char lo = hex[ci & 0xF];
		if (0 != a_hold)
		{
			a_hold[i * 3 + 0] = hi;
			a_hold[i * 3 + 1] = lo;
			const char d = (char)src[i];
			if (0x20 > d || d >= 0x7F || d == '"' || d == '\'')
				a_hold[limit * 3 + i] = '.';
			else
				a_hold[limit * 3 + i] = d;
		}
		if (w_hold != 0)
		{
			w_hold[i * 3 + 0] = (unsigned short)hi;
			w_hold[i * 3 + 1] = (unsigned short)lo;
			const char d = (char)src[i];
			if (d < 0x20 || d == '"' || d == '\'')
				w_hold[limit * 3 + i] = '.';
			else
				w_hold[limit * 3 + i] = d;
		}
		i++;
	}
fardone:
	return 0;
}
}
}

// ?rva00034A60@GeneralAllocator@Allocator@EA@@QAEPAXIIH@Z
// partial score=0.82 date=2026-10-05
// ?rva00034A60@GeneralAllocator@Allocator@EA@@QAEPAXIIH@Z @0x00034A60 163B Calloc-like
// cl: /O2 /MD
// Clean donor-guided engine: Calloc-like zeroing wrapper around the malloc
// engine 0x33ED0. Target facts: thiscall ecx=this pass-through, args
// (count,size,flags) at esp+4/8/C, total=count*size via imul, call 0x33ED0
// with (total,flags), null check, header at block-4 masked 0x7FFFFFF8, bit1
// selects no-zero return, n=size-4, large n>0x20 via rep stosd/stosb,
// small n<=0x20 via 8-case fall-through switch (jump table at 0x34B0C).
// Donor hint only: BFME1 _Reallocate skeleton + memset32 byte-fill shape;
// no BFME1 globals/ABI/lift bytes. Provider 0x33ED0 via existing Rva006C1F60
// pin 7434 (address only, identity unproven).
#include <string.h>

class Rva006C1F60;

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva00034A60(unsigned int count, unsigned int size, int flags);
};
}
}

class Rva006C1F60 : public EA::Allocator::GeneralAllocator
{
public:
	void *rva00033ED0(unsigned int size, int flags);
};

void *EA::Allocator::GeneralAllocator::rva00034A60(unsigned int count, unsigned int size, int flags)
{
	unsigned int total = count * size;
	void *block = ((Rva006C1F60 *)this)->rva00033ED0(total, flags);
	if (block != 0)
	{
		unsigned int header = *(unsigned int *)((char *)block - 4);
		if ((header & 2) == 0)
		{
			unsigned int n = (header & 0x7FFFFFF8u) - 4;
			if (n > 0x20)
			{
				memset(block, 0, n);
				return block;
			}
			switch ((n >> 2) - 1)
			{
			case 7: ((unsigned int *)block)[0] = 0;
			case 6: ((unsigned int *)block)[1] = 0;
			case 5: ((unsigned int *)block)[2] = 0;
			case 4: ((unsigned int *)block)[3] = 0;
			case 3: ((unsigned int *)block)[4] = 0;
			case 2: ((unsigned int *)block)[5] = 0;
			case 1: ((unsigned int *)block)[6] = 0;
			case 0: ((unsigned int *)block)[7] = 0;
			}
		}
	}
	return block;
}

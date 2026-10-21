// ?rva00033E90@GeneralAllocator@Allocator@EA@@QAEXPAX@Z @0x00033E90 49B.
// PPMalloc GeneralAllocator report close (ReportEnd-like), under the name
// memory_pool.cpp's _Exit and _DumpFragmentation call. A __thiscall member
// that recognises the "PANS" block signature and tail-calls the freeBlock
// pinned at 0x00033150 when the +0x0C byte is clear and +0x0D is set,
// otherwise clears the +0x20 field. The tail-callee must be a member call on
// this same object: that is what keeps ecx live across the byte loads and
// makes the compiler use dl rather than cl. Names are address-derived. No
// // cl: line: the default /O2 tail-call shape matches.

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void rva00033E90(void *p);
	// memory_pool.cpp owns the native 0x00033150 free engine under this ABI.
	void rva00033150(const void *block);
};
}
}

void EA::Allocator::GeneralAllocator::rva00033E90(void *p)
{
	if (p != 0 && *(int *)p == 0x534e4150)
	{
		if (*((char *)p + 0xd) != 0)
		{
			if (*((char *)p + 0xc) == 0)
				return rva00033150(p);
		}
		else
		{
			*(int *)((char *)p + 0x20) = 0;
		}
	}
}

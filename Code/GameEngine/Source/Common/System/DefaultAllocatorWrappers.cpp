// cl: /DNDEBUG /MD
//
// ?Rva0002FFC0Alloc@@YAPAXHH@Z @0x0002FFC0 19B and
// ?Rva0002FFE0Free@@YAXPAXH@Z @0x0002FFE0 17B: default-heap EA wrappers.
//
// Target facts (raw retail, actual ABI):
//   0x0002FFC0 (19B): mov eax,[esp+4]; mov ecx,[0x00DE0814]; push 0; push eax;
//     call 0x00035080; ret. First arg size, second arg ignored (never read).
//   0x0002FFE0 (17B): mov eax,[esp+4]; mov ecx,[0x00DE0814]; push eax;
//     call 0x000338F0; ret. First arg block, second arg ignored (never read).
//   0x00DE0814 is g_heaps.m_defaultAllocator (+0x400 from base 0x00DE0414):
//     written once in _Init (0x00030000 family) as mov [0xDE0814],edx where
//     edx=[0xDE0798]=m_allocators[0]; read here as this for the two
//     GeneralAllocator calls. Only three .text refs to DE0814 exist
//     (2FFC4/2FFE4/30103), so the provider is genuine, not a standalone
//     global. Single BSS owner stays memory_pool.cpp; this TU is extern-only.
//   Callees: 0x00035080 Malloc-like (matched counted lock wrapper, retail REL32 from
//     0x0002FFCD) and 0x000338F0 Free-like (matched in memory_pool.cpp).
//   Names are honest address-derived; no FreelistPool default claim here:
//     pool ctors (0x001EB1CB/0x0006FAEC) store VA 0x0042FFC0/0x0042FFE0,
//     which equal RVA 0x0002FFC0/0x0002FFE0 plus image base 0x00400000,
//     i.e. these same two wrappers expressed as VAs. The earlier
//     address-mismatch exclusion was VA/RVA confusion; no further
//     pool-default provider is asserted beyond the addresses.
// No STL, no header edit, no aliases, no fallbacks.

namespace EA
{
namespace Allocator
{
class GeneralAllocator
{
public:
	void *rva00035080(unsigned int size, int flags);
	void rva000338F0(void *block);
};
}
}

// TU-scoped minimal HeapTable view (+0x400 only). Same tag so
// ?g_heaps@MemoryPool@@3UHeapTable@1@A resolves to the single memory_pool.cpp BSS
// definition. Size 0x410, member at +0x400. No second definition,
// no /alternatename, no initializer, no header edit.
namespace MemoryPool
{
struct HeapTable
{
	unsigned char _pad400[0x400];
	EA::Allocator::GeneralAllocator *m_defaultAllocator;
	unsigned char _tail[0x410 - 0x404];
};

extern HeapTable g_heaps;
} // namespace MemoryPool

void *__cdecl Rva0002FFC0Alloc(int size, int ignored)
{
	(void)ignored;
	return MemoryPool::g_heaps.m_defaultAllocator->rva00035080((unsigned int)size, 0);
}

void __cdecl Rva0002FFE0Free(void *block, int ignored)
{
	(void)ignored;
	MemoryPool::g_heaps.m_defaultAllocator->rva000338F0(block);
}

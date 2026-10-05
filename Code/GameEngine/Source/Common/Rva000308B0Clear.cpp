// cl: /GX-
// ?Rva000308B0Clear@@YAXXZ @ 0x000308B0 17B
// Guarded flag clear: if the init flag at 0x00DE0821 is set, writes 0 to the
// byte at 0x00DE0818, else returns. Evidence: caller at 0x00225401, sibling
// set at 0x00030890 writes 1, getter at 0x000308D0 reads 0x00DE0818.
// Honest address-derived name. No STL.
// TU-scoped minimal HeapTable view (+0x404/+0x40D). Same tag so ?g_heaps@MemoryPool@@3UHeapTable@1@A
// resolves to the single memory_pool.cpp BSS definition. Size 0x410: +0x404 member,
// 8-byte mid pad covering (3 pad + initCount + shutDown) unnamed, +0x40D member, 2-byte tail.
// No definition added here (extern-only stays extern-only), no /alternatename, no header edit.
namespace MemoryPool
{
struct HeapTable
{
	unsigned char _pad404[0x404];
	bool m_clearAllocations;
	unsigned char _mid[0x40D - 0x405];
	bool m_addingHeaps;
	unsigned char _tail[0x410 - 0x40E];
};

extern HeapTable g_heaps;
} // namespace MemoryPool

void Rva000308B0Clear(void)
{
	if (MemoryPool::g_heaps.m_addingHeaps != 0)
		MemoryPool::g_heaps.m_clearAllocations = 0;
}

// cl: /GX-
// ?Rva000308E0AddHeap@@YAXII@Z @ 0x000308E0 16B
// Guarded AddHeap forwarder: if the init flag at 0x00DE0821 is set, tail-jumps
// to the resolved MemoryPool _AddHeap pointer at 0x00DE03E8 with the same
// (id, size) args, else returns. Evidence: callers at 0x0022542E 0x0022543E
// 0x00225449 0x00225454 push (id, size), 0x00030730 stores _AddHeap at
// 0x00DE03E8, flag 0x00DE0821 set only while _Init runs, sibling guard thunks
// at 0x00030890 0x000308B0. Honest address-derived name. No STL.
// TU-scoped minimal HeapTable view (+0x40D only). Same tag so ?g_heaps@MemoryPool@@3UHeapTable@1@A
// resolves to the single memory_pool.cpp BSS definition. Size 0x410, member at +0x40D.
// Forwarder global g_Va00DE03E8 (0x00DE03E8) is a SEPARATE slot filled by
// Rva00030730Init and stays untouched. No second definition, no /alternatename, no header edit.
namespace MemoryPool
{
struct HeapTable
{
	unsigned char _pad40D[0x40D];
	bool m_addingHeaps;
	unsigned char _tail[0x410 - 0x40E];
};

extern HeapTable g_heaps;
} // namespace MemoryPool
extern void (__cdecl *g_Va00DE03E8)(unsigned int id, unsigned int size);

void Rva000308E0AddHeap(unsigned int id, unsigned int size)
{
	if (MemoryPool::g_heaps.m_addingHeaps != 0)
		g_Va00DE03E8(id, size);
}

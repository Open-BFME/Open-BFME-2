// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002ABB20Free@@YGXPAPAXPAUPoolNode002ABB20@@@Z 0x002ABB20 36B
// Unlinks pool node then pushes it to free-list at 0xDA60F0; out gets prev.
// Evidence: callers 0x002ABFEB 0x004907B9; same free-list as 0x0026549E.
struct PoolNode002ABB20
{
	PoolNode002ABB20* m_prev;
	PoolNode002ABB20* m_next;
};

extern void *g_freeList;

void __stdcall Rva002ABB20Free(void** out, PoolNode002ABB20* n)
{
	PoolNode002ABB20* next = n->m_next;
	PoolNode002ABB20* prev = n->m_prev;
	next->m_prev = prev;
	prev->m_next = next;
	PoolNode002ABB20* head = (*(PoolNode002ABB20 **)&g_freeList);
	n->m_prev = head;
	(*(PoolNode002ABB20 **)&g_freeList) = n;
	*out = prev;
}

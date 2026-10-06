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

extern PoolNode002ABB20* g_pool009A60F0;

void __stdcall Rva002ABB20Free(void** out, PoolNode002ABB20* n)
{
	PoolNode002ABB20* next = n->m_next;
	PoolNode002ABB20* prev = n->m_prev;
	next->m_prev = prev;
	prev->m_next = next;
	PoolNode002ABB20* head = g_pool009A60F0;
	n->m_prev = head;
	g_pool009A60F0 = n;
	*out = prev;
}
// ?g_pool009A60F0@@3PAUPoolNode002ABB20@@A: the global at VA 0xda60f0 is ?g_freeList@@3PAXA.
#pragma comment(linker, "/alternatename:?g_pool009A60F0@@3PAUPoolNode002ABB20@@A=?g_freeList@@3PAXA")

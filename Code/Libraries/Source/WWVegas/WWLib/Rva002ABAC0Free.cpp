// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002ABAC0Free@@YGXPAPAXPAUPoolNode002ABAC0@@@Z, RVA 0x002ABAC0, size 36.
// Evidence: same unlink-push-free shape as 0x002ABB20 pool free; global g_00DBBD34; out gets prev; caller 0x002ABD48.
struct PoolNode002ABAC0
{
	PoolNode002ABAC0* m_prev;
	PoolNode002ABAC0* m_next;
};

// g_00DBBD34: matched references place it at VA 0xdbbd34 (retail .data initial value 0).
PoolNode002ABAC0* g_00DBBD34 = 0;

void __stdcall Rva002ABAC0Free(void** out, PoolNode002ABAC0* n)
{
	PoolNode002ABAC0* next = n->m_next;
	PoolNode002ABAC0* prev = n->m_prev;
	next->m_prev = prev;
	prev->m_next = next;
	PoolNode002ABAC0* head = g_00DBBD34;
	n->m_prev = head;
	g_00DBBD34 = n;
	*out = prev;
}

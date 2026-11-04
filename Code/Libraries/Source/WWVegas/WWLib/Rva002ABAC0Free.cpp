// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002ABAC0Free@@YGXPAPAXPAUPoolNode002ABAC0@@@Z, RVA 0x002ABAC0, size 36.
// Evidence: same unlink-push-free shape as 0x002ABB20 pool free; global g_00DBBD34; out gets prev; caller 0x002ABD48.
struct PoolNode002ABAC0
{
	PoolNode002ABAC0* m_prev;
	PoolNode002ABAC0* m_next;
};

// The free-list head is the +8 member of the complete pool at VA 0xDBBD2C.
class FreelistPool;
extern FreelistPool g_freelistPool009BBD2C;
#define g_00DBBD34 (*(PoolNode002ABAC0 **)((char *)&g_freelistPool009BBD2C + 8))

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

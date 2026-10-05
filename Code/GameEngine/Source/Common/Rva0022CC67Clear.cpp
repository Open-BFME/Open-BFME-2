// cl: /O1 /DNDEBUG /MD /GX
// ?rva0022CC67@Rva0022CC67@@QAEXXZ @0x0022CC67 73B leaf array-of-lists clear
// calling rowed ?Rva0022C8FBDestroy@@YGXPAURva0022C8FBElem@@@Z at 0x0022C8FB.
// Start at +4 end at +8 count=(end-start)>>2; each slot frees its Elem chain
// via m_next at +0 then clears the slot; size at +0x10 cleared. Evidence:
// chain packet calls rowed 0x0022C8FB; caller 0x0022CF13 destructor calls here
// then frees the bucket array; same 73B shape as rowed 0x002A8FE0.
// Retail mov ecx esi before call proves thiscall receiver; the Destroy body
// ignores ecx so the rowed stdcall body is ICF-identical and the member
// spelling aliases it (symbols.csv pin plus /alternatename).
struct Rva0022C8FBElem
{
	void *m_next;
};

class Rva0022CC67
{
public:
	void rva0022CC67();
	void Free(struct Rva0022C8FBElem *p);
private:
	char m_00[4];
	struct Rva0022C8FBElem **m_start;
	struct Rva0022C8FBElem **m_end;
	char m_0C[4];
	int m_10;
};

#pragma comment(linker, "/alternatename:?Free@Rva0022CC67@@QAEXPAURva0022C8FBElem@@@Z=?Rva0022C8FBDestroy@@YGXPAURva0022C8FBElem@@@Z")
void Rva0022CC67::rva0022CC67()
{
	unsigned i = 0;
	for (; i < (unsigned)(((char *)m_end - (char *)m_start) >> 2); ++i) {
		struct Rva0022C8FBElem *node = m_start[i];
		while (node) {
			struct Rva0022C8FBElem *next = (struct Rva0022C8FBElem *)node->m_next;
			Free(node);
			node = next;
		}
		m_start[i] = 0;
	}
	m_10 = 0;
}

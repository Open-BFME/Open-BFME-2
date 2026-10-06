// cl: /MD
// ?rva0029B63A@Rva0029B63A@@QAEXPAURva0029B63ANode@@@Z @0x0029B63A 45B.
// Unlocks 0x0029E015. Recursive child at +0xC then free list via +0x8; thiscall ret 4. Callees rowed _free 0x30830 plus self.
// Callers at 0x0029B64C self and 0x0029E023.
struct Rva0029B63ANode {
	void *m_0;
	void *m_4;
	Rva0029B63ANode *m_8;
	Rva0029B63ANode *m_C;
};
class Rva0029B63A {
public:
	void rva0029B63A(Rva0029B63ANode *p);
};
extern "C" void __cdecl free(void *block);
void Rva0029B63A::rva0029B63A(Rva0029B63ANode *p)
{
	if (p == 0)
		return;
	Rva0029B63ANode *cur = p;
	do {
		rva0029B63A(cur->m_C);
		Rva0029B63ANode *next = cur->m_8;
		free(cur);
		cur = next;
	} while (cur != 0);
}

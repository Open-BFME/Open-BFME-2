// cl: /MD
// ?rva0029B667@Rva0029B667@@QAEXPAURva0029B667Node@@@Z @0x0029B667 45B.
// Unlocks 0x0029E03E. Twin of 0x0029B63A: recursive child at +0xC then free list via +0x8; thiscall ret 4. Callees rowed _free 0x30830 plus self.
// Callers at 0x0029B679 self and 0x0029E04C.
struct Rva0029B667Node {
	void *m_0;
	void *m_4;
	Rva0029B667Node *m_8;
	Rva0029B667Node *m_C;
};
class Rva0029B667 {
public:
	void rva0029B667(Rva0029B667Node *p);
};
extern "C" void __cdecl free(void *block);
void Rva0029B667::rva0029B667(Rva0029B667Node *p)
{
	if (p == 0)
		return;
	Rva0029B667Node *cur = p;
	do {
		rva0029B667(cur->m_C);
		Rva0029B667Node *next = cur->m_8;
		free(cur);
		cur = next;
	} while (cur != 0);
}

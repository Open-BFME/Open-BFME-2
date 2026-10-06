// ?rva0036426E@Rva0036426E@@QAEXPAUFreeNode@@@Z
// cl: /DNDEBUG /MD
//
// Rva0036426E free-list helper, retail 0x0036426E, 45 bytes: recurse on +0xC
// then free via rowed _free walking +8. Evidence: self-call plus _free row
// 0x00030830 and callers 0x00364A37/0x00364A60; Path neighbours prove
// /O1 /arch:SSE flags; LINK BONUS via 0x00364521 chain.
extern "C" void __cdecl free(void *);

struct FreeNode
{
	void *m_unknown00;
	void *m_unknown04;
	FreeNode *m_next;
	FreeNode *m_child;
};

class Rva0036426E
{
public:
	void rva0036426E(FreeNode *head);
};

void Rva0036426E::rva0036426E(FreeNode *head)
{
	if (head == 0)
		return;
	FreeNode *cur = head;
	do {
		rva0036426E(cur->m_child);
		FreeNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur != 0);
}

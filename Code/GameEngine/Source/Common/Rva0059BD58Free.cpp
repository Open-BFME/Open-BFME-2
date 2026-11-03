// cl: /MD
// ?rva0059BD58@Rva0059BD58@@QAEXPAURva0059BD58Node@@@Z @0x0059BD58 (45B)
// Recursive list free: for each node recurse into child at +0xC with same
// this then free the node via rowed _free 0x00030830 and advance to +0x8.
// Same 45B shape as Rva00254D0BFree plus Rva001FD42BErase. Caller 0x0059BDC7.
// Evidence: self-call plus unlock lane.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct Rva0059BD58Node
{
	char m_pad[8];
	Rva0059BD58Node *m_next;
	void *m_child;
};
class Rva0059BD58
{
public:
	void rva0059BD58(Rva0059BD58Node *head);
};
void Rva0059BD58::rva0059BD58(Rva0059BD58Node *head)
{
	Rva0059BD58Node *cur = head;
	if (!cur)
		return;
	do {
		rva0059BD58((Rva0059BD58Node *)cur->m_child);
		Rva0059BD58Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

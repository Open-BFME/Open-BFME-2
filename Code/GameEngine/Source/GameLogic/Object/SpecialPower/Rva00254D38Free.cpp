// cl: /DNDEBUG /MD
// ?rva00254D38@Rva00254D38@@QAEXPAURva00254D38Node@@@Z @0x00254D38 45B.
// Recursive list free twin of 0x00254D0B: for each node recurse into child
// at +0xC with same this then free the node via rowed _free 0x00030830 and
// advance to +0x8. Self-call at 0x00254D4A plus caller 0x00255CB6.
// __thiscall method (this in ecx saved to ebx). Neighbour flags /O1 /DNDEBUG.
extern "C" void __cdecl free(void *block);
struct Rva00254D38Node
{
	char m_pad[8];
	Rva00254D38Node *m_next08;
	void *m_child0C;
};
class Rva00254D38
{
public:
	void rva00254D38(Rva00254D38Node *head);
};
void Rva00254D38::rva00254D38(Rva00254D38Node *head)
{
	Rva00254D38Node *cur = head;
	if (!cur)
		return;
	do {
		rva00254D38((Rva00254D38Node *)cur->m_child0C);
		Rva00254D38Node *next = cur->m_next08;
		free(cur);
		cur = next;
	} while (cur);
}

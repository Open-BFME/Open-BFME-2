// cl: /DNDEBUG /MD
// ?rva00254D0B@Rva00254D0B@@QAEXPAURva00254D0BNode@@@Z @0x00254D0B 45B.
// Recursive list free: for each node recurse into child at +0xC with same
// this then free the node via rowed _free 0x00030830 and advance to +0x8.
// Self-call at 0x00254D1D plus caller 0x00255CDF. __thiscall method (this in
// ecx saved to ebx for the recursive call). Neighbour flags /O1 /DNDEBUG.
extern "C" void __cdecl free(void *block);
struct Rva00254D0BNode
{
	char m_pad[8];
	Rva00254D0BNode *m_next08;
	void *m_child0C;
};
class Rva00254D0B
{
public:
	void rva00254D0B(Rva00254D0BNode *head);
};
void Rva00254D0B::rva00254D0B(Rva00254D0BNode *head)
{
	Rva00254D0BNode *cur = head;
	if (!cur)
		return;
	do {
		rva00254D0B((Rva00254D0BNode *)cur->m_child0C);
		Rva00254D0BNode *next = cur->m_next08;
		free(cur);
		cur = next;
	} while (cur);
}

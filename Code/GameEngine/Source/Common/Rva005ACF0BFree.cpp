// cl: /MD
// ?rva005ACF0B@Rva005ACF0B@@QAEXPAURva005ACF0BNode@@@Z retail 0x005ACF0B 45B
// Evidence: unlock lane; recursive child free via [esi+0xc] plus next-chain free via [esi+0x8] with game _free 0x00030830; ret 4 so thiscall with one stack param; caller 0x005AD093.
extern "C" void __cdecl free(void *ptr);

struct Rva005ACF0BNode
{
	char m_pad[8];
	struct Rva005ACF0BNode *m_next;
	struct Rva005ACF0BNode *m_child;
};

class Rva005ACF0B
{
public:
	void rva005ACF0B(struct Rva005ACF0BNode *node);
};

void Rva005ACF0B::rva005ACF0B(struct Rva005ACF0BNode *node)
{
	if (node == 0)
		return;
	do
	{
		rva005ACF0B(node->m_child);
		struct Rva005ACF0BNode *next = node->m_next;
		free(node);
		node = next;
	} while (node != 0);
}

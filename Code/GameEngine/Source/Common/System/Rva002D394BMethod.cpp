// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D394B@Rva002D394B@@QAEXPAX@Z retail 0x002D394B 45 bytes. Recursive
// list/tree free: child at +0xC recursed with same this, next at +0x8 freed
// in a loop via rowed free 0x00030830. Evidence: callers 0x002D395D self and
// 0x002D43D4 in 0x002D43C6 which passes [header+4] then resets header links.
extern "C" void __cdecl free(void *block);

class Rva002D394B
{
public:
	void rva002D394B(void *p);
};

struct Rva002D394BNode
{
	char m_pad[8];
	void *m_next;
	void *m_child;
};

void Rva002D394B::rva002D394B(void *p)
{
	if (p == 0)
		return;
	Rva002D394BNode *cur = (Rva002D394BNode *)p;
	do
	{
		rva002D394B(cur->m_child);
		Rva002D394BNode *next = (Rva002D394BNode *)cur->m_next;
		free(cur);
		cur = next;
	} while (cur != 0);
}

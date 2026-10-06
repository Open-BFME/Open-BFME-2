// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000B646B@Rva000B646B@@QAEXPAURva000B646BNode@@@Z, retail 0x000B646B, 45 bytes.
// __thiscall method freeing a linked structure: if arg null return; else loop
// recursing on node+0xc then freeing the node via rowed _free 0x00030830 and
// advancing to node+8. Self-recursive call at 0x000B647D; caller 0x000B9309
// passes [eax+4] with this preserved. Honest address name.
extern "C" void __cdecl free(void *block);

struct Rva000B646BNode
{
	int m0;
	int m1;
	struct Rva000B646BNode *m_next;
	struct Rva000B646BNode *m_child;
};

class Rva000B646B
{
public:
	void rva000B646B(struct Rva000B646BNode *n);
};

void Rva000B646B::rva000B646B(struct Rva000B646BNode *n)
{
	if (!n)
		return;
	do
	{
		rva000B646B(n->m_child);
		struct Rva000B646BNode *next = n->m_next;
		free(n);
		n = next;
	} while (n);
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000B6498@Rva000B6498@@QAEXPAURva000B6498Node@@@Z, retail 0x000B6498, 45 bytes.
// __thiscall method freeing a linked structure: if arg null return; else loop
// recursing on node+0xc then freeing the node via rowed _free 0x00030830 and
// advancing to node+8. Twin of rowed 0x000B646B (same 45B shape). Self call at
// 0x000B64AA; caller 0x000B9332. Honest address name.
extern "C" void __cdecl free(void *block);

struct Rva000B6498Node
{
	int m0;
	int m1;
	struct Rva000B6498Node *m_next;
	struct Rva000B6498Node *m_child;
};

struct Rva000B6498Head
{
	int m00;
	struct Rva000B6498Node *m04;
	struct Rva000B6498Head *m08;
	struct Rva000B6498Head *m0c;
};

class Rva000B6498
{
public:
	void rva000B6498(struct Rva000B6498Node *n);
	void rva000B9324();
private:
	struct Rva000B6498Head *m_head;
	int m_count;
};

void Rva000B6498::rva000B6498(struct Rva000B6498Node *n)
{
	if (!n)
		return;
	do
	{
		rva000B6498(n->m_child);
		struct Rva000B6498Node *next = n->m_next;
		free(n);
		n = next;
	} while (n);
}

// ?rva000B9324@Rva000B6498@@QAEXXZ 0x000B9324 41B
// Evidence: unlock lane; same this as rowed 0x000B6498 free call at 0x000B9332; caller 0x000BB694 unclaimed 56B; sentinel reset m08 m0c self m04 m_count zero.
void Rva000B6498::rva000B9324()
{
	if (m_count == 0)
		return;
	rva000B6498(m_head->m04);
	m_head->m08 = m_head;
	m_head->m04 = 0;
	m_head->m0c = m_head;
	m_count = 0;
}

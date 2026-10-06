// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004070D4@Rva004070D4@@QAEXPAURva004070D4Node@@@Z retail 0x004070D4 45B
// ?rva0040748D@Rva004070D4@@QAEXXZ retail 0x0040748D 41B
// Evidence: chain via 0x004070D4; reset sentinel same class; caller 0x004075A8.
// Evidence: unlock lane; same tree-free shape as Rva007590B0 51B but /O1 push-mem plus pop-ecx; callers 0x0040748D plus self; prev CreateAHeroElementCopy same /O1.
struct Rva004070D4Node
{
	char m_pad[8];
	Rva004070D4Node *m_next;
	Rva004070D4Node *m_child;
};

struct Rva004070D4Head
{
	char m_pad0[4];
	Rva004070D4Node *m_child;
	Rva004070D4Head *m_next;
	Rva004070D4Head *m_other;
};


class Rva004070D4
{
public:
	void rva004070D4(Rva004070D4Node *node);
	void rva0040748D();
private:
	Rva004070D4Head *m_head;
	void *m_state;
};

extern "C" void __cdecl free(void *block);

void Rva004070D4::rva0040748D()
{
	if (m_state == 0)
		return;
	rva004070D4(m_head->m_child);
	m_head->m_next = m_head;
	m_head->m_child = 0;
	m_head->m_other = m_head;
	m_state = 0;
}

void Rva004070D4::rva004070D4(Rva004070D4Node *node)
{
	if (node == 0)
		return;
	Rva004070D4Node *cur = node;
	do {
		rva004070D4(cur->m_child);
		Rva004070D4Node *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur != 0);
}

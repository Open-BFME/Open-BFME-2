// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E0D66@Rva002E0D66@@QAEXPAX@Z @0x002E0D66 45B recursive free of two-link list
// Evidence: callee rowed 0x00030830 free; self recursion; callers 0x002E0D78 self and 0x002E15F4; neighbours 0x002E0CD4 getter and 0x002E0D93 assign share /O1
extern "C" void __cdecl free(void *);

struct Rva002E0D66Node
{
	char m_pad[8];
	Rva002E0D66Node *m_8;
	Rva002E0D66Node *m_c;
};

class Rva002E0D66
{
public:
	void rva002E0D66(void *head);
};

void Rva002E0D66::rva002E0D66(void *head)
{
	Rva002E0D66Node *p = (Rva002E0D66Node *)head;
	if (p == 0)
		return;
	do
	{
		rva002E0D66(p->m_c);
		Rva002E0D66Node *next = p->m_8;
		free(p);
		p = next;
	} while (p != 0);
}

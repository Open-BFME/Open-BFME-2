// cl: /MD
//
// ?rva00556050@Rva00556050@@QAEXPAURva00556050Node@@@Z @0x00556050 53B
// Chain lane: recursive list teardown calling the landed dtor 0x00555B79.
// Each node holds next at +8, child at +0xc and the Rva00555B79 object at
// +0x10; children are torn down first, then the member is destroyed
// explicitly and the node freed. Caller 0x005562DD.

extern "C" void __cdecl free(void *block);

class Gen_uw_00385371
{
public:
	~Gen_uw_00385371();
};

class Rva00555B79
{
public:
	~Rva00555B79();

private:
	int m_pad0;
	Gen_uw_00385371 m_member;
};

struct Rva00556050Node
{
	int m_pad0;
	int m_pad1;
	Rva00556050Node *m_next; // +8
	Rva00556050Node *m_child; // +0xc
	Rva00555B79 m_obj; // +0x10
};

class Rva00556050
{
public:
	void rva00556050(Rva00556050Node *head);
};

void Rva00556050::rva00556050(Rva00556050Node *head)
{
	Rva00556050Node *cur = head;
	if (cur == 0)
		return;
	do
	{
		rva00556050(cur->m_child);
		Rva00556050Node *next = cur->m_next;
		cur->m_obj.~Rva00555B79();
		free(cur);
		cur = next;
	} while (cur != 0);
}

// cl: /O1 /DNDEBUG /MD /EHsc
// Native5C98C0..5C98F6: guard singleton+ B0, query region by ID and
// receiver+1C, retain returned pointer only when byte+1A2 is nonzero.
// Global, callee and offsets are target evidence. Item API names unproven.
// This caller proves the owned20FAB4 provider returns a pointer; its previous
// void declaration hid the observed return contract.
struct Rva0020FAB4Ret
{
	char m_pad[0x1a2];
	unsigned char m_1a2;
};

class Rva0020EE29
{
public:
	void *rva0020FAB4(int a1, int a2);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva0020EE29 *m_b0;
};

extern Rva002BA8F1Logic *g_009FEF10;


class Rva005C98C0
{
public:
	void *rva005C98C0(int id);
private:
	char m_pad00[0x1c];
	int m_1c;
};

void *Rva005C98C0::rva005C98C0(int id){Rva0020FAB4Ret*p=0;if(g_009FEF10&&g_009FEF10->m_b0){p=(Rva0020FAB4Ret*)g_009FEF10->m_b0->rva0020FAB4(id,m_1c);if(p&&!p->m_1a2)p=0;}return p;}

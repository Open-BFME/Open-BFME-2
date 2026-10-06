// cl: /DNDEBUG /MD /EHsc
// ?rva00395D18@Rva00395D18@@QAEXPAX@Z RVA 0x00395D18 size 45 unlock recursive free via +C iterate via +8.
extern "C" void __cdecl free(void *);
struct Rva00395D18Node
{
	int m_a;
	int m_b;
	Rva00395D18Node *m_next;
	Rva00395D18Node *m_child;
};
class Rva00395D18
{
public:
	void rva00395D18(void *p);
};
void Rva00395D18::rva00395D18(void *p)
{
	Rva00395D18Node *n = (Rva00395D18Node *)p;
	if (!n)
		return;
	do
	{
		rva00395D18(n->m_child);
		Rva00395D18Node *next = n->m_next;
		free(n);
		n = next;
	} while (n);
}

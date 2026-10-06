// cl: /DNDEBUG /MD /EHsc
// ?rva00395CEB@Rva00395CEB@@QAEXPAX@Z RVA 0x00395CEB size 45 unlock recursive free via +C iterate via +8.
extern "C" void __cdecl free(void *);
struct Rva00395CEBNode
{
	int m_a;
	int m_b;
	Rva00395CEBNode *m_next;
	Rva00395CEBNode *m_child;
};
class Rva00395CEB
{
public:
	void rva00395CEB(void *p);
};
void Rva00395CEB::rva00395CEB(void *p)
{
	Rva00395CEBNode *n = (Rva00395CEBNode *)p;
	if (!n)
		return;
	do
	{
		rva00395CEB(n->m_child);
		Rva00395CEBNode *next = n->m_next;
		free(n);
		n = next;
	} while (n);
}

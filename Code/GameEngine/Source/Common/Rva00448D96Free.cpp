// cl: /MD
// ?rva00448D96@Rva00448D96@@QAEXPAURva00448D96Node@@@Z retail 0x00448D96 53B
// List/tree free walking two links: if null return; recurse on m_0c with same
// this; destroy Rva00448089 value at +0x10 via rowed dtor 0x00448089; free node
// via rowed _free 0x00030830; loop via m_08. Evidence: push ebx esi edi test
// je recursion call dtor free test jne; unblocks 0x00448E3B; chain from dtor.
class Rva00448089
{
public:
	~Rva00448089();
};
extern "C" void __cdecl free(void *block);
struct Rva00448D96Node
{
	int m_00;
	int m_04;
	Rva00448D96Node *m_08;
	Rva00448D96Node *m_0c;
	Rva00448089 m_10;
};
class Rva00448D96
{
public:
	void rva00448D96(Rva00448D96Node *node);
};
void Rva00448D96::rva00448D96(Rva00448D96Node *node)
{
	if (node == 0)
		return;
	Rva00448D96Node *p = node;
	do
	{
		rva00448D96(p->m_0c);
		Rva00448D96Node *next = p->m_08;
		p->m_10.~Rva00448089();
		free(p);
		p = next;
	} while (p != 0);
}

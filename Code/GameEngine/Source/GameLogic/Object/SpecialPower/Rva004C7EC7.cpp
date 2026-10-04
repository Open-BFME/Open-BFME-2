// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva004C7EC7Update@@YAXPAX00@Z @0x004C7EC7 52B: free update calling Rva001E11F8 0x001E11F8 and ObjectCreationList 0x001F0410.
// Evidence: rowed callees 0x001E11F8 0x001F0410 with same two args; neighbours share flags.

class ObjectCreationList
{
public:
	void rva001F0410(void *a, void *b);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

struct Rva004C7EC7Holder
{
	char m_pad[0xA4];
	Rva001E11F8 *m_a4;
	ObjectCreationList *m_a8;
};

void __cdecl Rva004C7EC7Update(void *p, void *a, void *b)
{
	Rva004C7EC7Holder *h = (Rva004C7EC7Holder *)p;
	if (h->m_a4)
		h->m_a4->rva001E11F8((int)a, (int)b);
	if (h->m_a8)
		h->m_a8->rva001F0410(a, b);
}

// cl: /O1 /arch:SSE /G7 /Ob0
// Address-based member name; packet boundary and caller xref support the address, but no class identity is proven.
struct Rva002FDB44;

struct Rva002FDB44Link
{
	char m_pad[0xF4];
	Rva002FDB44 *m_item;
};

class Rva002FDB44
{
	char m_pad00[0x18];
	Rva002FDB44Link *m_link;
	char m_pad1C[0x1A0];
	Rva002FDB44 *m_previous;

public:
	void rva002FDB44(Rva002FDB44 *item);
};

void Rva002FDB44::rva002FDB44(Rva002FDB44 *item)
{
	Rva002FDB44Link *link = m_link;
	Rva002FDB44 *previous = link->m_item;
	item->m_previous = previous;
	link->m_item = item;
}

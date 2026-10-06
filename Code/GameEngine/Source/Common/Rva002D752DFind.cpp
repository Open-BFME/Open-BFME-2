// cl: /DNDEBUG /MD
//
// ?rva002D752D@Rva002D752D@@QAEPAURva002D752DNode@@ABV?$StringBase@D@@@Z @0x002D752D (39B).
// Finds node by AsciiString compare walking +0x04 next from head at +0x0C.
// Retail loads head at this+0x0C then StringBase at node+0x08 calling rowed
// compare at 0x000069D6 returning node or null. Evidence: 20 callers;
// honest Rva container and node plus rowed StringBase compare.

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &other) const;

private:
	void *m_data;
};

struct Rva002D752DNode
{
	unsigned char m_pad[4];
	Rva002D752DNode *m_next;
	StringBase<char> m_name;
};

class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);

private:
	unsigned char m_pad[0x0C];
	Rva002D752DNode *m_head;
};

Rva002D752DNode *Rva002D752D::rva002D752D(const StringBase<char> &name)
{
	for (Rva002D752DNode *cur = m_head; cur; cur = cur->m_next) {
		if (cur->m_name.compare(name) == 0)
			return cur;
	}
	return 0;
}

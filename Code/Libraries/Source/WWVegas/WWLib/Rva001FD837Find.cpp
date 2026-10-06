// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva001FD837Find@@YAXPAPAXPAURva001FD837Node@@1ABVAsciiString@@@Z @0x001FD837 39B
// List find: iterates nodes from first to last (next at +0x00), compares the
// AsciiString at +0x08 via rowed StringBase compare at 0x000069D6, stores the
// match (or last) through the out pointer. Callers at 0x001FD9E2 and 0x005BAA96.
#include "ascii_string.h"


struct Rva001FD837Node
{
	Rva001FD837Node *m_next;
	char m_pad[4];
	AsciiString m_data;
};

void __cdecl Rva001FD837Find(
	void **out,
	Rva001FD837Node *first,
	Rva001FD837Node *last,
	const AsciiString &value)
{
	Rva001FD837Node *it = first;
	while (it != last)
	{
		if (it->m_data.compare(value) == 0)
			break;
		it = it->m_next;
	}
	*out = it;
}

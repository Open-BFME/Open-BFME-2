// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0022307F@@QAE@ABVAsciiString@@ABVRva00468520@@@Z @0x0022307F 30B
// Ctor over AsciiString at +0 via rowed StringBase<char> copy 0x000365F0 and Rva00468520 at +4 via rowed set 0x004F62FE.
// Evidence: rowed set 0x004F62FE copies a reference pointer and an index. Caller
// 0x0022402A builds a 12B key/value record at ebp-0x24; ret 8 takes two refs.
#include "ascii_string.h"

class Rva00468520
{
public:
	Rva00468520 *set(const Rva00468520 *src) throw();
private:
	void *m_reference;
	int m_index;
};

class Rva0022307F
{
public:
	Rva0022307F(const AsciiString &head, const Rva00468520 &item);
private:
	AsciiString m_head;
	Rva00468520 m_item;
};

Rva0022307F::Rva0022307F(const AsciiString &head, const Rva00468520 &item) : m_head(head)
{
	m_item.set(&item);
}

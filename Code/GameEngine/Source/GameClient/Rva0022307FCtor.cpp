// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0022307F@@QAE@ABVAsciiString@@ABVRva00468520@@@Z @0x0022307F 30B
// Ctor over AsciiString at +0 via rowed StringBase<char> copy 0x000365F0 and Rva00468520 at +4 via rowed set 0x004F62FE.
// Evidence: same shape as rowed ??0Rva0022304A 0x002233F0 but second member is ref-counted Rva00468520 with no dtor so no EH prolog; caller 0x0022402A builds 12B temp at ebp-0x24 then feeds eax to 0x002237C7; ret 8 two refs.
#include "ascii_string.h"

class Rva00468520
{
public:
	Rva00468520 *set(const Rva00468520 *src) throw();
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

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0022304A@@QAE@ABVAsciiString@@ABVRva0022300F@@@Z @0x002233F0 57B
// Ctor over AsciiString at +0 via rowed StringBase<char> copy 0x000365F0 and Rva0022300F at +4 via rowed copy 0x00223226.
// Evidence: caller 0x00224BDB builds temp at -0x34 via this then destroys as ??1Rva0022304A; dtor 0x0022304A layout AsciiString +0 Rva0022300F +4; ret 8 two refs; EH prolog with and ebp-4 0.
#include "ascii_string.h"

class Rva0022300F
{
public:
	Rva0022300F(const Rva0022300F &o);
	~Rva0022300F();
};

class Rva0022304A
{
public:
	Rva0022304A(const AsciiString &head, const Rva0022300F &item);
private:
	AsciiString m_head;
	Rva0022300F m_item;
};

Rva0022304A::Rva0022304A(const AsciiString &head, const Rva0022300F &item) : m_head(head), m_item(item)
{
}

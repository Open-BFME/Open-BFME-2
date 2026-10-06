// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0022304A@@QAE@ABV0@@Z @0x002235B6 61B
// Copy ctor of the AsciiString-keyed pair Rva0022304A: AsciiString at +0 via the rowed
// StringBase<char> copy 0x000365F0, then Rva0022300F at +4 via its rowed copy 0x00223226,
// under an __EH_prolog frame (and [ebp-4] 0 after the first member); ret 4, one ref.
// Evidence: same member layout and copy calls as the rowed ctor 0x002233F0 and dtor
// 0x0022304A; sole caller 0x002238B4 (the node builder of the hash_map chain under
// bfmeSetText 0x00225301) passes one pair reference.
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
	Rva0022304A(const Rva0022304A &o);
private:
	AsciiString m_head;
	Rva0022300F m_item;
};

Rva0022304A::Rva0022304A(const Rva0022304A &o) : m_head(o.m_head), m_item(o.m_item)
{
}

// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva0023FD06@@UAE@XZ @0x0023FD06 48B
// Opaque dtor called by the rowed ??_G 0x0023FCEA (vtable 0x00BEDC94#0).
// Target facts: the body only destroys the AsciiString member at +0x08
// (inline dtor -> rowed StringBase<char>::releaseBuffer 0x00036410) under EH
// state 0 for the base subobject, then the inline base dtor resets to the
// one-slot base vtable 0x00BC6F20 (whose slot is the rowed ??_GRva0007DF07).
// No derived vptr store: retail's dtor is the implicit one. Identity unproven;
// address-derived name as pinned.
#include "ascii_string.h"

class Rva0007DF07
{
public:
	virtual ~Rva0007DF07() {}
};

class Rva0023FD06 : public Rva0007DF07
{
public:
	Rva0023FD06();

private:
	int m_04;
	AsciiString m_08;
};

// The implicit virtual dtor (no derived vptr store) is emitted with the vtable
// this out-of-line ctor needs.
// ?<Rva0023FD06::Rva0023FD06> absent-from-retail
Rva0023FD06::Rva0023FD06()
{
}

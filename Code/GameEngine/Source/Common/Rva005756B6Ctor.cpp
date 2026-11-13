extern unsigned g_Va00E0661C;

// cl: /DNDEBUG /MD
// ??0Rva005756B6@@QAE@H@Z retail 0x005756B6 49B
// Derived ctor of rowed base Rva005CBA04 (0x005CBA04): builds a 4B
// FixedStorage temp from global 0x00E0661C via rowed copy 0x002CF0F0,
// passes it by value to the base, stores the outer int arg at +8 and
// overwrites vtable with 0x0086E620. Evidence: call sequence matches base
// comment listing this as derived ctor with global 0x00E0661C; sole caller
// at 0x005757B9; neighbours share /O1. Honest Rva address name.
#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"
#include "../../Include/Common/Rva005CBA04.h"
class Rva005756B6 : public Rva005CBA04
{
public:
	Rva005756B6(int arg);
	// Empty: retail's vtable slot 0 (deleting dtor 0x005E5A66) calls 0x00576FCE,
	// one jump to the base dtor 0x005CB9F3.
	virtual ~Rva005756B6() {}
private:
	int m_08;
};
Rva005756B6::Rva005756B6(int arg)
	: Rva005CBA04(*reinterpret_cast<const BfmeFixedStorage002CF0F0 *>((unsigned int)&g_Va00E0661C))
	, m_08(arg)
{
}

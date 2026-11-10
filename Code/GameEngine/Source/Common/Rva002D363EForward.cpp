// cl: /O1 /DNDEBUG /MD
//
// ?rva002D363E@Rva002D363EOwner@@QAEXH@Z @0x002D363E 80B: dual-subobject
// forward with gated pair (thiscall, int arg, void). Forwards arg to the
// landed 0x0052A287 via +0x10+0x8c and to landed 0x0052854C via +0x10+0x90,
// then when landed hasOverrideWindow 0x002D35D6 on this is true forwards
// to pinned 0x00529FBE (+0x8c) and pinned 0x005288BD (+0x90). Honest
// address-derived names; sub-object identities unproven.

#include "../../Include/Common/RadarWindowOverrideSource.h"

// LINK: the three forwarded calls bind their rowed owners: 0x0052A287 Rva0052A287::rva0052A287(Obj0052A22C*),
// 0x00529FBE PalantirCommandInterface::rva00529FBE(), 0x0052854C Rva0052854C::rva0052854C(Rva0052854CArg*).
struct Obj0052A22C;
struct Rva0052854CArg;
struct Rva0052A287 { void setObject(Obj0052A22C *x); };
struct PalantirCommandInterface { void rva00529FBE(); };
struct Rva0052854C { void rva0052854C(Rva0052854CArg *x); };

struct Rva002D363E90
{
	void rva005288BD();
};

class Rva002D363EOwner
{
public:
	void rva002D363E(int x);
private:
	char m_pad00[0x10];
	void *m_p10;
};

// ?rva002D363E@Rva002D363EOwner@@QAEXH@Z
void Rva002D363EOwner::rva002D363E(int x)
{
	((Rva0052A287 *)((char *)m_p10 + 0x8C))->setObject((Obj0052A22C *)x);
	((Rva0052854C *)((char *)m_p10 + 0x90))->rva0052854C((Rva0052854CArg *)x);
	if (((RadarWindowOverrideSource *)this)->hasOverrideWindow()) {
		((PalantirCommandInterface *)((char *)m_p10 + 0x8C))->rva00529FBE();
		((Rva002D363E90 *)((char *)m_p10 + 0x90))->rva005288BD();
	}
}

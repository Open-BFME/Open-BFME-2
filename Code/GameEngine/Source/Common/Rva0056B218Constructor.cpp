// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B218@@QAE@PAVRva0056AC26Owner@@PAUParent0056B218@@1@Z, retail
// 0x0056B525..0x0056B599 (116 bytes, EH, ret 0xC). Constructor of the
// two-parent listener of Rva0056B218Dtor.cpp (vtables 0x00C6D40C, 0x00C6D3D0 at
// +8 and 0x00C6D3BC at +0x14): the rowed base Rva0056AC26 gets the owner, the
// listener at +0x14 is registered with the lists at +8 of both parents
// (rowed append 0x005A0B4C) and the second parent is kept at +0x1C beside
// the first at +0x18. Class and parent names address-derived.
class Rva0056AC26Owner;
struct Rva002BA8F1Listener;

#include "../../Include/Common/Rva005A0B4CList.h"

struct Parent0056B218
{
	char pad[8];
	Rva005A0B4CList holder;
};

#include "../../Include/Common/Rva0056AC26.h"

class Rva0056B218B2
{
public:
	Rva0056B218B2() {}
	virtual ~Rva0056B218B2() {}
};

class Rva0056B218 : public Rva0056AC26, public Rva0056B218B2
{
public:
	Rva0056B218(Rva0056AC26Owner *owner, Parent0056B218 *first, Parent0056B218 *second);
	virtual ~Rva0056B218();
private:
	Parent0056B218 *m_parent18;
	Parent0056B218 *m_parent1C;
	bool m_20;
};

Rva0056B218::Rva0056B218(Rva0056AC26Owner *owner, Parent0056B218 *first, Parent0056B218 *second)
	: Rva0056AC26(owner), m_parent18(first), m_parent1C(second), m_20(false)
{
	first->holder.append((Rva002BA8F1Listener *)static_cast<Rva0056B218B2 *>(this));
	second->holder.append((Rva002BA8F1Listener *)static_cast<Rva0056B218B2 *>(this));
}

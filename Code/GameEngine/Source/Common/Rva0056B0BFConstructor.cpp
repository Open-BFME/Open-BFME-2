// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B0BF@@QAE@PAVRva0056AC26Owner@@PAUParent0056B0BF@@1@Z, retail
// 0x0056B525..0x0056B599 (116 bytes, EH, ret 0xC). Constructor of the
// two-parent listener of Rva0056B0BFDtor.cpp (vtables 0x00C6D40C, 0x00C6D3D0 at
// +8 and 0x00C6D3BC at +0x14): the rowed base Rva0056AC26 gets the owner, the
// listener at +0x14 is registered with the lists at +8 of both parents
// (rowed append 0x005A0B4C) and the second parent is kept at +0x1C beside
// the first at +0x18. Class and parent names address-derived.
class Rva0056AC26Owner
{
public:
	char m_pad00[0x20];
	bool m_flag20;
};
struct Rva002BA8F1Listener;

#include "../../Include/Common/Rva005A0B4CList.h"

struct Parent0056B0BF
{
	char pad[8];
	Rva005A0B4CList holder;
};

#include "../../Include/Common/Rva0056AC26.h"

#include "../../Include/Common/LivingWorldBattleListener.h"

class Rva0056B0BF : public Rva0056AC26, public LivingWorldBattleListener
{
public:
	Rva0056B0BF(Rva0056AC26Owner *owner, Parent0056B0BF *parent);
	virtual ~Rva0056B0BF();
private:
	Parent0056B0BF *m_parent18;
	bool m_1C;
	bool m_1D;
	bool m_1E;
};

Rva0056B0BF::Rva0056B0BF(Rva0056AC26Owner *owner, Parent0056B0BF *parent)
	: Rva0056AC26(owner), m_parent18(parent)
{
	m_1C = false;
	m_1D = false;
	m_1E = false;
	owner->m_flag20 = true;
	m_parent18->holder.append((Rva002BA8F1Listener *)static_cast<LivingWorldBattleListener *>(this));
}

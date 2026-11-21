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

#include "../../Include/Common/LivingWorldBattleListener.h"

class Rva0056B218B2 : public LivingWorldBattleListener
{
public:
	Rva0056B218B2() {}
};

class Rva0056B218 : public Rva0056AC26, public Rva0056B218B2
{
public:
	Rva0056B218(Rva0056AC26Owner *owner, Parent0056B218 *first, Parent0056B218 *second);
	virtual ~Rva0056B218();
	// Rva0056AC26 slot 1 (retail table 0x00C6D3A8 / 0x00C6D40C slot 1): 0x00232E8F,
	// `mov al,[ecx+20h]; ret`, the flag at +0x20 (a body retail folds).
	virtual bool ac26Slot1();
	// LivingWorldBattleListener at +0x14 (retail table 0x00C6D3BC) slots 0 and 1.
	virtual void onArmyRemoved(void *army);
	virtual void slot1(int a, int b);
	// Rva0056AC26Base2 at +8 (retail table 0x00C6D3D0) slots 1 and 3.
	virtual bool slot1(Rva002B4BC9Arg *candidate);
	virtual bool slot3(int first, int second);
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

// ?ac26Slot1@Rva0056B218@@UAE_NXZ: slot 1 of retail table 0x00C6D40C is 0x00232E8F.
bool Rva0056B218::ac26Slot1()
{
	return m_20;
}

// Slot 1 of retail table 0x00C6D3BC: both parents seen in swapped order set +0x20.
void Rva0056B218::slot1(int a, int b)
{
	if (m_parent18 == (Parent0056B218 *)b && m_parent1C == (Parent0056B218 *)a)
		m_20 = true;
}

// Slot 1 of retail table 0x00C6D3D0: whether the candidate is the first parent.
bool Rva0056B218::slot1(Rva002B4BC9Arg *candidate)
{
	return m_parent18 == reinterpret_cast<Parent0056B218 *>(candidate);
}

// Slot 3 of retail table 0x00C6D3D0: whether the pair is the two parents.
bool Rva0056B218::slot3(int first, int second)
{
	return m_parent18 == (Parent0056B218 *)first && m_parent1C == (Parent0056B218 *)second;
}

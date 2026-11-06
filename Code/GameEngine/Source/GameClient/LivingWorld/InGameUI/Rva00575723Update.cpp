// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?rva00575723@Rva00575723@@QAEXXZ, retail 0x00575723..0x005757A5 (130 bytes,
// RET 0): the per-frame update of the object Rva00575D45 holds at +0x8; the
// owner's vtable 0x00C6E664 slot 1 (0x00575D80, MemberBaseDtorsB01.cpp)
// forwards to it. Target evidence: it updates the owner (+0x18, rowed
// 0x0057539C), the manual phase ender at +0x30
// (StrategicInGameUI::ManualPhaseEnder::Update) and the +0x40 notifier (rowed
// 0x005CD708); runs and clears a pending action held at +0x2C (slot 1, rowed
// holder clear 0x000AD6F4); when TheLivingWorldLogic's phase (rowed
// 0x002B2B66) differs from the one kept at +0x20 it clears the +0x28 action,
// resets the +0x0C checklist (rowed 0x005CD010) and keeps the new phase;
// then runs the +0x28 action, or failing that hands 0 to the owner's
// +0x04 field object (rowed getter 0x00574AAC, rowed 0x005CB84A); and
// finally tail-calls the checklist's rowed 0x005CCEB6. WorldBuilder twin
// 0x014D34F0 is unnamed. Names are address-derived.

class Rva00574AACAddDwordField
{
public:
	int get() const;
};

class Rva00575383
{
public:
	void rva0057539C();
	char m_pad00[0x04];
	Rva00574AACAddDwordField *m_04;		// +0x04
};

#include "../../../../Include/GameLogic/ManualPhaseEnder.h"
namespace StrategicInGameUI
{
}

class Rva005CD708
{
public:
	void rva005CD708();
};

class Rva000AD6F4Action
{
public:
	virtual void slot0();
	virtual void run();				// slot 1
};

#include "../../../../Include/Common/Rva000AD6F4.h"
// The two holders own Rva000AD6F4Action objects.
__forceinline Rva000AD6F4Action *heldAction(const Rva000AD6F4 &holder) { return static_cast<Rva000AD6F4Action *>(holder.m_ptr); }

class Rva002B2B66
{
public:
	int rva002B2B66();
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005CD010
{
public:
	void rva005CD010();
};
class Rva005CCEB6
{
public:
	void rva005CCEB6();
};
class Rva005CB84A
{
public:
	void rva005CB84A(int value);
};

class Rva00575723
{
public:
	void rva00575723();
private:
	char m_pad00[0x0C];
	Rva005CCEB6 m_checklist;			// +0x0C
	char m_pad0D[0x18 - 0x0D];
	Rva00575383 *m_owner;				// +0x18
	char m_pad1C[0x20 - 0x1C];
	int m_phase;					// +0x20
	char m_pad24[0x28 - 0x24];
	Rva000AD6F4 m_action;				// +0x28
	Rva000AD6F4 m_pendingAction;			// +0x2C
	StrategicInGameUI::ManualPhaseEnder m_manualPhaseEnder;	// +0x30
	Rva005CD708 m_notifier;				// +0x40
};

void Rva00575723::rva00575723()
{
	m_owner->rva0057539C();
	m_manualPhaseEnder.Update();
	m_notifier.rva005CD708();
	if (heldAction(m_pendingAction))
	{
		heldAction(m_pendingAction)->run();
		m_pendingAction.clear();
	}
	int phase = reinterpret_cast<Rva002B2B66 *>(TheLivingWorldLogic)->rva002B2B66();
	if (phase != m_phase)
	{
		m_action.clear();
		reinterpret_cast<Rva005CD010 &>(m_checklist).rva005CD010();
		m_phase = phase;
	}
	if (heldAction(m_action))
		heldAction(m_action)->run();
	else
		reinterpret_cast<Rva005CB84A *>(m_owner->m_04->get())->rva005CB84A(0);
	m_checklist.rva005CCEB6();
}

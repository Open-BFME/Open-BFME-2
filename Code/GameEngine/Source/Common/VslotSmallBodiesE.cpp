// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch E. As in VslotSmallBodiesA-D, each class and method
// is address-derived and models only what its body touches; the comment above
// each gives the .rdata slot address(es) that reference it. Meanings are not
// recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// slots at VA 0x00C433A0, 0x00C4401C, 0x00C45D1C, 0x00C46054, 0x00C46F68,
// 0x00C47314, 0x00C47868 and 0x00C48900: the embedded +0xA0 block while the
// +0xAC byte is set, else NULL.
struct Rva00462579Block
{
	char m_pad00[0x0C];
};
class Rva00462579
{
public:
	Rva00462579Block *rva00462579();
private:
	char m_pad00[0xA0];
	Rva00462579Block m_A0;
	Bool m_AC;
};
Rva00462579Block *Rva00462579::rva00462579()
{
	if (m_AC)
		return &m_A0;
	return 0;
}



typedef float Real;





enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;

class ModuleData;

class Object;

class DamageInfo;

class Xfer;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
    virtual void *vslot10() { return 0; }
    virtual void *vslot11() { return 0; }
};

// Native Update interface at +0x10: update, disabled mask, wake frame.
#pragma function(memcpy)
#include <string.h>
template <int NUM_BITS> class BitFlags
{
public:
    __forceinline BitFlags(const BitFlags &other) { memcpy(m_bits, other.m_bits, sizeof(m_bits)); }
private:
    UnsignedInt m_bits[(NUM_BITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;
extern DisabledMaskType DISABLEDMASK_ALL;

class UpdateModuleInterface
{
public:
    virtual UpdateSleepTime update() = 0;
    virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;
};

enum SleepyUpdatePhase;

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay);
protected:
    virtual SleepyUpdatePhase getUpdatePhase() const;
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual Bool isAlreadyUpgraded() const;
	void giveSelfUpgrade();
protected:
	Bool m_upgradeExecuted; // +0x04
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

// The +0x2C damage record; its ctor is rowed at 0x00263895.
class Rva00263895Member
{
public:
	Rva00263895Member();
private:
	unsigned char m_data[0x7C];
};

class FireWeaponWhenDeadBehaviorModuleData
{
public:
	unsigned char m_pad00[0x118];
	Bool m_initiallyActive; // +0x118
	UnsignedInt m_count; // +0x11C
};

class FireWeaponWhenDeadBehavior : public UpdateModule, public UpgradeMux, public DieModuleInterface
{
public:
	FireWeaponWhenDeadBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponWhenDeadBehavior();
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const { return DISABLEDMASK_ALL; }
	virtual void onDie(const DamageInfo *damageInfo);
	// Primary vftable 0x008497B4 slots 1-3, as Rva00589079Derived.cpp declares them.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
protected:
	virtual void xfer(Xfer *xfer);
public:
	// Primary vtable slot 4, already rowed at 0x00482E51.
	virtual NameKeyType getModuleNameKey() const;
private:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const { return (const FireWeaponWhenDeadBehaviorModuleData *)m_moduleData; }

	Rva00263895Member m_damageInfo; // +0x2C
	UnsignedInt m_count; // +0xA8
};

// Native 0x00482BB9, slot zero of the +0x10 Update interface.
UpdateSleepTime FireWeaponWhenDeadBehavior::update()
{
    Int *count = (Int *)&m_count;
    if (*count > 0 && --*count == 0)
        onDie((const DamageInfo *)&m_damageInfo);
    return UPDATE_SLEEP_NONE;
}

// slot at VA 0x00C49AFC: both +0x24 and +0x28 become TheGameLogic's frame
// plus the +0x04 object's +0x08 delay.
struct Rva00483BA3Data
{
	char m_pad00[0x08];
	UnsignedInt m_delay;
};
class Rva00483BA3
{
public:
	void rva00483BA3();
private:
	char m_pad00[0x04];
	const Rva00483BA3Data *m_moduleData;
	char m_pad08[0x24 - 0x08];
	UnsignedInt m_24;
	UnsignedInt m_28;
};
void Rva00483BA3::rva00483BA3()
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_24 = m_moduleData->m_delay + now;
	m_28 = m_24;
}

// slot at VA 0x00C4B4C4 (a state's onExit, its status unused): the owner's
// AI interface (+0x258 of the machine owner) passes its vslot 93 result's
// vslot 24 a turn when both exist.
class Rva004885B8Target
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual float vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual Bool vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14();
	virtual void vslot15(); virtual void vslot16(); virtual void vslot17();
	virtual void vslot18(); virtual void vslot19(); virtual void vslot20();
	virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24();
};
template <int N> class Rva004885B8Slots : public Rva004885B8Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva004885B8Slots<0>
{
};
class Rva004885B8AI : public Rva004885B8Slots<93>
{
public:
	virtual Rva004885B8Target *vslot93();
	virtual void vslot94();
	virtual void vslot95();
	virtual void vslot96();
	virtual void vslot97();
	virtual void vslot98();
	virtual void vslot99();
	virtual Rva004885B8Target *vslot100();
	virtual void vslot101();
	virtual void vslot102();
	virtual void vslot103();
	virtual void vslot104();
	virtual void vslot105();
	virtual void vslot106();
	virtual void vslot107();
	virtual void vslot108();
	virtual void vslot109();
	virtual Bool vslot110();
};
struct Rva004885B8Owner
{
	char m_pad00[0x258];
	Rva004885B8AI *m_ai;
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;
};
struct Rva004885B8Machine
{
	char m_pad00[0x14];
	Rva004885B8Owner *m_owner;
};
class Rva004885B8
{
public:
	void onExit(Int status);
	Int rva004A6C30();
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
};
void Rva004885B8::onExit(Int status)
{
	Rva004885B8AI *ai = m_machine->m_owner->m_ai;
	if (ai)
	{
		Rva004885B8Target *target = ai->vslot93();
		if (target)
			target->vslot24();
	}
}

// slot at VA 0x00C53270 (a state's onEnter): with an owner and its AI
// interface, runs vslot 0 of the AI's vslot 100 result when there is one;
// answers 0 (continue). Same owner/AI path as 0x004885B8.
Int Rva004885B8::rva004A6C30()
{
	Rva004885B8Owner *owner = m_machine->m_owner;
	if (owner)
	{
		Rva004885B8AI *ai = owner->m_ai;
		if (ai)
		{
			Rva004885B8Target *target = ai->vslot100();
			if (target)
				target->vslot00();
		}
	}
	return 0;
}

// slot at VA 0x00C4B578 (a state's onEnter): stamps TheGameLogic's frame at
// +0x20, clears the +0x28 byte and answers 0 (continue).
class Rva0048872D
{
public:
	Int onEnter();
private:
	char m_pad00[0x20];
	UnsignedInt m_20;
	char m_pad24[0x28 - 0x24];
	Bool m_28;
};
Int Rva0048872D::onEnter()
{
	m_20 = TheGameLogic->getFrame();
	m_28 = false;
	return 0;
}

// slot at VA 0x00C4B4B0 slot 4 (offset 0x10) of Rva00488545 (vtable 0x0084B4B0,
// class of ??0Rva00488545@@QAE@PAVStateMachine@@H@Z from AIStateHashCtorsMisc):
// runs AI vslot93, answers -2 when null, else stamps TheGameLogic frame at
// +0x24 and runs target vslot18(0) when +0x20 is 0 or 1, answers 0.
// Evidence: +0x18/+0x14/+0x258 AI path and vslot93/frame+0x40 same as 0x004885B8,
// m_20 at +0x20 and m_24 at +0x24 match Rva00488545 layout, ret void with -2/0.
class Rva00488573Target : public Rva004885B8Slots<18>
{
public:
	virtual void vslot18(Int arg);
};
class Rva00488545
{
public:
	Int onEnter();
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
	char m_pad1C[0x20 - 0x1C];
	Int m_20;
	UnsignedInt m_24;
};

Int Rva00488545::onEnter()
{
	Rva004885B8AI *ai = m_machine->m_owner->m_ai;
	Rva00488573Target *target = (Rva00488573Target *)ai->vslot93();
	if (!target)
		return -2;
	m_24 = TheGameLogic->getFrame();
	Int status = m_20;
	if (status == 0 || status == 1)
		target->vslot18(0);
	return 0;
}

// slot at VA 0x00C4B568 slot 5 (offset 0x14) of Rva004886C7 (vtable 0x0084B568,
// class of ??0Rva004886C7@@QAE@PAVStateMachine@@@Z from AIStateHashCtorsMisc):
// when +0x28 is set runs InGameUI vslot106 with owner and +0x24 then stamps
// +0x24 to -1 and clears +0x28. Evidence: ret 4 with unused arg, TheInGameUI
// at VA 0x009FEDF0, or -1 and bool clear, same machine/owner path as above.
class InGameUI : public Rva004885B8Slots<105>
{
public:
	virtual void vslot105(Rva004885B8Owner *owner);
	virtual void vslot106(Rva004885B8Owner *owner, Int val);
};
extern InGameUI *TheInGameUI;
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
#include "../../Include/Common/BfmeXfer.h"
class Rva004886C7
{
public:
	void onExit(Int status);
	void xfer(Xfer *xfer);
	Int update();
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
	char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_20;
	Int m_24;
	Bool m_28;
};

void Rva004886C7::onExit(Int status)
{
	if (!m_28)
		return;
	TheInGameUI->vslot106(m_machine->m_owner, m_24);
	m_24 |= -1;
	m_28 = false;
}

// slot at VA 0x00C4B568 slot 3 (offset 0x0C) of Rva004886C7 (vtable 0x0084B568,
// class of ??0Rva004886C7@@QAE@PAVStateMachine@@@Z from AIStateHashCtorsMisc):
// xfer: Version1 via rowed 0x000053EE then +0x20 as uint via Xfer slot 0x78,
// +0x24 as int via slot 0x7c and +0x28 as bool via slot 0x90. No base call
// and no IsLightCRC gate. Evidence: ret 4 with Xfer arg, Version1 first,
// three virtual xfers in offset order; m_20/m_24/m_28 match the rowed ctor
// layout (+0x20/+0x24/+0x28), slot order per the reversed-overload Xfer
// vtable (Version 0x28, AsciiString 0x6C, uint 0x78, bool 0x90 precedents).
void Rva004886C7::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_28;
}

class Player
{
public:
	char m_pad00[0x54];
	Int m_54;
};
class Object
{
public:
	Player *getControllingPlayer() const;
};

// slot at VA 0x00C4B568 slot 6 (offset 0x18) of Rva004886C7 (vtable 0x0084B568,
// class of ??0Rva004886C7@@QAE@PAVStateMachine@@@Z from AIStateHashCtorsMisc):
// answers -2 without an AI or its vslot93 target; when AI vslot110 holds and
// +0x28 is clear with owner +0x438 bit0 clear, stamps the controlling
// player's +0x54 at +0x24 and runs InGameUI vslot105 then sets +0x28; when
// +0x28 holds and (vslot110 fails or the bit is set) runs InGameUI vslot106,
// stamps +0x24 to -1 and clears +0x28; stamps TheGameLogic's frame at +0x20
// while vslot110 fails; resets +0x20 once the frame delta as float passes
// the target's vslot02 while its vslot08 fails; answers 0. Evidence: ret
// with EBP frame, AI vslot93 (0x174) plus vslot110 (0x1b8, AIUpdateInterface
// isIdle per AIGroupIsIdle) plus target float slot 2 (0x08) plus bool slot 8
// (0x20), rowed getControllingPlayer 0x0028AFA9, TheInGameUI slots 105/106,
// TheGameLogic frame +0x40, unsigned fild/fadd float conversion, owner
// +0x258 AI plus +0x438 EFFECTIVELY_DEAD bit like Object. The owner is
// treated as Object only for the rowed call.
Int Rva004886C7::update()
{
	Rva004885B8Owner *owner = m_machine->m_owner;
	Rva004885B8AI *ai = owner->m_ai;
	if (!ai)
		return -2;
	Rva004885B8Target *target = ai->vslot93();
	if (!target)
		return -2;
	if (ai->vslot110())
	{
		if (!m_28 && !(owner->m_privateStatus & 1))
		{
			m_24 = ((Object *)owner)->getControllingPlayer()->m_54;
			TheInGameUI->vslot105(m_machine->m_owner);
			m_28 = true;
		}
	}
	if (m_28 && (!ai->vslot110() || (owner->m_privateStatus & 1)))
	{
		TheInGameUI->vslot106(m_machine->m_owner, m_24);
		m_24 |= -1;
		m_28 = false;
	}
	if (!ai->vslot110())
		m_20 = TheGameLogic->getFrame();
	UnsignedInt elapsed = TheGameLogic->getFrame() - m_20;
	if ((float)elapsed > target->vslot02() && !target->vslot08())
		m_20 = TheGameLogic->getFrame();
	return 0;
}

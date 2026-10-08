#pragma once
// BFME2 copy of reference/open-bfme-1/Code/GameEngine/Source/Common/System/
// subsystem_interface.h; only SubsystemSlot differs.
#include <vector>
#include <utility>
#include "ascii_string.h"

class INI;
class Xfer;

// Retail's base vtable (0x00BD77A0, installed by the ctor at 0x001B4E63 and
// the dtor at 0x001B4E74) has fourteen slots, read from retail:
//    0 ~SubsystemInterface (??_G 0x001B4F51)   1 init (pure)
//    2 loadIniFilesFromLegend (0x001B5384)       3 postProcessLoad (empty)
//    4 bool(int) returning false (0x005CB9FF)    5 bool() returning false (0x0047A699)
//    6 int() returning 0 (0x000D43D0)            7 void(int), empty (0x0047A69C)
//    8 void(), empty (0x000B3FD0)                9 reset (pure)   10 update (pure)
//   11 bool(int) returning false (0x005CB9FF)   12 void(), empty   13 void(int), empty
// Names: slot 3 is postProcessLoad because WeaponStore (table 0x00C02114) and
// W3DDisplayStringManager (0x00BC7E2C) put their rowed postProcessLoad bodies
// there; 9 and 10 are reset and update because ScriptEngine (0x00BE3D70) puts
// its reset (0x00209ABE) and update there. Slots 4-8 and 11-13 have no name
// evidence: vslotNN are ours, their default bodies are retail's (structural).
// Slots 1 and 2 are the load-bearing ones: SubsystemInterfaceList::initSubsystem
// dispatches through [vptr+4] and [vptr+8].
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface {
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	// BFME-only: look this subsystem up in TheSubsystemLegend by name and load the
	// INI files and directories its "LoadSubsystem" block lists. Returns TRUE if
	// the legend supplied anything, in which case initSubsystem skips the
	// hard-coded paths it was passed.
	virtual Bool loadIniFilesFromLegend();
	virtual void postProcessLoad() {}
	virtual bool vslot04(int) { return false; }
	virtual bool vslot05() { return false; }
	virtual int vslot06() { return 0; }
	virtual void vslot07(int) {}
	virtual void vslot08() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual bool vslot11(int) { return false; }
	virtual void vslot12() {}
	virtual void vslot13(int) {}
	inline void UPDATE(void) { update(); }
	void setName(AsciiString name) { m_name = name; }
	AsciiString getName(void);
protected:
	// BFME2 layout: the base ctor (0x001B4E63) clears a byte at +0x04 and the
	// dtor (0x001B4E74) destroys m_name at +0x08; the byte's role is unknown.
	Bool m_flag;		// +0x04
	AsciiString m_name;	// +0x08
};

// The registry GameEngine::init drives; retail keeps it at 0x0134C6C8.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterfaceList
{
public:
	SubsystemInterfaceList();
	~SubsystemInterfaceList();

	void initSubsystem(SubsystemInterface *sys, void *slot, const char *path1,
					   const char *path2, const char *dirpath, Xfer *pXfer, AsciiString name);

	// Layout read off the two functions that touch it: the vector occupies +0x00
	// (start/finish/end at +0/+4/+8, eight-byte elements, so it holds pairs) and
	// the Xfer the legend loader passes to INI::load sits at +0x0c.
	std::vector<std::pair<SubsystemInterface *, void *> >	m_subsystems;	// +0x00
	Xfer													*m_xfer;		// +0x0c
};

extern SubsystemInterfaceList *TheSubsystemList;

// The eight-byte polymorphic holder the initSubsystem template news for every
// subsystem: a vptr (retail 0x01075D8C) plus the address of the global the
// subsystem was stored into. Handed to SubsystemInterfaceList::initSubsystem as
// its second argument and parked alongside the subsystem in m_subsystems, which
// is why that vector holds pairs.
// One instantiation per subsystem, not one shared class: each initSubsystem<T>
// stores a DIFFERENT vtable pointer here (0x1075D8C, 0x1075DA8, 0x1075DB4,
// 0x1075DCC, 0x1075DE8, 0x1075DEC for the six landed so far), which is only
// possible if the slot is parameterised on the same T. Modelling it as a plain
// class makes every instantiation claim one vtable symbol and trips the DIR32
// consistency check.
// BFME2: every slot shares one base (vtable 0x00BE714C, a single deleting-dtor
// slot at 0x00225A5C). Each ~SubsystemSlot<T> reinstalls that base vtable as its
// last store, so the base's dtor is non-trivial and inlined. The base's name is
// ours: nothing in retail names it.
class SubsystemSlotBase
{
public:
	virtual ~SubsystemSlotBase() {}
};

// The slot owns its subsystem: its dtor deletes the object through the global
// it was stored in and clears that global (retail 0x002282B7 for one T).
template<class SUBSYSTEM>
class SubsystemSlot : public SubsystemSlotBase
{
public:
	SubsystemSlot(SUBSYSTEM **slot) : m_slot(slot) {}
	virtual ~SubsystemSlot()
	{
		::delete *m_slot;
		*m_slot = 0;
	}
	SUBSYSTEM **m_slot;
};

// GameEngine::init calls this once per subsystem; ZH has the same helper.
template<class SUBSYSTEM>
void initSubsystem(SUBSYSTEM *&sysref, AsciiString name, SUBSYSTEM *sys, Xfer *pXfer,
				   const char *path1 = 0, const char *path2 = 0, const char *dirpath = 0)
{
	sysref = sys;
	TheSubsystemList->initSubsystem(sys, new SubsystemSlot<SUBSYSTEM>(&sysref), path1, path2, dirpath, pXfer, name);
}

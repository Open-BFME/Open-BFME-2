// FILE: VictorySystem.h //////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 VictorySystem (the TheVictorySystem subsystem).
//
// Target facts (code addresses are RVAs, tables are VAs):
//  - ??0VictorySystem (0x004054E1) calls ??0SubsystemInterface 0x001B4E63 on +0,
//    stores Snapshot's table 0x00BBB554 at +0x0C (Snapshot's inline constructor),
//    then its own tables 0x00C388D4 at +0 and 0x00C388C4 at +0x0C. ??1VictorySystem
//    (0x004053C2) stores the same own pair, destroys the +0x120 vector (0x00405350),
//    restores 0x00BBB554 at +0x0C and calls ~SubsystemInterface 0x001B4E74, which
//    stores 0x00BD77A0. The first stores are the bases' lifetimes, the second pair
//    is this class's: VictorySystem : SubsystemInterface (+0), Snapshot (+0x0C).
//  - GameEngine::init pushes 0x140 at 0x0022F828, calls ??2@YAPAXI@Z 0x0002FDA0 and
//    the constructor at 0x0022F840: sizeof 0x140, global operator new.
//  - Primary table 0x00C388D4 has 15 slots: SubsystemInterface's fourteen (0x00BD77A0)
//    with overrides 0 ??_G 0x0040559F, 1 init 0x004055F2, 9 reset 0x00404B6C and
//    10 update 0x00405315 (slots 2-8 and 11-13 equal the base's), plus slot 14,
//    newMap 0x00404DE5 (WorldBuilder twin 0x01075B20), which GameLogic::rva00248278
//    calls through [vptr+0x38] on TheVictorySystem (VA 0x00E02F3C) at 0x00248428.
//  - Snapshot table 0x00C388C4: 0 ??_E thunk 0x00405417 (this-0x0C), 1 the empty
//    shared ret 0x000B3FD0 (load post-process), 2 GetSnapshotName 0x00405411
//    (returns "VictorySystem"), 3 DoXfer 0x004056ED.
//  - Fields: the constructor stores floats +0x10/+0x18/+0x1C/+0x20 and 1.0f at +0x24,
//    a dword at +0x14, twenty dwords at +0x28, calls Rva00404781::rva0040475C on
//    +0x78 (0xA8 bytes), builds the +0x120 vector header through 0x00211E58, stores
//    +0x138, byte +0x134, +0x13C and the two grid pointers +0x12C/+0x130.
//    newMap stores ??0CellGrid (0x0056C266) objects into +0x12C/+0x130 and the
//    player count into +0x14; init 0x004055F2 pushes 24-byte faction records
//    (AsciiString and five floats, 0x00404BC5) into +0x120 through 0x004055BB;
//    rva00404B03 (0x00404B03) destroys the grids through 0x0056C065, 0x0056C3E5
//    and ??3@YAXPAX@Z, and update 0x00405315 tests byte +0x134.
// No original member name is established; members are named by offset.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_VICTORYSYSTEM_H
#define BFME2_VICTORYSYSTEM_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

#include <vector>
#include "Rva00404781.h"

class CellGrid;
class Xfer;
struct BfmeStringRecord00404BF3;

class VictorySystem : public SubsystemInterface, public Snapshot
{
public:
	VictorySystem();							// 0x004054E1
	virtual ~VictorySystem();					// 0x004053C2 (slot 0: ??_G 0x0040559F)

	virtual void init();						// 0x004055F2, slot 1
	virtual void reset();						// 0x00404B6C, slot 9
	virtual void update();						// 0x00405315, slot 10

	// Snapshot slots, spelled the way the unit selected Snapshot.h's.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess() {}
#else
	virtual void loadPostProcess() {}
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName() { return "VictorySystem"; }
#else
	virtual const char *GetSnapshotName() const { return "VictorySystem"; }	// 0x00405411
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void DoXfer(Xfer *xfer);			// 0x004056ED, Snapshot slot 3
#else
	virtual void xfer(Xfer *xfer);
#endif

	virtual void newMap();						// 0x00404DE5, slot 14

	void rva00404B03();							// 0x00404B03, reset's body

	float m_10;
	unsigned int m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	int m_28[20];
	Rva00404781 m_78;
	_STL::vector<BfmeStringRecord00404BF3> m_120;
	CellGrid *m_12C[2];
	bool m_134;
	unsigned int m_138;
	unsigned int m_13C;
};

typedef char VictorySystemSize[(sizeof(VictorySystem) == 0x140) ? 1 : -1];

#endif // BFME2_VICTORYSYSTEM_H

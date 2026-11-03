// FILE: ShroudManagerClass.h /////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ShroudManager, the shroud subsystem behind TheShroudManager.
//
// Target facts (code addresses are RVAs, tables and globals VAs):
//  - GameLogic::init allocates 0x14 bytes through operator new 0x0002FDA0 at 0x00243F52,
//    calls the constructor 0x007398D0 at 0x00243F6A and stores the object in
//    TheShroudManager 0x00DFE74C at 0x00243F73: sizeof 0x14.
//  - Constructor 0x007398D0 calls ??0SubsystemInterface 0x001B4E63 with this+0, stores
//    Snapshot's table 0x00BBB554 at +0x0C, then its own primary table 0x00CF1250 at +0 and
//    secondary table 0x00CF1240 at +0x0C. It allocates 0x70 bytes, constructs them with
//    ??0ShroudManagerImpl 0x0073E310 and stores the pointer at +0x10, its last write.
//    Bases: SubsystemInterface at +0 (12 bytes), Snapshot at +0x0C.
//  - Destructor 0x00739980 (called by the deleting destructor 0x00739E40, slot 0) restores
//    0x00CF1250/0x00CF1240, runs ??1ShroudManagerImpl 0x0073E3F0 and operator delete 0x0002FD60
//    on +0x10, restores 0x00BBB554 and calls ??1SubsystemInterface 0x001B4E74. The constructor,
//    destructor and deleting destructor rows still carry the placeholder class Open2Store8F75D0.
//  - Primary table 0x00CF1250 has fourteen slots ending at the class-name string 0x00CF1288
//    "ShroudManager". Slots 2-8 and 11-13 equal SubsystemInterface's table 0x00BD77A0; the
//    class overrides its three __purecall slots: 1 init 0x00739700 (`mov ecx,[ecx+0x10]` then
//    jump to 0x0073DFD0 on the implementation), 9 reset 0x006158B0 (calls slot 1) and
//    10 update 0x00739710 (jump to ShroudManagerImpl::drainPending 0x0073D7D0 on +0x10).
//  - Secondary table 0x00CF1240: deleting-destructor thunk 0x00739960 (this-0x0C, jump to
//    0x00739E40), loadPostProcess 0x0069E440 (`ret`), GetSnapshotName 0x00739970 (returns
//    0x00CF1288 "ShroudManager") and xfer 0x00739A00 (versions the Xfer, then passes it to
//    0x0073D8B0 on the pointer at +0x10).
//  - 0x00739820 (row ?rva00739820@ShroudManager@@) is `mov ecx,[ecx+0x10]; jmp 0x0073E5A0`
//    (ShroudManagerImpl::GetNearestGroupWithValue); ScriptActions calls it at 0x003C0FCD.
//  - ShroudManager::Data is a nested class: the rows at 0x00739FE0, 0x0073A0C0, 0x0073AAE0
//    and 0x0073AD90 mangle `@Data@ShroudManager@@`. Its layout is not part of this header.
// Slot names come from the registered parents. The +0x10 member has no name evidence.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_SHROUDMANAGERCLASS_H
#define BFME2_SHROUDMANAGERCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Xfer;
class ShroudManagerImpl;
struct Coord3D;

class ShroudManager : public SubsystemInterface, public Snapshot
{
public:
	class Data;

	ShroudManager();
	virtual ~ShroudManager();
	virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
#endif
	virtual void reset();
	virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
	virtual bool vslot11(int);
	virtual void vslot12();
	virtual void vslot13(int);
#endif

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);
#else
	virtual void DoXfer(Xfer *xfer);
#endif
#else
	virtual void xfer(Xfer *xfer);
#endif

	// 0x00739820: forwards to the implementation at +0x10.
	void rva00739820(const Coord3D *sourceLocation, int playerMask, int unknown,
		int valueRequired, Coord3D *outLocation);

	ShroudManagerImpl *m_10; // +0x10, constructed by 0x0073E310
};

#endif // BFME2_SHROUDMANAGERCLASS_H

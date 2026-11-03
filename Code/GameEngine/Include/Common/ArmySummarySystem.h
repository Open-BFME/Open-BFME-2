// FILE: ArmySummarySystem.h //////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ArmySummarySystem, the Snapshot embedded at GameLogic+0x184.
//
// Target facts (code addresses are RVAs, tables and literals are VAs):
//  - GameLogic's constructor 0x002470AE calls 0x0040E039 on this+0x184 (0x002472C1..0x002472E9)
//    and its destructor 0x00243BA0 calls 0x0040DB52 on this+0x184 (0x00243DA2..0x00243DAC).
//    Both are rowed under the address name Rva0040DB52. The GameLogic+0x184 forwarders
//    0x0023D028..0x0023D0C2 tail-jump to the rowed ArmySummarySystem members below.
//  - The constructor stores 0x00C394CC at +0 (0x0040E04B). The destructor stores 0x00C394CC
//    (0x0040DB63), frees the +0x20 and +0x14 storage, then restores Snapshot's 0x00BBB554
//    (0x0040DB93): the inlined Snapshot destructor. 0x00C394CC is this class's own table and
//    Snapshot is its only base. Retail calls the constructor and destructor out of line.
//  - 0x00C394CC holds four code pointers: deleting destructor 0x0040E09B (calls 0x0040DB52),
//    loadPostProcess 0x000B3FD0 (empty), GetSnapshotName 0x0040DBA3 (const; returns the literal
//    "ArmySummarySystem" at 0x00C394DC, the word after the table) and xfer 0x0040E6F6.
//  - Constructor fields: floats +0x04/+0x08 zeroed by movss (0x0040E072, 0x0040E077), byte
//    +0x0C = 0, dword +0x10 = 0xFF000000; +0x14 and +0x20 are STLport vectors built by the empty
//    _Vector_base constructor 0x00211E58 and cleared by the 4-byte erases 0x00532803/0x0031BD55.
//  - xfer 0x0040E6F6 transfers its version, then +0x04 through Xfer's table entry +0x50
//    (operator==(Coord2D &) in BfmeXfer.h), +0x0C through +0x90 (bool), +0x10 through +0x7C (int),
//    +0x14 through 0x003F2394 and +0x20 through 0x0040E269, which passes each element to +0x7C.
//  - GameLogic::init 0x00243EE7 writes GameLogic+0x1B0 (0x00244288), so sizeof is 0x2C.
//  - GetArmyIDOfFirstWalkOnArmy 0x0040D3FF (WB twin 0x0108DEF0) reads the id list's start and
//    finish at +0x14/+0x18 and passes each element to 0x0040D008, which takes an int.
// The vectors are spelled as their three storage words so that units built without STLport
// can include this header. Zero Hour has no such class: field names are neutral offsets.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_ARMYSUMMARYSYSTEM_H
#define BFME2_ARMYSUMMARYSYSTEM_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

class AsciiString;
class Object;
class Rva003F468D;
class UnitRevivalEntry;
class Xfer;
struct Rva0040D2FDVec;
struct _Rva0040CA61Arg;

class ArmySummarySystem : public Snapshot
{
public:
	ArmySummarySystem();												// 0x0040E039
	virtual ~ArmySummarySystem();										// slot 0, 0x0040DB52

	void *rva0040D008(int id);											// 0x0040D008
	int rva0040D025(int id);											// 0x0040D025
	const AsciiString *rva0040D041(int id);								// 0x0040D041
	void rva0040D280(Object *obj, int value);							// 0x0040D280
	void rva0040D2C3();													// 0x0040D2C3
	void rva0040D2FD(int armyID, int delaySeconds, Rva0040D2FDVec *coordinates);	// 0x0040D2FD
	const AsciiString *GetArmyNameByID(int id);							// 0x0040D34C
	const AsciiString *GetArmyBannerByID(int id);						// 0x0040D366
	int rva0040D380(int id);											// 0x0040D380
	void CallArmyToEngageInBattleByID(int id);							// 0x0040D396
	float GetArmyEngageProgressByID(int id);							// 0x0040D3B6
	int rva0040D3D5(int id);											// 0x0040D3D5
	int GetArmyCurFramesToReinforceByID(int id);						// 0x0040D3E8
	int GetArmyIDOfFirstWalkOnArmy();									// 0x0040D3FF
	void rva0040D43F(Rva003F468D *battle);								// 0x0040D43F
	int ComputePlayerEarnedSpellPoints(_Rva0040CA61Arg *player);		// 0x0040CA61
	void AddDeadHeroEntry(UnitRevivalEntry *entry);						// 0x0040F10F
	void Save(Object *objects);											// 0x0040F19D
	void rva0040F87E();													// 0x0040F87E
	void CallArmyReinforcementIntoBattleByID(int id);					// 0x0040FAFE

protected:
	// Slots 1-3 follow the spelling profile the included Snapshot header selected.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();										// slot 1, 0x000B3FD0
#else
	virtual void loadPostProcess();										// slot 1, 0x000B3FD0
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;						// slot 2, 0x0040DBA3
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
	virtual void xfer(Xfer *xfer);										// slot 3, 0x0040E6F6
#endif

public:
	Coord2D m_04;
	bool m_0C;
	int m_10;
	int *m_14;		// id list start
	int *m_18;		// id list finish
	int *m_1C;		// id list end of storage
	int *m_20;		// second int list start
	int *m_24;		// second int list finish
	int *m_28;		// second int list end of storage
};

#endif // BFME2_ARMYSUMMARYSYSTEM_H

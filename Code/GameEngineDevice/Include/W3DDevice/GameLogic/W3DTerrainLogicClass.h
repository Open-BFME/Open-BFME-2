// FILE: W3DTerrainLogicClass.h ///////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 W3DTerrainLogic.
//
// Target facts (code addresses are RVAs, tables are VAs):
//  - ??0W3DTerrainLogic (0x00062A7E) calls ??0TerrainLogic 0x00283FAA on this+0 at 0x00062A81,
//    clears +0x18 at 0x00062A89, stores 0.0f at +0x191C (0x00062A8D) and 1.0f (0x00BBB8D8) at
//    +0x1920 (0x00062AB8), and stores the tables 0x00BC5890/+0, 0x00BC5858/+4, 0x00BC5848/+0x10
//    and 0x00BC5838/+0x14 at 0x00062A9D..0x00062AB1. The single base is TerrainLogic at +0.
//  - sizeof 0x1924: the factory pushes 0x1924 at 0x00041FDA, calls operator new at 0x00041FDF and
//    the constructor at 0x00041FF3. TerrainLogic ends at 0x191C, so the class adds two floats.
//  - ~W3DTerrainLogic (0x00062AF7) stores the same four tables and tail-jumps to ~TerrainLogic
//    0x0028418A at 0x00062B12; it is called out of line from ??_G 0x00062E8D. Secondary slot 0
//    is the thunk 0x00062E6A (sub ecx,4; jmp 0x00062E8D). The two listener tables equal
//    TerrainLogic's own, so the class overrides no listener slot.
//  - Primary table 0x00BC5890 has TerrainLogic's 51 slots (0x00BFB2C8). Overridden: 0=62E8D,
//    1=62E4A loadPostProcess, 2=62AF1 GetSnapshotName (returns "W3DTerrainLogic" 0x00BC595C),
//    3=62E2F xfer, 4=63153 loadMap, 5=62B75 newMap, 6=62C45 getGroundHeight, 7=62C95
//    getLayerHeight, 8=62EF8, 9=62F64, 10=62B9C, 11=62E4F, 12=62FFF, 15=62C0F isClearLineOfSight,
//    16=62C23, 20=62D94 isCliffCell, 21=62DB3, 22=62DD2, 23=62DF1, 24=62E10, 50=63082. Every
//    other slot (13, 14, 17-19, 25-49) holds the parent's entry, so no override is declared.
//  - Secondary table 0x00BC5858 has SubsystemInterface's 14 slots (0x00BFB28C). Overridden:
//    0=62E6A, 1=62B17 init, 9=62B44 reset, 10=62B97 update.
//  - init 0x00062B17 and reset 0x00062B44 run with this at the +4 subobject: their stores to
//    +0x18/+0x1C and +0x1918/+0x191C are the object's +0x1C/+0x20 and +0x191C/+0x1920, the last
//    two again 0.0f and 1.0f.
//  - Ledger rows name the overrides above where they carry this class's scope, and the
//    non-virtual members Rva0027D960 (0x0027D960), Rva0027DA58 (0x0027DA58) and rva0027DA6A
//    (0x0027DA6A). The constructor, destructor and every rowed member are declared out of line.
// Donor (Zero Hour W3DTerrainLogic.h) facts: the override names and m_mapMinZ/m_mapMaxZ, whose
// initialisers m_mapMinZ(0), m_mapMaxZ(1) are the values retail stores at +0x191C/+0x1920.
// The overrides of slots 8-12, 16, 21-24 and 50 take the parent's spellings, which they must
// match; their bodies are rowed under other names.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_W3DTERRAINLOGICCLASS_H
#define BFME2_W3DTERRAINLOGICCLASS_H

#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

//-------------------------------------------------------------------------------------------------
class W3DTerrainLogic : public TerrainLogic
{
public:
	W3DTerrainLogic();
	virtual ~W3DTerrainLogic();

	virtual void init();
	virtual void reset();
	virtual void update();

	virtual bool loadMap(const AsciiString &, ChunkInputStream *, bool, bool);
	virtual void newMap(bool);
	virtual float getGroundHeight(float, float, Coord3D * = 0) const;
	virtual float getLayerHeight(float, float, PathfindLayerEnum, Coord3D * = 0, bool = true) const;
	virtual void getExtent(Region3D *) const;
	virtual void slot09(Region3D *) const;
	virtual void getExtentIncludingBorder(Region3D *) const;
	virtual float slot11();
	virtual void getMaximumPathfindExtent(Region3D *) const;
	virtual bool isClearLineOfSight(const Coord3D &, const Coord3D &) const;
	virtual float slot16(const Coord3D &, const Coord3D &) const;
	virtual bool isCliffCell(float, float) const;
	virtual unsigned char slot21(float, float) const;
	virtual unsigned char slot22(float, float) const;
	virtual bool slot23(float, float) const;
	virtual unsigned char slot24(float, float) const;
	virtual bool slot50(const Coord3D *) const;

	void Rva0027D960(void *, float *);
	void Rva0027DA58();
	bool rva0027DA6A(const float *, float *);

protected:
	virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
	virtual const char *GetSnapshotName() const;
#else
	virtual void crc(Xfer *xfer);
#endif
	virtual void xfer(Xfer *);

	float m_mapMinZ;		// +0x191C
	float m_mapMaxZ;		// +0x1920
};

#endif // BFME2_W3DTERRAINLOGICCLASS_H

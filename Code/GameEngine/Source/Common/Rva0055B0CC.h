#pragma once
// Rva0055B0CC: the 0x2C-byte polymorphic base Team (and the AI buildables)
// derive from. Its ctor 0x0055B048 and dtor 0x0055B0CC sit in AIBuildable.cpp
// and two of its slots carry AIBuildable rows (addNeed, registerWithBuilder),
// so WorldBuilder's AIBuildable is the likely original name; the ledger still
// spells it Rva0055B0CC and this header keeps that spelling.
//
// Target facts, read off game.dat:
//  - The ctor 0x0055B048 installs table 0x0086B900, 17 slots:
//     0 ??_G 0x0055B166           1 0x0055AFA3 (void())
//     2 0x0055B0B9 (float() const) 3 0x0055B146 (void(int), AIBuildable::addNeed)
//     4 0x0047A699 (bool() const, returns false)
//     5 0x0055B228 rva0055B228    6 0x0055AD91 (void(void *, bool), registerWithBuilder)
//     7 0x005F69CE (void(int))    8 0x003A36D3, 9 0x003A36F7, 10 0x003A3700 (float(int))
//    11 0x0047A699 (bool() const) 12 0x0055AED6 Rva0055AED6(Xfer *, void *)
//    13..16 __purecall: Team supplies 13 getLocation (0x0039D7DB) and 14..16.
//  - Slot signatures come from the bodies' own rows; vslotNN names are
//    placeholders for slots whose rows belong to other classes (ICF-shared
//    bodies or AIBuildable spellings), so callers through this class keep the
//    retail slot index.
//  - sizeof 0x2C: Team's ctor 0x003A39A7 constructs it at +4 and starts its own
//    members at +0x30.
#ifndef CANONICAL_RVA0055B0CC_H
#define CANONICAL_RVA0055B0CC_H

struct Coord3D;
class Xfer;

class Rva0055B0CC
{
public:
	Rva0055B0CC();									// 0x0055B048
	virtual ~Rva0055B0CC();							// 0x0055B0CC (slot 0: ??_G 0x0055B166)
	virtual void vslot01();							// slot 1, 0x0055AFA3
	virtual float vslot02() const;					// slot 2, 0x0055B0B9
	virtual void vslot03(int);						// slot 3, 0x0055B146
	virtual bool vslot04() const;					// slot 4, 0x0047A699
	virtual void rva0055B228();						// slot 5, 0x0055B228
	virtual void vslot06(void *, bool);				// slot 6, 0x0055AD91
	virtual void vslot07(int);						// slot 7, 0x005F69CE
	virtual float vslot08(int);						// slot 8, 0x003A36D3
	virtual float vslot09(int);						// slot 9, 0x003A36F7
	virtual float vslot10(int);						// slot 10, 0x003A3700
	virtual bool vslot11() const;					// slot 11, 0x0047A699
	virtual void Rva0055AED6(Xfer *, void *);		// slot 12, 0x0055AED6
	virtual Coord3D getLocation() const = 0;		// slot 13, pure here
	virtual bool vslot14() const = 0;				// slot 14, pure here
	virtual bool vslot15(int) = 0;					// slot 15, pure here
	virtual int vslot16(void *) = 0;				// slot 16, pure here

	void rva0055B01F();								// 0x0055B01F

private:
	unsigned char m_opaque04[0x2C - 0x04];			// +0x04; AIBuildable.cpp names the fields
};
typedef char CanonicalRva0055B0CCSizeCheck[sizeof(Rva0055B0CC) == 0x2C ? 1 : -1];

#endif // CANONICAL_RVA0055B0CC_H

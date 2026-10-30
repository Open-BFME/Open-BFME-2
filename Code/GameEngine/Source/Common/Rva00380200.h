#pragma once
// Rva00380200: the 0x2C-byte polymorphic base Player builds at +8 (the row
// notes call it the player's skill-points rank object; original name unknown).
//
// Target facts, read off game.dat (code addresses are RVAs, tables VAs):
//  - Its ctor 0x00380523 installs table 0x00BFDC30: six slots (the next
//    table, 0x00BFDC48, follows directly; no /GR), ??_G 0x002A9844 (a trivial
//    inline destructor: table store, then the optional delete),
//    1 rva0038037C (0x0038037C, bool(int)), 2 0x0038027B (void(int)),
//    3 0x0038028B (void()), 4 0x0047A69C (empty, one argument), 5 0x0047A699
//    (bool(), returns false). The rva0038037C row is the only one spelled
//    virtual; the others keep rslotNN placeholders so callers keep the retail
//    slot index.
//  - Non-virtual members: every Rva00380200 row of reverse/functions.csv,
//    as its decorated name states (all public, Q). The slot 2 and 3 bodies
//    keep both spellings: their rows are non-virtual, the slots virtual.
//  - No out-of-line destructor row exists; Player's ctor 0x002B0F3C starts
//    its own members at +0x34, so sizeof is 0x2C.
#ifndef CANONICAL_RVA00380200_H
#define CANONICAL_RVA00380200_H

class AsciiString;
class Xfer;

class Rva00380200
{
public:
	Rva00380200();									// 0x00380523
	virtual ~Rva00380200() {}						// slot 0
	virtual bool rva0038037C(int);					// slot 1, 0x0038037C
	virtual void rslot02(int);						// slot 2, 0x0038027B
	virtual void rslot03();							// slot 3, 0x0038028B
	virtual void rslot04(const void *);				// slot 4, 0x0047A69C
	virtual bool rslot05();							// slot 5, 0x0047A699

	AsciiString *rva00380200();						// 0x00380200
	void rva0038020D();								// 0x0038020D
	void rva0038027B(int);							// 0x0038027B, slot 2's base body
	void rva0038028B();								// 0x0038028B, slot 3's base body
	int rva003802DF();								// 0x003802DF
	int rva00380459(int);							// 0x00380459
	void rva00380499(Xfer *);						// 0x00380499
	bool rva003805BB(float, bool);					// 0x003805BB

private:
	unsigned char m_opaque04[0x2C - 0x04];			// +0x04
};
typedef char CanonicalRva00380200SizeCheck[sizeof(Rva00380200) == 0x2C ? 1 : -1];

#endif // CANONICAL_RVA00380200_H

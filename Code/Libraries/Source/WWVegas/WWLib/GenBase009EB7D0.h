// FILE: GenBase009EB7D0.h ////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 GenBase009EB7D0, the abstract reference-counted asset base under the
//         texture factories and the HierarchyPrototype asset family.
//
// Target facts (code addresses are RVAs; the table is VA 0x00C7C584, RVA 0x0087C584):
//  - ??0GenBase009EB7D0 (0x0061ED40, 51 bytes) calls no base constructor. It stores word +4 = 0,
//    sets bits 16-23 of +4 to 7 (and 0xFF07FFFF, or 0x70000), clears bits 24-26 (and 0xF8FFFFFF),
//    stores the table 0x00C7C584 at +0 and zeroes +8, +0xC and +0x10.
//  - Derived constructors store their first member at +0x14 right after calling 0x0061ED40
//    (0x001320D0 at 0x001320F9): sizeof 0x14.
//  - The table holds 15 slots: 0-3, 5-7, 13 and 14 are __purecall (0x0003B810); 4 is the shared
//    `ret 4` 0x0047A69C; 8 is 0x0061EDA0 (row ?Delete@AssetFactoryBase@@UAEXXZ); 9 is the scalar
//    deleting destructor 0x0061EE90; 10 is 0x00130FCE; 11 is 0x0061EE20; 12 is 0x0061EE50 (row
//    ?UnloadNow@BfmeE1024@@QAEXXZ).
//  - The destructor body is 0x0061ED80: it stores 0x00C7C584 and passes +0xC to operator delete[]
//    with no element loop. Derived destructors call it (0x00131C2E, 0x00136B4A, 0x0014CDA3). The
//    deleting destructor 0x0061EE90 inlines the same body. 0x00135E35, which the ledger rows as
//    ??1GenBase009EB7D0@@UAE@XZ by fold proof, is the empty destructor of the derived class with
//    table 0x00BD28F0 (constructor 0x00135E23, deleting destructor 0x00135F19) and tail-jumps to
//    0x0061ED80, so calls through that row reach the same body.
//  - Delete 0x0061EDA0 calls slot 10 and tests al; when true it calls slots 5, 6 and 7, setting
//    bits 16-23 of +4 to 4, 5, 6 and finally 7. It then calls slot 9 with 0 and passes the result
//    to operator delete.
//  - +4 bits 0-15 are the reference count: 0x000424B6 (row ?Add_Ref@TextureBaseClass@@QAEXXZ) is
//    `inc word ptr [ecx+4]`; 0x0061ED10 (row ?Release_Ref@TextureBaseClass@@QAEXXZ) returns when
//    the low word is 0, decrements it, and at zero with bit 24 (0x01000000) set jumps through
//    slot 8.
//  - +4 bits 16-23 are a state: 0x0061EE20 and 0x0061EE50 mask 0xFF0000 and compare with 0x30000
//    and 0x70000; slot 10 0x00130FCE returns whether it equals 0x30000.
//  - Slot 10 first calls 0x0061EEC0, which stores the incremented counter at [[0x00E09C0C]]+0x30
//    into +0x10.
// Names: Delete, UnloadNow, Add_Ref and Release_Ref are the ledger's member spellings for these
// bodies. Other slots and members keep neutral names. +4 stays one dword: retail reaches the count
// with word operations and the state with dword masks, and bits 25-26 are only cleared by the
// constructor, so no bitfield split is settled.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_GENBASE009EB7D0_H_
#define __BFME2_GENBASE009EB7D0_H_

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();	// 0x0061ED40

	virtual void slot00() = 0;			// 0
	virtual void slot01() = 0;			// 1
	virtual void slot02() = 0;			// 2
	virtual void slot03() = 0;			// 3
	virtual void vslot04(int) {}			// 4: 0x0047A69C
	virtual void slot05() = 0;			// 5
	virtual void slot06() = 0;			// 6
	virtual void slot07() = 0;			// 7
	virtual void Delete();				// 8: 0x0061EDA0
	virtual ~GenBase009EB7D0();			// 9: deleting destructor 0x0061EE90
	virtual bool vslot10();				// 10: 0x00130FCE
	virtual void vslot11();				// 11: 0x0061EE20
	virtual void UnloadNow();			// 12: 0x0061EE50
	virtual void slot13() = 0;			// 13
	virtual void slot14() = 0;			// 14

	void Add_Ref();		// 0x000424B6
	void Release_Ref();	// 0x0061ED10

	unsigned int m_04;	// +0x04: count in bits 0-15, state in 16-23, delete-at-zero flag in bit 24
	unsigned int m_08;	// +0x08
	char *m_0C;		// +0x0C: array the destructor deletes
	unsigned int m_10;	// +0x10: set by 0x0061EEC0
};

#endif // __BFME2_GENBASE009EB7D0_H_

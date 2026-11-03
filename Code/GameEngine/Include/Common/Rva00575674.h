// Target facts: RVA 0x00575674 (38 bytes) reads the held pointer at +0, guards self-assignment, stores the new pointer at +0 and destroys the old pointee through its slot 0 with flag 0 before freeing the result at 0x0002FD60. The indirect call belongs to the pointee. This holder has no virtual functions, vftable or base.
// RVA 0x005CC698 zeros the holder at +8 (store 0x005CC6F1), passes its address to 0x00575674 at 0x005CC771 and places a different virtual base at +0x0C. RVA 0x0057621A zeros adjacent holders at +0x28/+0x2C (0x005762A2/0x005762A6), and destructor 0x00575F38 clears both at 0x00575FD0/0x00575FDC: sizeof is four bytes, with one pointer at +0.
// Unwind action 0x007A143B destroys the +8 holder by jumping to 0x000AD6F4, the 29-byte nonvirtual owning-pointer cleanup also called on the singleton by 0x007B770E. The destructor stays out of line. No separate constructor/destructor ledger spelling or original class/member name is established for Rva00575674; m_ptr is a neutral pointer label.
#pragma once

#ifndef BFME2_COMMON_RVA00575674_H
#define BFME2_COMMON_RVA00575674_H

class Object;

class Rva00575674
{
public:
	Rva00575674() : m_ptr(0) {}
	~Rva00575674();
	void rva00575674(Object *object);

	Object *m_ptr;
};

#endif

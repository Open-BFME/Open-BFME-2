// Target facts (BFME2 RVAs): 0x006266BA..0x006266D6 forwards one comparator dword to 0x006264B0 and 0x00625BB0; 0x00626969..0x00626983 forwards it to 0x00626780 and 0x006266A0. The 17 byte-matched private views agree on sizeof 4 and one +0 carrier; m_bfmeState and void* retain project placeholders without asserting pointer semantics.
// 0x00625BD1..0x00625BDD and 0x00625DC0..0x00625DCC compare the elements' +4 floats with fld/fcomp, fnstsw and test ah,5: operator() is an inline strict less-than and ignores the carrier. 0x00626A0F initializes only its low byte before 0x00626A1B calls sort; the four-byte ABI slot alone does not prove four meaningful state bytes.
// The ledger spells US4Cmp00625BB0@@ (struct), with no constructor, destructor, copy, assignment or vftable rows. No virtual functions or base storage occur in these retail operations; construction, copying and destruction remain trivial, with no vptr or virtual slots.

#pragma once

#ifndef BFME2_S4CMP00625BB0_H
#define BFME2_S4CMP00625BB0_H

#include "S4SortElem8.h"

struct S4Cmp00625BB0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

#endif

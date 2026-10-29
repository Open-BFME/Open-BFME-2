// FILE: Overridable.h ////////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 Overridable as ThingTemplate's base sees it (Common/ThingTemplate.h).
//
// Target facts: the ThingTemplate constructor (0x0033E1B8) inlines this
// constructor (+0x04 = 0, byte +0x08 = 0, +0x0C = -1) before its own members
// at +0x10; ThingTemplate's one-slot vftable (RVA 0x00810C4C) leaves this class
// no virtual but the destructor, which is out of line at 0x001E3624
// (Overridable.cpp). Zero Hour's MemoryPoolObject base and its pool glue are
// not BFME2's. Donor (Zero Hour Overridable.h) facts: the class and the
// m_nextOverride / m_isOverride names. +0x0C has no recovered name.
// Not registered in reverse/canonical_classes.csv: the 185 private views of
// Overridable are its own lane's reconciliation.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_OVERRIDABLE_H_
#define __BFME2_OVERRIDABLE_H_

//-------------------------------------------------------------------------------------------------
class Overridable
{
public:

	Overridable() : m_nextOverride( 0 ), m_isOverride( false ), m0C( -1 ) { }
	virtual ~Overridable();										// 0x001E3624

	// recursively ask if there is a next override, and if not, return this.
	// Zero Hour's inline body; its out-of-line COMDAT is the 14-byte 0x001E35DF.
	const Overridable *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:

	Overridable *m_nextOverride;								// +0x04
	bool m_isOverride;											// +0x08
	int m0C;													// +0x0C

};

#endif // __BFME2_OVERRIDABLE_H_

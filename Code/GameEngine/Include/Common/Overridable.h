// FILE: Overridable.h ////////////////////////////////////////////////////////////////////////////
// Desc:   BFME2 Overridable as ThingTemplate's base sees it (Common/ThingTemplate.h).
//
// Target facts: the ThingTemplate constructor (0x0033E1B8) inlines this
// constructor (+0x04 = 0, byte +0x08 = 0, +0x0C = -1) before its own members
// at +0x10; ThingTemplate's one-slot vftable (RVA 0x00810C4C) leaves this class
// no virtual but the destructor, which is out of line at 0x001E3624
// (Overridable.cpp). Zero Hour's MemoryPoolObject base and its pool glue are
// not BFME2's. Donor (Zero Hour Overridable.h) facts: the class and the
// m_nextOverride / m_isOverride names and the accessor names, which the ledger
// rows spell. +0x0C has no recovered name.
// Registered in reverse/canonical_classes.csv; units still carrying a private
// view are queued in reverse/header_queue.tsv.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_OVERRIDABLE_H_
#define __BFME2_OVERRIDABLE_H_

//-------------------------------------------------------------------------------------------------
class Overridable
{
public:

	Overridable() : m_nextOverride( 0 ), m_isOverride( false ), m0C( -1 ) { }
	// Retail's copy constructor (0x003664DD) resets to the defaults and ignores the
	// source; its assignment (0x001FD28E) only returns *this, so a copy never takes the
	// source's override chain. Both are out of line (the RankInfo, CrateTemplate and
	// ThingTemplate assignments call 0x001FD28E).
	Overridable( const Overridable &that );						// 0x003664DD
	Overridable &operator=( const Overridable &that );			// 0x001FD28E
	virtual ~Overridable();										// 0x001E3624

	// recursively ask if there is a next override, and if not, return this.
	// Zero Hour's inline body.
	const Overridable *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

	// Zero Hour's other accessors. Retail calls these four out of line, so they are
	// declared here and defined by their rowed owners; the rest keep Zero Hour's
	// inline bodies (no retail row).
	const Overridable *getNextOverride( void ) const { return m_nextOverride; }
	void setNextOverride( Overridable *nextOverridable ) { m_nextOverride = nextOverridable; }
	Overridable *friend_getNextOverride( void ) { return m_nextOverride; }
	Overridable *friend_getFinalOverride( void );				// 0x001E35DF
	const Overridable *friend_getFinalOverride( void ) const;	// 0x00288609
	void markAsOverride( void );								// 0x00248D08
	Overridable *deleteOverrides( void );						// 0x001E35ED
	bool rva0028864F( const Overridable *other ) const;			// 0x0028864F

private:

	Overridable *m_nextOverride;								// +0x04
	bool m_isOverride;											// +0x08
	int m0C;													// +0x0C

};

#endif // __BFME2_OVERRIDABLE_H_

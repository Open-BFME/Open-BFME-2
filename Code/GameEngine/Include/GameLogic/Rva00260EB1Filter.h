/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
 * relationship flags and whether a hit allows.
 * sizeof 20; base Rva000421C8 (PartitionFilter.h).
 * Its destructor only restores the base table 0x00BC26E0 (base teardown).
 */
#pragma once

#ifndef BFME2_RVA00260EB1FILTER_H
#define BFME2_RVA00260EB1FILTER_H

#include "PartitionFilter.h"

class Object;

class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#endif

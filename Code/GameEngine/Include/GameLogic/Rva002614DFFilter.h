/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00C07190, allow 0x002614DF.
 * sizeof 12; base Rva000421C8 (PartitionFilter.h).
 * Its destructor only restores the base table 0x00BC26E0 (base teardown).
 */
#pragma once

#ifndef BFME2_RVA002614DFFILTER_H
#define BFME2_RVA002614DFFILTER_H

#include "PartitionFilter.h"

class Object;

class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

#endif

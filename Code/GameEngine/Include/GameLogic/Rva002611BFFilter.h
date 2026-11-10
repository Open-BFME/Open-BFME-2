/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * ctor 0x002623AB clears +4, installs 0x00BF91BC and stores its const Object*
 * argument at +8; sizeof 12. Table 0x00BF91BC: slot 0 the shared deleting-dtor
 * wrapper 0x00395A19 (base teardown 0x0049C38A), slot 1 allow 0x002611BF, slot 2
 * getPlayerMask 0x0036CC7A. allow compares the candidate's +0x438 bit 3 with this+8.
 */
#pragma once

#ifndef BFME2_RVA002611BFFILTER_H
#define BFME2_RVA002611BFFILTER_H

#include "PartitionFilter.h"

class Object;

class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

#endif

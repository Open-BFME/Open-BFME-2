/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
 * (or none), +0x0C a flag.
 * sizeof 16; base Rva000421C8 (PartitionFilter.h).
 * Its destructor only restores the base table 0x00BC26E0 (base teardown).
 */
#pragma once

#ifndef BFME2_RVA00261058_H
#define BFME2_RVA00261058_H

#include "PartitionFilter.h"

class Object;
class Player;

class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

#endif

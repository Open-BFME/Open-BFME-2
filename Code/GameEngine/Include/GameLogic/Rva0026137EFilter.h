/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a player,
 * +0x0C whether a hit allows.
 * sizeof 16; base Rva000421C8 (PartitionFilter.h).
 * Its destructor only restores the base table 0x00BC26E0 (base teardown).
 */
#pragma once

#ifndef BFME2_RVA0026137EFILTER_H
#define BFME2_RVA0026137EFILTER_H

#include "PartitionFilter.h"

class Object;
class Player;

class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

#endif

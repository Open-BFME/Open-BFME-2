/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
 * object's team against the +0x10 flags, +0x0C whether a hit allows.
 * sizeof 20; base Rva000421C8 (PartitionFilter.h).
 */
#pragma once

#ifndef BFME2_RVA00261409FILTER_H
#define BFME2_RVA00261409FILTER_H

#include "PartitionFilter.h"

class Object;
class Player;

class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

#endif

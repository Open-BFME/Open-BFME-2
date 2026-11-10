/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a player,
 * +0x10 whether a hit allows.
 * sizeof 20; base Rva000421C8 (PartitionFilter.h).
 * Its destructor only restores the base table 0x00BC26E0 (base teardown).
 */
#pragma once

#ifndef BFME2_RVA002614ECFILTER_H
#define BFME2_RVA002614ECFILTER_H

#include "PartitionFilter.h"

class Object;
class Player;

class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

#endif

// Target facts: Player::addTeamToList (RVA 0x002AE228) walks the list at Player +0x32C, compares the TeamPrototype pointer at node +8 and calls list<TeamPrototype *>::push_back at 0x002ADCC7. Its call at 0x002ADCD8 reaches insert 0x002ACF9C, which writes node +0 = position and node +4 = position's previous node (0x002ACFAC..0x002ACFB3). These are the next and previous links.
// Node allocation 0x002AC04E calls pool pop 0x002393E2 on VA 0x00DBBD2C and copies the TeamPrototype pointer into node +8 at 0x002AC065. Sentinel initialization 0x002AC026 writes self-links at +0/+4 (0x002AC040/0x002AC042). Erase 0x002ABAC0 unlinks those fields and returns the node to the pool without a node destructor. This is a non-polymorphic node with no virtual functions, vftable or parent; there are no PlayerTeamNode constructor, destructor or other member rows in the ledger.
// Player::healAllObjects (0x002AB06A) and updateTeamStates (0x002AB429) read next at +0 and pass the value at +8 to TeamPrototype::healAllObjects (0x0039ED6C) and updateState (0x003A34AC). The three four-byte fields occupy 0x0C bytes, matching all private compiled views. Pool grow 0x001EAEF9 carves 0x10-byte slots (0x001EAF4C), which is allocation granularity rather than evidence of a fourth member. PlayerTeamNode is the project's storage-view name for this list node, not a recovered retail class name.
#pragma once

#ifndef BFME2_PLAYERTEAMNODE_H
#define BFME2_PLAYERTEAMNODE_H

class TeamPrototype;

struct PlayerTeamNode
{
    PlayerTeamNode *m_next;
    PlayerTeamNode *m_prev;
    TeamPrototype *m_value;
};

typedef char PlayerTeamNodeSizeCheck[sizeof(PlayerTeamNode) == 0x0C ? 1 : -1];

#endif

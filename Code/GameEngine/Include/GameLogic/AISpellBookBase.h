/* Target facts (BFME2 1.06; code addresses are RVAs, table addresses are VAs):
   AISpellBookBase has no evidenced virtual functions, vptr, bases or data fields.
   Its rowed methods at 0x005EEAC6, 0x005EEB7B and 0x005EEBF6 do not use the
   incoming receiver. Retail calls them directly: 0x005D7DE1, 0x005D7B95 and
   0x005D81E5 pass the enclosing spell-book object's +0x28 helper address.
   The enclosing constructors 0x005D7D76, 0x005D7B2C and 0x005D816B install
   0x00C75EAC, 0x00C75E68 and 0x00C75F84 at +0, respectively. Their destructors
   0x005D7D88, 0x005D7B3E and 0x005D817D restore those same primary tables.
   These seven-slot tables dispatch shouldActivate at slot 6; none belongs to
   the helper at +0x28. Constructor 0x005EE2E6 initializes the enclosing base
   through byte +0x27 without constructing a polymorphic helper at +0x28.
   No AISpellBookBase constructor, destructor or allocation-size row is known.
   Representation: an empty plain class (MSVC sizeof 1), as in the matched
   views; retail's receiver-independent bodies do not independently prove size.
   Method names and parameter class-keys follow the three ledger rows above.
*/

#pragma once

#ifndef __BFME2_AISPELLBOOKBASE_H_
#define __BFME2_AISPELLBOOKBASE_H_

class ModuleData;
class Object;
class Player;
class Rva005EE9CE;
struct Coord3D;

namespace _STL
{
template <class T> class allocator;
template <class T, class Allocator> class vector;
}

class AISpellBookBase
{
public:
    bool findDenseStructureCenter(Player *player, Player *viewingPlayer, Coord3D *denseCenter);
    void findUnitInCombat(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *combatUnits, Player *player);
    void getStatsInCombatRange(Rva005EE9CE *tally, Object *source, float radius);
};

#endif

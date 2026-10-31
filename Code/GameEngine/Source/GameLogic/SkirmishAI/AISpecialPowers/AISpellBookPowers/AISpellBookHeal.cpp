// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AISpellBookHeal::shouldActivate, retail 0x005D81A4 (109B), from the
// WorldBuilder lead (AISpellBookHeal.cpp): find one of the player's units in
// combat (the spell book base at +0x28, 0x005EEA20 with true, true), gather
// the combat statistics within 350 of it (AISpellBookBase::
// getStatsInCombatRange, 0x005EEBF6, into a zeroed 16-byte record from
// 0x005EE9CE) and, when the record's +4 ratio is under 0.8, let the AoE target
// picker (0x005EE8DD) settle on the unit's position.
//
// Target facts: the statistics record, the base and the picker keep their
// ledger's address-derived names.

typedef bool Bool;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Common/PartitionRangeQueryCallView.h"
class Player;
// Native template byte108 bit7 is the tested flag; its enum name is unresolved.
struct PickerTemplate { char before[0x108]; unsigned char flag; };

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }
    const PickerTemplate *getPickerTemplate() const { return m_template; }

private:
	unsigned char m_pad00[4];
    PickerTemplate *m_template;
    unsigned char m_pad08[0x38-8];
	Coord3D m_position;
};

class Rva005EE9CE
{
public:
	Rva005EE9CE *rva005EE9CE();

	float m_0;
	float m_ratio;
	float m_8;
	float m_c;
};

class Rva005EEA20
{
public:
	Object *findUnitInCombat(Player *player, Bool a, Bool b);
	void getStatsInCombatRange(Rva005EE9CE *stats, Object *unit, float range);
};
class AISpellBookBase
{
public:
	void getStatsInCombatRange(Rva005EE9CE *stats, Object *unit, float range);
};

class Rva005EE816
{
public:
	Bool rva005EE8DD(const Coord3D *pos, Object *obj);
};

// shouldActivate is slot 6 of the 7-slot vftable 0x00C75F84 (installed by
// 0x005D816B/0x005D817D), so it is virtual and the vptr sits at +0.
class AISpellBookHeal
{
public:
	virtual Bool shouldActivate(Object *obj);

private:
	unsigned char m_pad04[0x24];
	Rva005EEA20 m_base;
};

Bool AISpellBookHeal::shouldActivate(Object *obj)
{
	Object *unit = m_base.findUnitInCombat(obj->getControllingPlayer(), true, true);
	if (unit)
	{
		Rva005EE9CE stats;
		stats.rva005EE9CE();
		((AISpellBookBase *)&m_base)->getStatsInCombatRange(&stats, unit, 350.0f);
		if (stats.m_ratio < 0.8f)
			return ((Rva005EE816 *)this)->rva005EE8DD(unit->getPosition(), obj);
	}
	return false;
}

// The following sibling is virtual slot6 of native vtableC75FA0, installed
// by ctor5D8211 and the rowed Rva005D8223 destructor. Adjacent seven-slot
// spell-book tables and their named overrides establish shouldActivate;
// the derived class and original source-file names remain unknown.
// Native5D824A..5D8317 and WB1597330 agree on the player/team/shroud graph.
// Source location follows repair_queue's served home beside native5D81A4.
// Layout facts are target accesses: player count14/index54/team2EC,
// template pointer4/flag108, Object position38. The iterator return is24B;
// its current pointer is observed and the remaining20 bytes stay opaque.
// An explicit value copy permits direct return-buffer construction. No
// PMF representation or additional iterator layout is asserted here.
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED };
template<class T> class DLINK_ITERATOR {public:
    T *current;
    unsigned char state[20];
    DLINK_ITERATOR(const DLINK_ITERATOR &that):current(that.current) {
        for(int i=0;i<20;++i)state[i]=that.state[i];
    }
    void advance();
    bool done() const { return !current; }
    T *cur() const { return current; }
};
#include "../../../../../Include/Common/TeamBFME2.h"
class Player {public:
    bool rva002AA245() const;
    Relationship getRelationship(const Player *) const;
    char beforeIndex[0x54];int index;
    char beforeTeam[0x2EC-0x58];Team *team;
};
class PlayerList {public:
    Player *getNthPlayer(int);
    char beforeCount[0x14];int count;
};
extern PlayerList *ThePlayerList;
extern PartitionManager *TheShroudManager;
class Rva005D8223 {public:
    virtual ~Rva005D8223();
    virtual bool shouldActivate(Object *);
};

bool Rva005D8223::shouldActivate(Object *caster)
{
    Player *enemy=0;
    int count=ThePlayerList->count;
    for(int i=0;i<count;++i) {
        if(!enemy) {
            Player *player=ThePlayerList->getNthPlayer(i);
            if(player && !player->rva002AA245() &&
               player->getRelationship(caster->getControllingPlayer())==ENEMIES)
                enemy=player;
        } else break;
    }
    if(enemy && enemy->team) {
        DLINK_ITERATOR<Object> iter=enemy->team->iterate_TeamMemberList();
        for(;!iter.done();iter.advance()) {
            Object *obj=iter.cur();
            if(obj->getPickerTemplate()->flag & 0x80) {
                const Coord3D *position=obj->getPosition();
                int playerIndex=caster->getControllingPlayer()->index;
                if(TheShroudManager->getShroudStatusForPlayer(playerIndex,position)!=CELLSHROUD_SHROUDED)
                    return ((Rva005EE816*)this)->rva005EE8DD(position,caster);
            }
        }
    }
    return false;
}

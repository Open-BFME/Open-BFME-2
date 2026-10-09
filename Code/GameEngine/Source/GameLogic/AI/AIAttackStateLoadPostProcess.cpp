// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME 1 semantic donor: 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/AI/AIAttackState_loadPostProcess.cpp.
// Target identity: C13B78 slot1 follows the Snapshot loadPostProcess convention,
// with slot2 returning AIAttackState. Complete retail346063..3460BF RET/tail
// confirms machine18/owner14, victim team304, saved team2C, weapon template4,
// template name8 and locked weapon name3C. WB E23040 preserves the same calls.
// The weapon-lock predicate retains its existing address-derived owner; no
// claim of its original spelling. Consumed object/weapon prefixes only.
#include "ascii_string.h"

class Team;
enum WeaponSlotType { WEAPON_SLOT_TYPE_UNSPECIFIED = 0 };

struct AttackWeaponTemplateNameView
{
    char m_unrecovered00[8];
    AsciiString m_name;
};

class Weapon
{
public:
    char m_unrecovered00[4];
    AttackWeaponTemplateNameView *m_template;
};

class Object
{
public:
    const Weapon *getCurrentWeapon(WeaponSlotType *) const;
    char m_unrecovered000[0x304];
    Team *m_team;
};

class Rva0028B7B5CmpBoolField
{
public:
    bool get() const;
};

class StateMachine
{
public:
    Object *getGoalObject();
    char m_unrecovered00[0x14];
    Object *m_owner;
};

class AIAttackState
{
protected:
    virtual void slot00();
    virtual void loadPostProcess();
    char m_unrecovered04[0x14];
    StateMachine *m_machine;
    char m_unrecovered1C[0x10];
    Team *m_victimTeam;
    char m_originalVictimPosition[12];
    AsciiString m_lockedWeaponOnEnter;
};

void AIAttackState::loadPostProcess()
{
    Object *victim = m_machine->getGoalObject();
    if (victim)
        m_victimTeam = victim->m_team;

    Object *owner = m_machine->m_owner;
    if (reinterpret_cast<const Rva0028B7B5CmpBoolField *>(owner)->get()
        && owner->getCurrentWeapon(0))
    {
        m_lockedWeaponOnEnter = owner->getCurrentWeapon(0)->m_template->m_name;
    }
    else
    {
        m_lockedWeaponOnEnter.clear();
    }
}

/* Target facts: constructor RVA 0x00543163 calls StateMachine RVA 0x004D79E1 at RVA 0x0054317F with the unchanged receiver, then installs VA 0x00C69680 at RVA 0x00543187. Destructor RVA 0x00542C19 installs the same table and tail-calls StateMachine RVA 0x004D759C; the base installs VA 0x00C60740 and restores Snapshot VA 0x00BBB554 at RVA 0x004D7616. These are base teardown tables. Factory RVA 0x0034145C pushes allocation size 0x74 at RVA 0x00341468 and calls the guard constructor at RVA 0x00341489. The base ends at +0x3C: the constructor clears dwords +0x3C/+0x40/+0x44, floats +0x48/+0x4C/+0x50/+0x54/+0x58/+0x5C, byte +0x60, float +0x64 and dwords +0x68/+0x6C/+0x70 at RVAs 0x0054318D..0x005431C7. VA 0x00C69680 has 16 slots followed by the AIGuardMachine string at VA 0x00C696C0: target RVAs 0x00542ED8, 0x000B3FD0, 0x00542C24, 0x00542FC5, 0x004D7321, 0x004D72C5, 0x004D7A75, 0x004D770F, 0x004D7ACD, 0x000D43D0, 0x000D43D0, 0x002621B8, 0x004D7309, 0x004D7395, 0x004D750F and 0x004D73A4. Only destructor, snapshot name and xfer differ from StateMachine; slots 9/10 keep the parent's neutral names. Slot 2 is rowed as the nonvirtual name() getter, so both that spelling and the inherited snapshot override are declared out of line. Ledger rows prove xfer RVA 0x00542FC5, getStdGuardRange RVA 0x00542C2A, rva00543326 RVA 0x00543326, lookForInnerTarget RVA 0x005433FA, setTargetPositionToGuard RVA 0x0033F867 and setBfmeAreaCenter RVA 0x0033F883. Transfer RVAs 0x00543001..0x005430C8 establish object ID +0x3C, team ID +0x40, nemesis ID +0x68, positions +0x48/+0x54, validity +0x60, four-byte guard mode +0x6C, unsigned field +0x70, area pointer +0x44 and radius +0x64. Setter RVAs 0x0033F83D/0x0033F852 copy Object +0x74 and Team +0x34 to +0x3C/+0x40. Zero Hour GeneralsMD GameLogic/AIGuard.h supplies the shared guard member/accessor names; BFME2's area-center setter and its reads in outer-state onEnter RVA 0x005439F2 establish the added center accessors. RVA 0x0054333A calls GameLogic::findObjectByID with +0x3C and RVA 0x0054334A calls TeamFactory::findTeamByID with +0x40, proving the lookup accessors. The XferObjectID calls at RVAs 0x00543006/0x0054301D take the enum ObjectID addresses, matching the ledger helper signature. AIGuardState::onEnter RVA 0x003511E3 reads the inherited default state ID at +0x1C. The +0x70 member remains neutral because its original name is unproven. */
#pragma once

#ifndef BFME2_AIGUARDMACHINE_H
#define BFME2_AIGUARDMACHINE_H

#include "../Common/StateMachineClass.h"

class PolygonTrigger;
class Team;
enum ObjectID;

class AIGuardMachine : public StateMachine
{
public:
    AIGuardMachine(Object *owner, unsigned int nameKey);
    virtual ~AIGuardMachine();

    const char *name() const;
    bool lookForInnerTarget();
    Coord3D rva00543326() const;
    static float getStdGuardRange(const Object *object);
    void setTargetPositionToGuard(const Coord3D *position, float radius);
    void setBfmeAreaCenter(const Coord3D *position);
    Object *findTargetToGuardByID();
    Object *findTargetToGuardByID() const;
    Team *findTeamToGuardByID();
    Team *findTeamToGuardByID() const;

    StateID getDefaultStateID() const { return m_defaultStateID; }
    const Coord3D *getPositionToGuard() const { return &m_positionToGuard; }
    const PolygonTrigger *getAreaToGuard() const { return m_areaToGuard; }
    void setAreaToGuard(const PolygonTrigger *area) { m_areaToGuard = area; }
    ObjectID getNemesisID() const { return m_nemesisToAttack; }
    void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
    int getGuardMode() const { return m_guardMode; }
    void setGuardMode(int mode) { m_guardMode = mode; }
    bool hasBfmeAreaCenter() const { return m_bfmeAreaCenterValid; }
    const Coord3D *getBfmeAreaCenter() const { return &m_bfmeAreaCenter; }
    float getBfmeGuardRadius() const { return m_bfmeGuardRadius; }

    ObjectID m_targetToGuard;
    unsigned int m_teamToGuard;
    const PolygonTrigger *m_areaToGuard;
    Coord3D m_positionToGuard;
    Coord3D m_bfmeAreaCenter;
    bool m_bfmeAreaCenterValid;
    float m_bfmeGuardRadius;
    ObjectID m_nemesisToAttack;
    int m_guardMode;
    unsigned int field70;

protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
};

typedef char AIGuardMachineSize[sizeof(AIGuardMachine) == 0x74 ? 1 : -1];

#endif

/* Target facts: constructor RVA 0x00351C48 calls StateMachine at RVA 0x00351C64, constructs the three-pointer goal-path vector at +0x3C (LEA RVA 0x00351C6C, call RVA 0x00351C7B), and stores vtable VA 0x00C14CD0 at RVA 0x00351C75. Destructor RVA 0x003516F3 stores the same table at RVA 0x00351704, deletes the squad at +0x4C, frees the vector block at +0x3C and calls StateMachine::~StateMachine at RVA 0x00351741. StateMachine's VA 0x00C60740 (store RVA 0x004D75AF) and Snapshot's VA 0x00BBB554 (store RVA 0x004D7616) belong to base teardown. Allocation RVA 0x0026251F requests 0x68 bytes before calling this constructor at RVA 0x00262540; the parent ends at +0x3C. The constructor clears waypoint +0x48, squad +0x4C, temporary state +0x50, frame end +0x54, object ID +0x58 and three floats +0x5C/+0x60/+0x64. Table VA 0x00C14CD0 contains 16 slots, followed by the name string at VA 0x00C14D10: target RVAs 0x00352B25, 0x000B3FD0, 0x00351753, 0x00353667, 0x003502CA, 0x00352B41, 0x00350392, 0x004D770F, 0x003503D0, 0x0034BA20, 0x0034145C, 0x002621B8, 0x0033FD77, 0x004D7395, 0x0033FCDC, 0x004D73A4. Ledger rows name overrides xfer/updateStateMachine/clear/resetToDefaultState/setState; slot 12 tests the temporary state before the parent's isInBusyState, and slot 14 tail-jumps to the parent's setGoalObject. Slots 9/10 keep the parent's neutral names. Nonvirtual rowed methods: setTemporaryState RVA 0x0033FCE1, rva0035033F RVA 0x0035033F, setGoalTeam RVA 0x0035042D, setGoalAIGroup RVA 0x00350462, setGoalSquad RVA 0x00352B9D, setGoalWaypoint RVA 0x003E3BFB and addToGoalPath RVA 0x0035385E. The latter and xfer establish the Coord3D vector at +0x3C; the header retains its 12-byte storage opaquely; the waypoint setter stores +0x48 and the squad setters access +0x4C. getGoalPathPosition is called from RVA 0x0034DF1D and pinned to RVA 0x00346FA5. The inlined waypoint read in onEnter RVA 0x0034ED7B and Zero Hour AIStateMachine::getGoalWaypoint establish the getter; getCurrentStateID RVA 0x00262FC3 reads the temporary State pointer at +0x50 and its ID at +4, with invalid ID 999999. Zero Hour AIStateMachine.h supplies the shared member and accessor names; BFME2's saved ID and position retain neutral field names. */
#pragma once
#ifndef BFME2_AISTATEMACHINECLASS_H
#define BFME2_AISTATEMACHINECLASS_H

#include "../Common/StateMachineClass.h"

class Waypoint;
class Team;
class Squad;
class AIGroup;

class AIStateMachine : public StateMachine
{
public:
    AIStateMachine(Object *owner, unsigned int nameKey);
    virtual ~AIStateMachine();
protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
public:
    virtual StateReturnType updateStateMachine();
    virtual void clear();
    virtual StateReturnType resetToDefaultState();
    virtual StateReturnType setState(StateID stateID);
    virtual int slot09();
    virtual int slot10();
    virtual bool isInBusyState() const;
    virtual void setGoalObject(const Object *object);

    StateReturnType setTemporaryState(unsigned int stateID, int frameLimit);
    void rva0035033F();
    void setGoalTeam(const Team *team);
    void setGoalAIGroup(const AIGroup *group);
    void setGoalSquad(const Squad *squad);
    void setGoalWaypoint(const Waypoint *waypoint);
    const Waypoint *getGoalWaypoint() { return m_goalWaypoint; }
    void addToGoalPath(const Coord3D *point);
    const Coord3D *getGoalPathPosition(int index) const;
    unsigned int getTemporaryState() const { return m_temporaryState ? m_temporaryState->m_id : 999999; }

    unsigned char field3C[0x0C];
    const Waypoint *m_goalWaypoint;
    Squad *m_goalSquad;
    State *m_temporaryState;
    unsigned int m_temporaryStateFramEnd;
    unsigned int field58;
    Coord3D field5C;
};

typedef char AIStateMachineSize[sizeof(AIStateMachine) == 0x68 ? 1 : -1];

#endif

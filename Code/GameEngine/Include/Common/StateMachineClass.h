/* Target facts: StateMachine constructor RVA 0x004D79E1 (RET 12, scalar name key) and destructor RVA 0x004D759C install VA 0x00C60740; destructor RVA 0x004D7616 then restores Snapshot VA 0x00BBB554 at +0. The latter is the base teardown table, not another StateMachine table. VA 0x00C60740 has 16 code entries followed by data at VA 0x00C60780: slots 0..8 target RVAs 0x004D7A59, 0x000B3FD0, 0x00341456, 0x004D7744, 0x004D7321, 0x004D72C5, 0x004D7A75, 0x004D770F, 0x004D7ACD; slots 9/10 return zero at RVA 0x000D43D0; slots 11..15 target 0x002621B8, 0x004D7309, 0x004D7395, 0x004D750F, 0x004D73A4. Ledger names prove the named slots; 9/10 retain neutral names. Constructor stores bound the extent through byte +0x3A, rounded to 0x3C with four-byte alignment; AIStateMachine constructor RVA 0x00351C48 calls the base at 0x00351C64 and constructs its first member at +0x3C (LEA at 0x00351C6C). It initializes current state +4, constructs a 12-byte tree at +8 (call RVA 0x0033C432), stores owner +0x14, default ID +0x1C, goal ID +0x20, floats +0x24/+0x28/+0x2C/+0x30, dword +0x34 and flags +0x38/+0x39/+0x3A. RVA 0x004D766B reads/writes sleep frame +0x18; RVA 0x004D73C4 copies the goal position and stores range; RVA 0x004D7435 reads Object +0x74 into goal ID. Unknown members remain neutral and the tree is opaque. Out-of-line declarations follow the StateMachine ledger rows at RVAs 0x002621B8..0x00262224 and 0x004D72C5..0x004D7B0F; getGoalObject is called at RVA 0x004D7AE6 and pinned at 0x004D7726. Zero Hour StateMachine.h proves the inline accessor names; retail owner +0x14, current-state +4, state ID +4 and lock +0x38 accesses prove their offsets. StateID parameters are unsigned: RVAs 0x004D764C, 0x004D76F2 and 0x004D7627 pass the parameter's own address to the unsigned-key find RVA 0x00357180 (jb/jae compares), and Zero Hour StateMachine.h declares typedef UnsignedInt StateID. State declarations below retain their existing canonical surface. */
// StateMachine stays apart from State's StateMachine.h: units that adopted State still hold private StateMachine views.
#pragma once
#ifndef BFME2_STATEMACHINECLASS_H
#define BFME2_STATEMACHINECLASS_H

#include "StateMachine.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object;
struct StateConditionInfo;

class StateMachine : public Snapshot
{
public:
    StateMachine(Object *owner, unsigned int nameKey, bool flag);
    virtual ~StateMachine();
protected:
    virtual void loadPostProcess() {}
    // Slot 2 follows the spelling the included Snapshot base selected, as State's does, so it always overrides.
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
public:
    virtual StateReturnType updateStateMachine();
    virtual void clear();
    virtual StateReturnType resetToDefaultState();
    virtual StateReturnType initDefaultState();
    virtual StateReturnType setState(StateID stateID);
    virtual int slot09() { return 0; }
    virtual int slot10() { return 0; }
    virtual bool isInAttackState() const;
    virtual bool isInBusyState() const;
    virtual void rva004D7395();
    virtual void setGoalObject(const Object *object);
    virtual void halt();

    void defineState(unsigned int id, State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions = 0);
    State *internalGetState(StateID stateID);
    StateReturnType internalSetState(StateID stateID);
    bool hasState(StateID stateID);
    void rva004D7627(StateID stateID);
    void setGoalPosition(const Coord3D *position);
    void setGoalPosition(const Coord3D *position, float range);
    void internalSetGoalPosition(const Coord3D *position, float range);
    void internalSetGoalObject(const Object *object);
    void rva004D73AD(const void *source);
    void rva004D7427(const void *source);
    bool isGoalObjectDestroyed() const;
    bool isInGuardIdleState() const;
    bool rva002621DA() const;
    bool rva002621EB() const;
    bool rva002621FC() const;
    bool rva0026220D() const;
    void lock(const char *message);
    void unlock() { m_locked = false; }
    bool isLocked() const { return m_locked; }
    Object *getGoalObject();
    Object *getOwner() const { return m_owner; }
    unsigned int getCurrentStateID() const { return m_currentState ? m_currentState->m_id : 999999; }
    const Coord3D *getGoalPosition() const { return &m_goalPosition; }

    State *m_currentState;
    unsigned char field08[0x0C];
    Object *m_owner;
    unsigned int m_sleepTill;
    int m_defaultStateID;
    int m_goalObjectID;
    Coord3D m_goalPosition;
    float m_goalRange;
    int field34;
    bool m_locked;
    bool m_defaultStateInited;
    bool field3A;
};

inline Object *State::getMachineOwner() const { return m_machine->getOwner(); }
inline Object *State::getMachineGoalObject() const { return m_machine->getGoalObject(); }

#endif

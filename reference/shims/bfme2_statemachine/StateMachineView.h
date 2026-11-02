// Retail StateMachine table at VA 0x00C60740 and its 0x3C-byte object layout.
// Slots 9 and 10 share the zero-return body; their original names are unknown.
#pragma once

class Object;
class Xfer;
struct State;
struct StateConditionInfo;

class StateMachine
{
public:
    StateMachine(Object *owner, unsigned int nameKey, bool flag);
    virtual ~StateMachine();
protected:
    virtual void loadPostProcess() {}
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
public:
    virtual StateReturnType updateStateMachine();
    virtual void clear();
    virtual StateReturnType resetToDefaultState();
    virtual StateReturnType initDefaultState();
    virtual StateReturnType setState(unsigned int stateID);
    virtual int slot09() { return 0; }
    virtual int slot10() { return 0; }
    virtual bool isInAttackState() const;
    virtual bool isInBusyState() const;
    virtual void rva004D7395();
    virtual void setGoalObject(const Object *object);
    virtual void halt();

    void defineState(unsigned int id, State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions = 0);
    Object *getOwner() const { return m_owner; }
    Object *getGoalObject();
    const Coord3D *locomotorGoalPosition() const { return &m_goalPosition; }
    void setGoalPosition(const Coord3D *position, float range);
    __declspec(dllimport) __forceinline unsigned int getCurrentStateID() const;
protected:
    State *m_currentState;
    unsigned char m_pad08[0x14 - 0x08];
    Object *m_owner;
    unsigned char m_pad18[0x24 - 0x18];
    Coord3D m_goalPosition;
    unsigned char m_pad30[0x3C - 0x30];
};

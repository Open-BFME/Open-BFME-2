// Target facts: RVA 0x0033F279 calls State's 0x004D73FC constructor and installs VA 0x00C10DE8; State writes through +0x1C, and this class starts at +0x20. The last byte initialized is +0x4B; derived constructor 0x003429B9 starts at +0x4C, establishing sizeof 0x4C and a 0x20-byte State prefix.
// Table 0x00C10DE8 has 18 slots, followed by the name string at 0x00C10E30: 0 deleting destructor (0x0034280A, calling 0x0033FF2B), 1 empty (0x000B3FD0), 2 name (0x0033F2F7), 3 xfer (0x0033FF76), 4 onEnter (0x0034C146), 5 onExit (0x003473A4), 6 update (0x00347460), 7 clears byte +0x49 (0x0033F2D7), 8-15 false (0x0047A699), 16 empty (0x000B3FD0), 17 computePath (0x003441F7). The destructor at 0x0033FF2B restores the same table, removes the unsigned audio handle at +0x40 and calls the folded State destructor 0x0049B47C.
// Constructor 0x0033F279 and xfer 0x0033FF76 establish Coord3D at +0x20/+0x34, float +0x2C, layer +0x30, unsigned handle +0x40, unsigned timestamp +0x44 and byte flags +0x48..+0x4B. forceRepath (0x0034002A) writes -100 to +0x34/+0x38/+0x3C and the negated frame rate to +0x44; update (0x00347460) compares the frame against +0x44. Zero Hour AIStateMachine.h supplies the matching field and accessor names; +0x2C and +0x4B retain neutral names. Rowed out-of-line methods also include getAdjustsDestination (0x00344138) and startMoveSound (0x00347225).

#pragma once

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../Common/StateMachine.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class State;
class StateMachine;
class Xfer;
struct Coord3D;

class AIInternalMoveToState : public State
{
public:
    AIInternalMoveToState(StateMachine *machine, unsigned int hash);
    virtual ~AIInternalMoveToState();
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);
    virtual StateReturnType update();

protected:
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
    virtual bool computePath();
    bool getAdjustsDestination() const;
    void forceRepath();

    Coord3D m_goalPosition;
    float m_2C;
    int m_goalLayer;
    Coord3D m_pathGoalPosition;
    unsigned int m_ambientPlayingHandle;
    unsigned int m_pathTimestamp;
    bool m_adjustDestinations;
    bool m_waitingForPath;
    bool m_tryOneMoreRepath;
    bool m_4B;

private:
    virtual void _bfme_state_slot7();
    void startMoveSound();
};

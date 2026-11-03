/* Target facts: constructor RVA 0x00546001 calls StateMachine RVA 0x004D79E1 at 0x0054601E with the unchanged receiver, owner, name key 0x91632A45 and false, then installs VA 0x00C6A090 at 0x00546026. Destructor RVA 0x00545B84 installs the same table and tail-calls StateMachine RVA 0x004D759C; that base restores VA 0x00C60740 at 0x004D75AF and Snapshot VA 0x00BBB554 at 0x004D7616. These are successive base teardown tables. Allocations at RVAs 0x0034203C/0x0034203E and 0x003420A2/0x003420A7 reserve 0x50 bytes before constructor calls at 0x00342056 and 0x003420C0. Constructor stores at 0x00546037/0x0054603C/0x00546041 place the three-float position at +0x3C/+0x40/+0x44, after the registered 0x3C-byte StateMachine base; 0x0054602C/0x0054602F initialize nemesis +0x48 and guard mode +0x4C. Transfer RVA 0x00545EB2 calls the base at 0x00545EBD, transfers the ID at 0x00545EE0, the position at 0x00545EEE and four version-2 bytes at 0x00545F01. RVA 0x003420E1 copies the position and 0x003420F4 stores the AI guard mode at +0x4C. VA 0x00C6A090 has 16 code entries followed by the string AITNGuardMachine at VA 0x00C6A0D0: slots 0/1/2/3 target RVAs 0x00545DD2/0x000B3FD0/0x00545B8F/0x00545EB2; slots 4..15 target 0x004D7321, 0x004D72C5, 0x004D7A75, 0x004D770F, 0x004D7ACD, 0x000D43D0, 0x000D43D0, 0x002621B8, 0x004D7309, 0x004D7395, 0x004D750F and 0x004D73A4, identical to the registered base. The base establishes the snapshot override names; the slot-2 body 0x00545B8F is GetSnapshotName. Ledger RVAs 0x00546001, 0x00545B84, 0x00545B8F, 0x00545EB2 and 0x005461A2 prove the out-of-line method declarations. */
// Zero Hour GeneralsMD GameLogic/AITNGuard.h supplies the field and inline accessor names; retail accesses above establish their BFME2 offsets.
#pragma once

#ifndef BFME2_AITNGUARDMACHINE_H
#define BFME2_AITNGUARDMACHINE_H

#include "../Common/StateMachineClass.h"

class AITNGuardMachine : public StateMachine
{
public:
    AITNGuardMachine(Object *owner);
    virtual ~AITNGuardMachine();

    const Coord3D *getPositionToGuard() const { return &m_positionToGuard; }
    void setTargetPositionToGuard(const Coord3D *position) { m_positionToGuard = *position; }
    void setNemesisID(unsigned int id) { m_nemesisToAttack = id; }
    unsigned int getNemesisID() const { return m_nemesisToAttack; }
    int getGuardMode() const { return m_guardMode; }
    void setGuardMode(int guardMode) { m_guardMode = guardMode; }
    bool lookForInnerTarget();

    Coord3D m_positionToGuard;
    unsigned int m_nemesisToAttack;
    int m_guardMode;

protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
};

#endif

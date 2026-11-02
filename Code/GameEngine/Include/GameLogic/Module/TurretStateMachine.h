/* Target facts: constructor RVA 0x004D7CE6 calls StateMachine RVA 0x004D79E1 at 0x004D7D02 with the unchanged receiver, installs VA 0x00C609C8 at 0x004D7D0F and stores its TurretAI argument at +0x3C at 0x004D7D15. TurretAI constructor RVA 0x004D85B6 pushes 0x40 at 0x004D8666, allocates at 0x004D866D and calls this constructor at 0x004D8689: sizeof is 0x40 and the StateMachine base occupies 0x3C. Destructor RVA 0x004D7E61 installs the same table and tail-calls StateMachine RVA 0x004D759C; the base constructor/destructor install VA 0x00C60740, and the base teardown restores Snapshot VA 0x00BBB554 at RVA 0x004D7616. VA 0x00C609C8 has 16 code entries followed by the name string at VA 0x00C60A08: slot 0 is deleting destructor RVA 0x004D8523; slot 1 is the inherited empty loadPostProcess RVA 0x000B3FD0; slot 2 returns that string at RVA 0x004D7E5B; slot 3 is the version-only transfer RVA 0x00306A9B. Slots 4..15 target RVAs 0x004D7321, 0x004D853F, 0x004D855B, 0x004D770F, 0x004D8578, 0x000D43D0, 0x000D43D0, 0x002621B8, 0x004D7309, 0x004D7395, 0x004D750F and 0x004D73A4. Ledger rows name clear, resetToDefaultState and setState at slots 5, 6 and 8; the other slots retain the registered base declarations. Ledger rows at RVAs 0x004D7726 and 0x004D7735 declare the out-of-line object lookups through inherited +0x20 and +0x34. Zero Hour GeneralsMD GameLogic/TurretAI.h supplies the m_turretAI and getTurretAI names, corroborated by the +0x3C constructor store and reads at RVAs 0x004D8547, 0x004D8563 and 0x004D8598. The registered base and its retail table establish the snapshot override names; no shim declaration supplies target evidence. */
#pragma once

#ifndef BFME2_TURRETSTATEMACHINE_H
#define BFME2_TURRETSTATEMACHINE_H

#include "../../Common/StateMachineClass.h"

class TurretAI;

class TurretStateMachine : public StateMachine
{
public:
    TurretStateMachine(TurretAI *turretAI, Object *owner, unsigned int nameKey);
    virtual ~TurretStateMachine();

    virtual void clear();
    virtual StateReturnType resetToDefaultState();
    virtual StateReturnType setState(StateID newStateID);

    Object *getGoalObject();
    Object *rva004D7735();
    TurretAI *getTurretAI() const { return m_turretAI; }

    TurretAI *m_turretAI;

protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
};

#endif

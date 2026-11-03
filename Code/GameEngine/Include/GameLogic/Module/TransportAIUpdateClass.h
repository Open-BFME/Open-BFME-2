// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x004A9042 calls AIUpdateInterface at 0x004A904D, then stores
// 0x00C53AA8/+0, 0x00BFA3C0/+0x0C, 0x00C53A98/+0x10,
// 0x00C47B88/+0x20 and 0x00C52F88/+0x24 at 0x004A9052..0x004A906D.
// Destructor 0x004A9080 restores the identical five tables at
// 0x004A9080..0x004A909B, then jumps to AIUpdateInterface's 0x0026E836.
// The parent's 0x0026E9BD first constructs its interfaces with pure tables
// 0x00C1C780/+0x20 and 0x00C40818/+0x24, then replaces them at
// 0x0026EA14/0x0026EA1B. Those are base construction states.
// Factory 0x0024F192 pushes 0x3E4 at 0x0024F19D and calls 0x004A9042
// at 0x0024F1BC. Transport adds no fields to its 0x3E4 registered parent.
// The 154-slot primary table changes parent slots 0 (deleting destructor
// 0x004A912B), 1 (0x0049A7EE, tail-jumping to loadPostProcess 0x002686A4),
// 2 (0x004A907A, returning "TransportAIUpdate" at 0x00BF4F88),
// 3 (xfer 0x0049060D), 4 (getModuleNameKey 0x004A90A7),
// 34 (privateAttackObject 0x004A9147), 38 (privateForceAttackObject
// 0x004A91E0), 40 (privateAttackPosition 0x004A9279) and
// 150 (makeStateMachine 0x004A90EC). All other slots equal the parent.
// Secondary tables equal the parent's 47/3/1/6-slot tables. There are no
// additional virtual slots. Named method signatures come from ledger rows;
// Snapshot and loadPostProcess override the registered parent's slots.
// Zero Hour TransportAIUpdate.h independently names the three attack
// overrides and makeStateMachine; its getAiFreeToExit has no BFME2 override.
// HordeWorker constructor 0x0049AD15 calls HordeAIUpdate at 0x0049AD2C;
// its 0x3E8 base includes that class's +0x3E4 interface, not Transport data.
#pragma once
#ifndef __BFME2_TRANSPORTAIUPDATECLASS_H_
#define __BFME2_TRANSPORTAIUPDATECLASS_H_

#include "AIUpdate.h"

class TransportAIUpdate : public AIUpdateInterface
{
public:
    TransportAIUpdate(Thing *, const ModuleData *);
    virtual ~TransportAIUpdate();
    virtual NameKeyType getModuleNameKey() const;
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    virtual void privateAttackObject(Object *, int, CommandSourceType);
    virtual void privateForceAttackObject(Object *, int, CommandSourceType);
    virtual void privateAttackPosition(const Coord3D *, int, CommandSourceType);
    virtual AIStateMachine *makeStateMachine();
};

typedef char TransportAIUpdateParentExtent[sizeof(AIUpdateInterface) == 0x3E4 ? 1 : -1];
typedef char TransportAIUpdateExtent[sizeof(TransportAIUpdate) == 0x3E4 ? 1 : -1];

#endif

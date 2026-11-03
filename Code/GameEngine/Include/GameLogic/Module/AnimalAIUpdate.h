// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0047ECA8 calls AIUpdateInterface at 0x0026E9BD. Factory
// 0x0024BE95 pushes 0x3FC at 0x0024BEA0 and calls it at 0x0024BEBF.
// AIUpdateInterface's factory 0x0024BDB7 allocates 0x3E4 bytes. The added
// one-slot interface occupies +0x3E4; 0x0047ECC1 installs its pure table
// 0x00C1C780, then 0x0047ECC7 replaces it with 0x00C47B84.
// Constructor 0x0047ECE1..0x0047ECFC and destructor 0x0047EB78..0x0047EB9A
// agree on 0x00C47B98/+0, 0x00BFA3C0/+0x0C, 0x00C47B8C/+0x10,
// 0x00C47B88/+0x20, 0x00C52F88/+0x24 and 0x00C47B84/+0x3E4.
// The destructor jumps to AIUpdateInterface's 0x0026E836 at 0x0047EBA4;
// scalar deleting destructor 0x0047ED21 calls it at 0x0047ED24.
// Primary table 0x00C47B98 has 154 entries before text at 0x00C47E00.
// Compared with AIUpdateInterface's table, slots 0,1,2,3,4,96,150 differ:
// 0x0047ED21, 0x0049A7EE, 0x0047EBA9, 0x0047EBAF, 0x0047EC1A,
// 0x004A9B51 and 0x0047EC69. Slot 2 returns "AnimalAIUpdate" at
// 0x00BF4F68; slot 4 passes that same string to nameToKey at 0x0047EC44.
// 0x0049A7EE tail-calls AIUpdateInterface::loadPostProcess. Slot 96
// returns the +0x3E4 interface, preserving null (0x004A9B51).
// The +0x10 table's slot 0 is update (0x0047EDC9); its other two slots,
// the 47-slot +0x0C table, the one-slot +0x20 table and the six-slot +0x24
// table retain the parent's entries. The +0x3E4 table has one slot,
// 0x0047EC5F, which reads ModuleData at [ecx-0x3E0], then byte +0x7C.
// Constructor stores at 0x0047ECCF..0x0047ECDB establish a dword at
// +0x3E8 and bytes at +0x3F8/+0x3F9; 0x0047ED03..0x0047ED13 zero
// floats +0x3F4/+0x3F0/+0x3EC. xfer 0x0047EBAF passes these fields to
// XferObjectID (0x0047EBD5), bool slots (0x0047EBE7/0x0047EC06) and
// the Coord3DBase slot (0x0047EBF8), then calls the parent's xfer.

#pragma once
#ifndef __BFME2_ANIMALAIUPDATE_H_
#define __BFME2_ANIMALAIUPDATE_H_

#include "AIUpdate.h"
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva0047EB78_Interface3E4
{
public:
    virtual unsigned char rva0047EC5F() const = 0;
};

class AnimalAIUpdate : public AIUpdateInterface, public Rva0047EB78_Interface3E4
{
public:
    AnimalAIUpdate(Thing *, const ModuleData *);
    virtual ~AnimalAIUpdate();
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual unsigned char rva0047EC5F() const;
    virtual void *vslot096();

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#endif
    virtual void xfer(Xfer *);
    virtual AIStateMachine *makeStateMachine();

    ObjectID m_3E8;
    Coord3DBase m_3EC;
    bool m_3F8;
    bool m_3F9;
};

#endif

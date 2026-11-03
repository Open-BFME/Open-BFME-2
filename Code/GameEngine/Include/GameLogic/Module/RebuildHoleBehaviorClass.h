// Target facts (code addresses are RVAs; tables and strings are VAs):
// 0x00483271 calls UpdateModule at 0x00253390, initializes interface tables
// 0x00C1C780 at +0x20 and 0x00C078DC at +0x24, then installs 0x00C49A74 at
// +0, 0x00C49188 at +0x0C, 0x00C49A68 at +0x10, 0x00C49A64 at +0x20 and
// 0x00C49A50 at +0x24. Destructor 0x0048353E restores those same five tables
// and calls ~UpdateModule at 0x0024A797. The initial +0x20/+0x24 pure tables
// belong to interface construction; all five final stores are vptrs.
// Factory 0x0024C3FB allocates 0x48 bytes at 0x0024C406 and calls 0x00483271.
// Primary table 0x00C49A74 has 14 slots: deleting destructor 0x00483629,
// loadPostProcess 0x00497805 (jumps to 0x0058B03E), Snapshot name 0x0048331C,
// xfer 0x004833EC, name key 0x004832D7, four empty slots, onCapture 0x0050B238,
// two null getters, getUpdatePhase 0x0022C4CB and the +0x24 getter 0x00483322.
// Name and key bodies use "RebuildHoleBehavior" at 0x00BF5880. The 47-slot
// behavior table overrides getDie (slot 7, 0x004543A9, +0x0C -> +0x20) and
// getUpdate (slot 9, 0x002533D3). The three-slot update table holds update
// 0x00483645, getDisabledTypesToProcess 0x00253376 and rva0044DF8D 0x0044DF8D.
// The die table holds onDie 0x004835FB, which receives this+0x20 and clears
// the worker ID at interface+8. Neither added interface has a destructor slot.
// Rebuild interface 0x00C49A50 has five slots: startRebuildProcess 0x004835B4
// (this+0x24), getters 0x001DB0A8 (+0x0C), 0x0030F45F (+8), 0x002A79A1
// (+0x18), then 0x00210CD3 (stores the argument byte at +0x20, ret 4).
// Call 0x00486930 dispatches that fifth slot with the spawn interface's byte
// flag. setSlot4Flag is the existing neutral label for this slot and access.
// Constructor stores and xfer 0x004833EC prove ObjectIDs +0x28/+0x2C/+0x30,
// unsigned counter +0x34, template pointers +0x38/+0x3C, float transfer +0x40
// and bool transfer +0x44. The constructor clears +0x28..+0x40 and sets +0x44.
// Out-of-line rows: newWorkerRespawnProcess 0x0048337A and interface search
// 0x004831CB; the latter returns module+0x24 after the module-name-key test.
// Donor facts: Zero Hour RebuildHoleBehavior.h names the interfaces, methods
// and six fields +0x28..+0x3C. The added byte setter and tail fields stay neutral.

#pragma once

#ifndef __BFME2_REBUILDHOLEBEHAVIORCLASS_H_
#define __BFME2_REBUILDHOLEBEHAVIORCLASS_H_

#include "UpdateModule.h"
#include "DieModuleInterface.h"

class ThingTemplate;
enum ObjectID;

class RebuildHoleBehaviorInterface
{
public:
    virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID) = 0;
    virtual ObjectID getSpawnerID() = 0;
    virtual ObjectID getReconstructedBuildingID() = 0;
    virtual const ThingTemplate *getRebuildTemplate() const = 0;
    virtual void setSlot4Flag(bool value) = 0;
};

class RebuildHoleBehavior : public UpdateModule,
    public DieModuleInterface, public RebuildHoleBehaviorInterface
{
public:
    RebuildHoleBehavior(Thing *thing, const ModuleData *moduleData);
    virtual ~RebuildHoleBehavior();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *obj);

    virtual NameKeyType getModuleNameKey() const;
    virtual DieModuleInterface *getDie() { return this; }
    virtual UpdateSleepTime update();
    virtual RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterface();
    virtual void onDie(const DamageInfo *damageInfo);
    virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID);
    virtual ObjectID getSpawnerID() { return m_spawnerObjectID; }
    virtual ObjectID getReconstructedBuildingID() { return m_reconstructingID; }
    virtual const ThingTemplate *getRebuildTemplate() const { return m_rebuildTemplate; }
    virtual void setSlot4Flag(bool value) { m_44 = value; }

    void newWorkerRespawnProcess(Object *existingWorker);

    ObjectID m_workerID; // +0x28
    ObjectID m_reconstructingID; // +0x2C
    ObjectID m_spawnerObjectID; // +0x30
    unsigned int m_workerWaitCounter; // +0x34
    const ThingTemplate *m_workerTemplate; // +0x38
    const ThingTemplate *m_rebuildTemplate; // +0x3C
    float m_40; // +0x40
    bool m_44; // +0x44

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);
};

#endif

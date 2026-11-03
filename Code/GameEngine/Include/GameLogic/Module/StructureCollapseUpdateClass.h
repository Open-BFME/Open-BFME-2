// Target facts (code addresses are RVAs; table addresses are VAs):
// 0x004A42E4 calls UpdateModule's constructor at 0x00253390, initializes the
// DieModuleInterface at +0x20 with 0x00C1C780, then installs 0x00C52648 at +0,
// 0x00C49188 at +0x0C, 0x00C5263C at +0x10 and 0x00C52638 at +0x20.
// 0x0024EDA2 allocates 0x44 bytes; 0x0024EDBE calls this constructor.
// Destructor 0x004A4214 (rowed as Rva004A4214) restores those same four tables
// and jumps to ~UpdateModule at 0x0024A797. The BehaviorModule table stores
// there are inlined base destruction, not StructureCollapseUpdate tables.
// 0x00C52648 has 13 slots: deleting destructor 0x004A436F, loadPostProcess
// 0x00497805, Snapshot name 0x004A4234, xfer 0x004A4AB2, name key 0x004A429F,
// four empty slots, onCapture 0x0050B238, two null getters and getUpdatePhase
// 0x0022C4CB. The name getter and key body use "StructureCollapseUpdate"
// at 0x00BF4FCC. The 47-slot behavior table overrides getDie (slot 7,
// 0x004543A9) and getUpdate (slot 9, 0x002533D3). The update table has update
// 0x004A46BF, getDisabledTypesToProcess 0x004A4580 and rva0044DF8D 0x0044DF8D.
// The die table has only onDie 0x004A466E and no destructor; this body receives
// this+0x20, reads module data at -0x1C and the object at -0x18, then subtracts
// 0x20 before calling beginStructureCollapse at 0x004A459B.
// Constructor stores and xfer 0x004A4AB2 prove 4-byte fields at +0x24, +0x28,
// +0x2C, +0x30, +0x34, +0x38, +0x3C and +0x40. The first two transfer as
// unsigned integers, +0x2C as four raw bytes, and the last five as floats.
// 0x004A459B copies Object position into +0x38/+0x3C/+0x40; update 0x004A46BF
// uses that triple as the collapse origin. The other fields and method names
// follow the rowed bodies and Zero Hour's StructureCollapseUpdate declaration.
// Out-of-line helpers: getCollapseHeight 0x004A438B, doPhaseStuff 0x004A43E9
// and doCollapseDoneStuff 0x004A44B1. The destructor remains declaration-only.

#pragma once

#ifndef __BFME2_STRUCTURECOLLAPSEUPDATECLASS_H_
#define __BFME2_STRUCTURECOLLAPSEUPDATECLASS_H_

#include "UpdateModule.h"
#include "DieModuleInterface.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class StructureCollapseUpdateModuleData;
enum StructureCollapsePhaseType;
enum StructureCollapseStateType;

class StructureCollapseUpdate : public UpdateModule, public DieModuleInterface
{
public:
    StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~StructureCollapseUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static NameKeyType rva0004A429F();

    virtual NameKeyType getModuleNameKey() const;
    virtual DieModuleInterface *getDie() { return this; }
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual void onDie(const DamageInfo *damageInfo);

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    void beginStructureCollapse(const DamageInfo *damageInfo);
    float getCollapseHeight() const;
    void doPhaseStuff(StructureCollapsePhaseType scphase, const Coord3D *target);
    void doCollapseDoneStuff();

    const StructureCollapseUpdateModuleData *getStructureCollapseUpdateModuleData() const
    {
        return (const StructureCollapseUpdateModuleData *)getModuleData();
    }

    unsigned int m_collapseFrame; // +0x24
    unsigned int m_burstFrame; // +0x28
    StructureCollapseStateType m_collapseState; // +0x2C
    float m_collapseVelocity; // +0x30
    float m_currentHeight; // +0x34
    Coord3D m_collapsePosition; // +0x38
};

#endif

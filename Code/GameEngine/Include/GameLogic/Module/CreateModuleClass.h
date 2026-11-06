// Target facts: CreateModule ctor RVA 0x004B8CF7 calls BehaviorModule at 0x00253330, stores primary VA 0x00C59368 at +0, BehaviorModuleInterface VA 0x00BEF9C0 at +0x0C and CreateModuleInterface VA 0x00C59358 at +0x10, then byte +0x14 = 1. ObjectModule ctor RVA 0x00306AA7 stores the ModuleData argument at +4 and the Object at +8. The flag requires at least 0x15 bytes; SpawnedModelConditionCreate factory RVA 0x0025496D allocates 0x18 and its ctor 0x00250A1F only replaces these three vptrs, bounding the aligned CreateModule size to 0x18.
// Target facts: VA 0x00C4EF80 is the four-purecall interface construction table; VA 0x00C59358 is its CreateModule override table: purecall, RVA 0x00250A49 (clear byte interface +4), 0x000B3FD0 (ret), 0x00098CBC (read byte interface +4). Primary VA 0x00C59368 has 12 slots, with deleting dtor 0x004B8D32, loadPostProcess 0x0058B03E, name getter 0x004B8D2C and xfer 0x004B8D4E in slots 0-3. Dtor 0x004B8CDE retains VA 0x00C59358 at +0x10, restores BehaviorModule's VA 0x00BEEA7C and 0x00BEE9C0 at +0/+0x0C, then jumps to Snapshot teardown 0x0049B47C; these are base teardown tables, not competing CreateModule layouts.
// Target facts: CreateModule::xfer RVA 0x004B8D4E calls BehaviorModule::xfer 0x004C9C7D and transfers byte +0x14. SupplyCenterCreate::onBuildComplete 0x004B8E2B and GrantUpgradeCreate::onBuildComplete 0x004B9093 occupy interface slot 1 and call slot 3 before clearing interface +4. BehaviorModuleInterface slot 3 at VA 0x00BEF9C0 selects RVA 0x002533D3, which converts interface +0x0C to interface +0x10. Donor names: Zero Hour CreateModule.h proves getCreate, onCreate, onBuildComplete, shouldDoOnBuildComplete and m_needToRunOnBuildComplete; BFME2's additional interface slot 2 remains slot02. The interface has no virtual destructor.

#pragma once

#ifndef __BFME2_CREATEMODULECLASS_H_
#define __BFME2_CREATEMODULECLASS_H_

#include "BehaviorModule.h"

class CreateModuleInterface
{
public:
    virtual void onCreate() = 0;
    virtual void onBuildComplete() = 0;
    virtual void slot02() = 0;
    virtual bool shouldDoOnBuildComplete() const = 0;
};

class CreateModule : public BehaviorModule, public CreateModuleInterface
{
public:
    CreateModule(Thing *thing, const ModuleData *moduleData);

    virtual CreateModuleInterface *getCreate() { return this; }
    virtual void onCreate() = 0;
    virtual void onBuildComplete() { m_needToRunOnBuildComplete = false; }
    virtual void slot02() { }
    virtual bool shouldDoOnBuildComplete() const { return m_needToRunOnBuildComplete; }

protected:
    virtual ~CreateModule();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);

    bool m_needToRunOnBuildComplete;
};

#endif

// Target facts (code addresses are RVAs; table and string addresses are VAs):
// 0x0024F8F6 allocates 0x44 bytes and calls 0x004AF096 at 0x0024F91D.
// 0x004AF096 calls UpdateModule's 0x00253390, then stores 0x00C556B0,
// 0x00BEFF90 and 0x00C556A4 at +0, +0x0C and +0x10 respectively.
// UpdateModule occupies 0x20 bytes: its constructor writes through +0x1C,
// and RespawnUpdate starts with a float at +0x20. The two secondary vptrs
// belong to the inherited BehaviorModuleInterface and UpdateModuleInterface.
// 0x00C556B0 has 16 slots, ending before non-code 0x46EA6000 at 0x00C556F0.
// Slots 0-4 are 0x004AF161, 0x00497805, 0x004AF15B, 0x004AF00B,
// 0x004AF116; slots 5-8 are 0x000B3FD0, 9 is 0x0050B238, 10-11 are
// 0x000D43D0, 12 is 0x0022C4CB. Slots 13-15 are getPercentReady
// (0x004AEFAD), getDeadImage (0x004AF2DE), and a const byte getter
// (0x005C4FEB, reads +0x41); the last slot's original name is unknown.
// 0x004AF15B returns "RespawnUpdate" at 0x00BF4F08. Its ledger spelling
// is the nonvirtual name(); the inherited Snapshot name slot is slot 2.
// 0x00C556A4 holds update (0x004AF92F), the disabled-mask getter
// (0x004DF396, copies the four-byte BitFlags<11> at 0x00E030D0), and
// UpdateModule's wake method (0x0044DF8D). 0x00BEFF90 is inherited unchanged.
// Deleting destructor 0x004AF161 calls 0x004AF17D, which jumps to
// ~UpdateModule (0x0024A797). Its 0x00BEEA7C/0x00BEE9C0 stores are inlined
// BehaviorModule destruction, not RespawnUpdate's live tables. EnragedBehavior
// shares this empty destructor but has a different primary table (0x00C40FBC).
// 0x004AF096 initializes float +0x20, dwords +0x24/+0x28/+0x2C/+0x30/
// +0x34/+0x38/+0x3C, and bytes +0x40/+0x41. 0x004AF00B transfers +0x20
// as float, +0x2C as a mode, +0x30 as ObjectID, +0x34/+0x38/+0x3C as int,
// and +0x40/+0x41 as bool. 0x004AF2DE uses +0x24 as an Image pointer;
// 0x004AF25D returns the cached pointer at +0x28. Names remain placeholders.
// Other out-of-line ledger methods: rva004AEF46 (0x004AEF46), rva004AF182
// (0x004AF182), searchForSuitableSpawnAtObject (0x004AF1CE),
// triggerDeathBeforeRespawn (0x004AF63E), triggerRevival (0x004AF79C),
// iniParseDefaultRule (0x004AFC5F), iniParseNewRuleForLevel (0x004AFE6C).

#pragma once

#ifndef __BFME2_RESPAWNUPDATE_H_
#define __BFME2_RESPAWNUPDATE_H_

#include "UpdateModule.h"

class Image;
class INI;

class RespawnUpdate : public UpdateModule
{
public:
    RespawnUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~RespawnUpdate();

    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual float getPercentReady(int *out);
    virtual const Image *getDeadImage();
    virtual bool vslot15() const;

    const char *name() const;
    void rva004AEF46();
    void rva004AF182();
    void *rva004AF25D();
    Object *searchForSuitableSpawnAtObject();
    void triggerDeathBeforeRespawn();
    void triggerRevival(Object *at);

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static void iniParseDefaultRule(INI *, void *, void *, const void *);
    static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);

    float m_20;
    const Image *m_24;
    void *m_28;
    int m_2C;
    unsigned int m_30;
    int m_34;
    int m_38;
    int m_3C;
    bool m_40;
    bool m_41;

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

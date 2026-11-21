// Target facts (code addresses are RVAs; table and string addresses are VAs):
// Factory 0x0024E8E0 allocates 0x24 and calls constructor 0x0049FF06, whose
// base call is UpdateModule (0x00253390). The constructor zeroes +0x20 and
// installs 0x00C5191C/+0, 0x00BEFF90/+0x0C and 0x00C51910/+0x10.
// Destructor 0x0049FE7B restores those three tables and tail-jumps to
// ~UpdateModule (0x0024A797); deleting destructor 0x0049FF34 is slot 0 of the
// primary table 0x00C5191C. That table's slot 1 is loadPostProcess 0x00497805
// (jumps to 0x0058B03E), slot 2 the snapshot name 0x0049FE94 (returns
// "ProneUpdate" at 0x00BF500C), slot 3 xfer 0x0049508D (Version1, base xfer,
// int at +0x20), slot 4 getModuleNameKey 0x0049FE9A. The +0x10 table's slot 0
// is update 0x0049FFA0. startProneEffects 0x0049FF50, stopProneEffects
// 0x0049FF78 and goProne 0x0049FFB9 access +0x20 as a four-byte counter.

#pragma once

#ifndef __BFME2_PRONEUPDATE_H_
#define __BFME2_PRONEUPDATE_H_

#include "UpdateModule.h"

class DamageInfo;
class ProneUpdateModuleData;

class ProneUpdate : public UpdateModule
{
public:
    ProneUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~ProneUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    void goProne(const DamageInfo *damageInfo);
    virtual UpdateSleepTime update();
    virtual NameKeyType getModuleNameKey() const;

protected:
    virtual void loadPostProcess();
    virtual void xfer(Xfer *xfer);

    const ProneUpdateModuleData *getProneUpdateModuleData() const
    {
        return (const ProneUpdateModuleData *)getModuleData();
    }
    void startProneEffects();
    void stopProneEffects();

    int m_proneFrames; // +0x20
};

#endif

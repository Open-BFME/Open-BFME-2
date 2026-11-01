// Target facts (all code addresses are RVAs; vftables are VAs):
// 0x00253390 calls BehaviorModule at 0x00253330, installs 0x00BF004C at +0,
// 0x00BEFF90 at +0x0C and 0x00BFBCE4 at +0x10, and writes 0, -1, -1 at
// +0x14, +0x18, +0x1C. AIGateUpdate's 0x004B08E8 starts its fields at +0x20,
// bounding UpdateModule at sizeof 0x20; its added interface occupies 4 bytes.
// BehaviorModule's 0x00BEEA7C has 12 primary slots; 0x00BF004C has 13,
// ending before the UpdateModule string at 0x00BF0080. Slots 1, 2, 3 are
// loadPostProcess (0x0058B03E), GetSnapshotName (0x002533CD), xfer (0x0044DF9F);
// slot 12 is getUpdatePhase (0x0022C4CB, returns 2). There is no crc slot.
// 0x00BEFF90 has BehaviorModuleInterface's 47 slots with slot 9 = 0x002533D3,
// which converts the +0x0C interface pointer to the +0x10 update interface.
// The interface's 0x00BE2B78 holds three pure slots; 0x00BFBCE4 holds pure
// update, getDisabledTypesToProcess (0x00253376), rva0044DF8D (0x0044DF8D).
// The getter's row names BitFlags<11>; its bytes copy four bytes from
// 0x00E030CC. BitFlags<11>::xfer (0x00292414) loops to 11, not 13.
// The wake body subtracts 0x10, loads Object at +8 and calls
// setWakeFrame (0x0044DF71). Neither interface has a virtual destructor.
// 0x0024A797 stores 0x00BFBCE4 at +0x10, then BehaviorModule's 0x00BEEA7C
// and 0x00BEE9C0 at +0/+0x0C, and jumps to 0x0049B47C (Snapshot reset).
// The latter stores are inlined base destruction, not UpdateModule tables.
// 0x0023C3C6 clamps and stores the raw frame at +0x14; 0x0023C3DA returns
// +0x18 and writes +0x1C through its argument. 0x0044DF5B reads raw +0x14.
// frameToSleepTime is rowed at 0x0044DF28. These methods and the destructor
// at 0x0024A797 have out-of-line owners.
// Donor facts: Zero Hour UpdateModule.h names update, getUpdate, getUpdatePhase,
// m_nextCallFrameAndPhase, m_indexInLogic, the wake/sleep helpers and the
// SleepyUpdatePhase and UpdateSleepTime enum types. Common/BitFlags.h uses an
// unsigned size_t template parameter; BFME2's getter row selects value 11.

#pragma once

#ifndef __BFME2_UPDATEMODULE_H_
#define __BFME2_UPDATEMODULE_H_

// A unit that already read Snapshot without the name slot spells that slot crc.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "BehaviorModule.h"

template <unsigned int NUM_BITS> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

enum UpdateSleepTime;
enum SleepyUpdatePhase;

class UpdateModuleInterface
{
public:
    virtual UpdateSleepTime update() = 0;
    virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();

    virtual UpdateModuleInterface *getUpdate() { return this; }
    virtual UpdateSleepTime update() = 0;
    virtual DisabledMaskType getDisabledTypesToProcess() const;
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay);
    virtual void xfer(Xfer *xfer);

    void friend_setNextCallFrame(unsigned int frame);
    int rva0023C3DA(int *phase);

    unsigned int m_nextCallFrameAndPhase; // +0x14
    int m_indexInLogic; // +0x18
    int m_field1C; // +0x1C

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual SleepyUpdatePhase getUpdatePhase() const;

    void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
    UpdateSleepTime getWakeFrame() const;
    UpdateSleepTime frameToSleepTime(unsigned int frame1,
        unsigned int frame2, unsigned int frame3, unsigned int frame4);
};

typedef UpdateModule *UpdateModulePtr;

#endif

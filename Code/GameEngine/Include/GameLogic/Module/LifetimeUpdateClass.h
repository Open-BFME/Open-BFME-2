// Target facts (code addresses are RVAs; table and string addresses are VAs):
// 0x0024E376 allocates 0x2C bytes; 0x0024E392 calls the constructor at
// 0x003A4B58. That constructor calls UpdateModule at 0x00253390 and stores
// 0x00C1B038, 0x00BEFF90 and 0x00C1B02C at +0, +0x0C and +0x10.
// The destructor rowed as Rva003A49D1 at 0x003A49D1 restores those same
// tables and jumps to ~UpdateModule at 0x0024A797; its deleting wrapper is
// 0x003A4A97. The base destructor's 0x00BEEA7C and 0x00BEE9C0 stores are
// inlined BehaviorModule destruction, not LifetimeUpdate's own tables.
// 0x00C1B038 has 13 primary slots, followed by zero at 0x00C1B06C. Slots
// 0-4 are 0x003A4A97, 0x00497805, 0x003A49EA, 0x003A4AFA, 0x003A4A27;
// slots 5-12 equal UpdateModule's 0x00BF004C. Slot 2 returns the string
// "LifetimeUpdate" at 0x00BE11E8. The registered parent supplies the slots.
// 0x00BEFF90 is the parent's 47-slot behavior interface; slot 9 is
// 0x002533D3. 0x00C1B02C has update at 0x003A4BFD, the inherited disabled
// mask getter at 0x00253376, and wake override rva0044DF8D at 0x003A4AE1.
// Both update and the wake override receive the +0x10 interface pointer.
// 0x003A4B76/79/7C initialize a byte at +0x28 and dwords at +0x20/+0x24;
// 0x003A49F0 stores the current frame at +0x24 and frame plus delay at
// +0x20. 0x003A4AFA transfers both dwords and the byte. 0x003A4AE1 clears
// the byte through [interface+0x18]. UpdateModule occupies the first 0x20.
// Out-of-line rows also prove setLifetimeRange (0x003A4AB3), rva003A4AD2
// (0x003A4AD2), calcSleepDelay (0x003A49F0), friend_newModuleInstance
// (0x0024E36B) and friend_newModuleData (0x0024E3A3).
// Donor facts: Zero Hour LifetimeUpdate.h names m_dieFrame, getDieFrame,
// setLifetimeRange and calcSleepDelay. The other two fields stay unnamed.

#pragma once

#ifndef __BFME2_LIFETIMEUPDATECLASS_H_
#define __BFME2_LIFETIMEUPDATECLASS_H_

#include "UpdateModule.h"

class INI;

class LifetimeUpdate : public UpdateModule
{
public:
    LifetimeUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~LifetimeUpdate();

    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual void rva0044DF8D(UpdateSleepTime wakeDelay);

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static ModuleData *friend_newModuleData(INI *ini);
    void setLifetimeRange(unsigned int minFrames, unsigned int maxFrames);
    void rva003A4AD2();
    unsigned int getDieFrame() const { return m_dieFrame; }

    unsigned int m_dieFrame; // +0x20
    unsigned int m_field24; // +0x24
    bool m_field28; // +0x28

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    unsigned int calcSleepDelay(unsigned int minFrames, unsigned int maxFrames);
};

#endif

// Target facts (code RVAs, table VAs): factory 0x0024FAB5 allocates 0xC8 and calls 0x004B21B9; that constructor calls UpdateModule 0x00253390, installs the one-slot pure base 0x00C1C780 at +0x20, then tables 0x00C5667C/+0, 0x00C565C0/+0x0C, 0x00C565B0/+0x10 and 0x00C565AC/+0x20. Destructor 0x004B1322 restores the same four tables before calling 0x0024A797; that base destructor's 0x00BEEA7C/0x00BEE9C0 stores are inlined BehaviorModule destruction. The UpdateModule base occupies 0x20 bytes (0x002533A7..0x002533AF), and the secondary base has no destructor slot.
// Target facts: 0x00C5667C has 13 slots: destructor 0x004B15CA, loadPostProcess 0x004B0FB9, name getter 0x004B138D (literal 0x00BF4EA8, EmotionTrackerUpdate), xfer 0x004B1ECB, getModuleNameKey 0x004B1393, four empty slots 0x000B3FD0, onCapture 0x0050B238, then three zero-return slots 0x000D43D0. The 47-slot +0x0C table changes slot 6 to 0x004543A9 and slot 9 to 0x002533D3; the three-slot +0x10 table is update 0x004B1633, getDisabledTypesToProcess 0x00253376, rva0044DF8D 0x0044DF8D. The +0x20 slot is rva004B15E6 (0x004B15E6), whose +0x7C/+0x70 accesses are complete-object +0x9C/+0x90.
// Target facts: 0x004B2253..0x004B2266 initialize twelve bytes at +0x24 and twelve dwords each at +0x30/+0x60; 0x004B0D4C/0x004B0D70 access those arrays. Constructor 0x004B220A builds the pointer vector at +0x90; 0x004B221F builds the 12-byte tree at +0xA4, and xfer 0x004B1ECB transfers its four-byte ObjectID keys. Stores 0x004B2219..0x004B2282 establish +0x9C/+0xA0, dwords +0xB0/+0xB4/+0xB8/+0xBC/+0xC4 and byte +0xC0; 0x004B0FB9 indexes the vector with +0xC4. Out-of-line ledger methods also include rva004B0EBC (0x004B0EBC), ForceEmotion (0x004B0DAC) and rva004B13D8 (0x004B13D8); nested TauntPointFilter is named by rows 0x004B0EE5/0x004B0FEB/0x004B0D28. Unproved field and secondary-base names remain placeholders.

#pragma once
#ifndef BFME2_EMOTIONTRACKERUPDATE_H
#define BFME2_EMOTIONTRACKERUPDATE_H

#include "UpdateModule.h"
#include "../Rva002EE9B7.h"

class EmotionNugget;

class EmotionTrackerUpdateSecondaryBase
{
public:
    virtual void rva004B15E6() = 0;
};

class EmotionTrackerUpdate : public UpdateModule, public EmotionTrackerUpdateSecondaryBase
{
public:
    class TauntPointFilter;
    enum { SLOT_COUNT = 12 };

    EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~EmotionTrackerUpdate();
    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    virtual UpdateSleepTime update();
    virtual NameKeyType getModuleNameKey() const;
    virtual void rva004B15E6();
    virtual void *slot06();

    const char *name() const;
    bool rva004B0EBC();
    EmotionNugget *rva004B13D8();
    void rva004B0D4C(int index, void *source);
    void PulseEmotion(int index, void *source, int delay);
    void ForceEmotion(int index, float value, int source);

    bool field24[SLOT_COUNT];
    unsigned int field30[SLOT_COUNT];
    unsigned int field60[SLOT_COUNT];
    EmotionNugget **field90;
    EmotionNugget **field94;
    EmotionNugget **field98;
    EmotionNugget *field9C;
    int fieldA0;
    Rva002EE9B7 fieldA4;
    int fieldB0;
    int fieldB4;
    unsigned int fieldB8;
    unsigned int fieldBC;
    bool fieldC0;
    int fieldC4;

protected:
    virtual void loadPostProcess();
    virtual void xfer(Xfer *xfer);
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual SleepyUpdatePhase getUpdatePhase() const;
};

typedef char EmotionTrackerUpdateRetailSize[(sizeof(EmotionTrackerUpdate) == 0xC8) ? 1 : -1];

#endif

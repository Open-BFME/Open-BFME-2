// Target facts (code RVAs, table VAs): factory 0x0024B37C allocates 0x34 bytes at 0x0024B387 and calls constructor 0x0045EF80 at 0x0024B3A3; constructor calls UpdateModule 0x00253390 at 0x0045EF8B and the 16-byte storage constructor 0x00330757 at this+0x20 (0x0045EF90), zeros the stance word at +0x30 (0x0045EF98), and installs tables 0x00C424DC/+0, 0x00BEFF90/+0x0C, 0x00C424D0/+0x10 (0x0045EF9C..0x0045EFA9). Destructor 0x0045F001 restores those same three tables at 0x0045F013..0x0045F020; cleanup 0x0078A729 null-adjusts this+0x20 before jumping to storage destructor 0x0007FAB3, proving a secondary storage base. Its original type name is unknown; Rva00330757Member is the ledger's neutral constructor/destructor spelling.
// Table 0x00C424DC has 13 slots: 0=0x0045F068 (deleting destructor), 1=0x00497805 (tail jump to UpdateModule::loadPostProcess 0x0058B03E), 2=0x0045EFB6 (returns the StancesBehavior name at VA 0x00BF5A4C), 3=0x0045ED9D (xfer), 4=0x0045EFBC (getModuleNameKey), 5..8=0x000B3FD0, 9=0x0050B238, 10..11=0x000D43D0, 12=0x0022C4CB. Table 0x00BEFF90 has the parent's 47 slots, with slot 9=0x002533D3; table 0x00C424D0 has update 0x0045F290, getDisabledTypesToProcess 0x00253376 and wake 0x0044DF8D. This class is polymorphic. UpdateModule's constructor 0x00253390 installs 0x00BF004C, whereas destructor 0x0024A797 restores BehaviorModule's 0x00BEEA7C and 0x00BEE9C0 during inlined base destruction; these are different lifetime stages, not competing StancesBehavior tables.
// Storage constructor 0x00330757 calls 0x00211E58 for three pointer words and writes -1 at storage+0x0C; listener walks 0x0045EE57/0x0045EEC4 read begin/end at +0/+4 and the index at +0x0C, and destructor 0x0007FAB3 frees the first pointer. Classifier 0x0045ED4B reads signed stance at +0x30; xfer 0x0045ED9D passes its address at 0x0045EDC3. HordeContain::xfer finds this module at 0x004751AC..0x004751B9, reads +0x30 at 0x004751BF (the private getStance accessor), then calls changeStanceFromXfer at 0x004751E5; changeStance 0x0045F084 reads and writes the same stance word. Other out-of-line ledger methods are changeStanceFromXfer 0x0045EDD5, changeStance 0x0045F084, rva0045F21C 0x0045F21C, rva0045F235 0x0045F235, update 0x0045F290 and getModuleNameKey 0x0045EFBC. Update's object load at 0x0045F293 uses secondary this-8, and its primary call at 0x0045F2B2 uses this-0x10, confirming the +0x10 interface. No Zero Hour StancesBehavior declaration establishes names or layout here.

#pragma once

#ifndef __BFME2_STANCESBEHAVIOR_H_
#define __BFME2_STANCESBEHAVIOR_H_

#include "Module/UpdateModule.h"
#include "../Common/Rva00330757Member.h"

class StancesBehavior : public UpdateModule, private Rva00330757Member
{
public:
    StancesBehavior(Thing *thing, const ModuleData *moduleData);
    virtual ~StancesBehavior();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();

    int getStance() const { return m_stance; }
    int rva0045ED4B() const;
    bool changeStanceFromXfer(int value);
    bool changeStance(int value);
    void rva0045F21C();
    void rva0045F235();

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    int m_stance;
};

#endif

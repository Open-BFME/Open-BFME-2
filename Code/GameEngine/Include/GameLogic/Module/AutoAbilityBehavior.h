// Target facts (code/table addresses are RVAs/VAs): 0x0024AFAD allocates 0x34 bytes and calls 0x0045A78F, which calls UpdateModule (0x00253390), installs 0x00C4175C/+0, 0x00BEFF90/+0x0C and 0x00C41750/+0x10, and zeros +0x20/+0x24/+0x28/+0x2C/+0x30 (last write is one byte).
// 0x0045A37F restores those same tables, destroys AsciiString +0x20 through 0x00036410 and calls ~UpdateModule (0x0024A797). That base restores BehaviorModule tables during teardown; its 0x00BF004C constructor table has 13 primary slots, matching 0x00C4175C. The latter's slots 0..4 are 0x0045A560/0x00497805/0x0045A3C8/0x0045A291/0x0045A3CE; slots 5..12 retain UpdateModule's targets. The +0x10 table has update (0x0045A963), getDisabledTypesToProcess (0x004A2D67, returns mask 8) and 0x0044DF8D; +0x0C retains UpdateModule's 47-slot table.
// 0x0045A3C8 returns "AutoAbilityBehavior"; 0x0045A3CE keys that same name. 0x0045A291 transfers the string at +0x20, byte +0x30 and coordinate triple +0x24. Nonvirtual declarations retain the ledger's spellings at 0x0045A413/0x0045A421/0x0045A447/0x0045A57C/0x0045A6D3/0x0045A6FE/0x0045A748/0x0045A8C2. No new primary slots are introduced; the rowed constructor and destructor are out of line.
#pragma once

#ifndef BFME2_AUTOABILITYBEHAVIOR_H
#define BFME2_AUTOABILITYBEHAVIOR_H

#include "UpdateModule.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class CommandButton;
struct BfmeWideResult;
struct Rva0045A6D3Arg;
struct Rva0045A8C2Options;

class AutoAbilityBehavior : public UpdateModule
{
public:
    AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData);
    virtual ~AutoAbilityBehavior();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual DisabledMaskType getDisabledTypesToProcess() const;

    void rva0045A413();
    void rva0045A421(void *source);
    Object *rva0045A447(BfmeWideResult *items, const CommandButton *button);
    bool rva0045A57C();
    int isAutoAbilityCommand(const Rva0045A6D3Arg *commandButton);
    void rva0045A6FE(void *button);
    void rva0045A748(void *source, bool flag);
    void rva0045A8C2(Object *source, Object *target, const Rva0045A8C2Options *options);

    AsciiString m_20;
    Coord3D m_24;
    bool m_30;

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

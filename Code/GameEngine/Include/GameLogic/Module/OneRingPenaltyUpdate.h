// Target facts (code addresses are RVAs; table and string addresses are VAs):
// Factory 0x0024E3F4 allocates 0x34 at 0x0024E3FF and calls constructor
// 0x00499A70. Its base call at 0x00499A87 is UpdateModule (0x00253390).
// The constructor first installs DieModuleInterface's pure table 0x00C1C780
// at +0x20, then 0x00C50260/+0, 0x00C49188/+0x0C, 0x00C50254/+0x10
// and 0x00C50250/+0x20. Destructor 0x00499934 restores those four tables
// and tail-calls ~UpdateModule (0x0024A797); its ledger name is Rva00499934.
// The transient +0x20 pure table belongs to base construction, not this class.
// The primary table has 13 slots, ending at the zero word 0x00C50294:
// destructor 0x00499AE1, loadPostProcess 0x00497805 (jumps to 0x0058B03E),
// Snapshot name 0x00499954 (returns "OneRingPenaltyUpdate" at 0x00BF5578),
// xfer 0x0049995A, getModuleNameKey 0x004999AC, then inherited slots 5-12.
// Behavior-interface slot 7 is 0x004543A9 (converts +0x0C to +0x20),
// slot 9 is 0x002533D3; the other 45 slots match the inherited interface.
// The +0x10 table has update 0x00499E98 and UpdateModule's two remaining
// slots. The +0x20 table has one slot, 0x00499D18: subtract 0x20 from this,
// call 0x00499C46, ret 4. The registered DieModuleInterface supplies its ABI.
// Constructor stores at 0x00499ABD..0x00499AC8 zero four-byte fields at
// +0x24/+0x28/+0x2C/+0x30, with MOVSS at +0x2C. Xfer 0x0049995A calls
// XferObjectID (0x003060B2) on +0x24 and transfers uint/float/uint after it.
// Update 0x00499E98 and helpers 0x00499AFD, 0x00499C35, 0x00499C6C and
// 0x00499D23 prove the out-of-line declarations and these same offsets.

#pragma once

#ifndef __BFME2_ONERINGPENALTYUPDATE_H_
#define __BFME2_ONERINGPENALTYUPDATE_H_

#include "UpdateModule.h"
#include "DieModuleInterface.h"

enum ObjectID;

class OneRingPenaltyUpdate : public UpdateModule, public DieModuleInterface
{
public:
    OneRingPenaltyUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~OneRingPenaltyUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual void onDie(const DamageInfo *damageInfo);
    virtual DieModuleInterface *getDie() { return this; }

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    void rva00499AFD();
    void rva00499C35();
    void rva00499C46();
    void rva00499C6C();
    void rva00499D23();

    ObjectID m_24; // +0x24
    unsigned int m_28; // +0x28
    float m_2C; // +0x2C
    unsigned int m_30; // +0x30
};

#endif

// FXListStore target facts (code addresses are RVAs; table addresses are VAs): constructor 0x001E33A5 calls SubsystemInterface's 0x001B4E63 at 0x001E33B7, then stores 0x00BDD97C at 0x001E33C3. Destructor 0x001E2AD9 (ledger owner Rva001E2AD9) restores the same table at 0x001E2AEE and calls the parent destructor 0x001B4E74 at 0x001E2B9C. The parent's table 0x00BD77A0 is its construction/destruction stage, not a second FXListStore table. The parent constructor clears byte +4 and the AsciiString pointer +8; its destructor destroys the string at +8.
// Table 0x00BDD97C has fourteen slots: 0=0x001E2C92 (deleting destructor calling 0x001E2AD9), 1/3/8/9/10/12=0x000B3FD0 (ret), 2=0x001B5384 (SubsystemInterface::loadIniFilesFromLegend), 4=0x001E0DB9 (bool(int), ret 4), 5=0x0047A699 (false, ret), 6=0x000D43D0 (zero, ret), 7/13=0x0047A69C (ret 4), 11=0x005CB9FF (false, ret 4). The parent contract establishes inherited slot order; Zero Hour FXList.h supplies init/reset/update names at 1/9/10. Slot 4 calls slot 2 and reports the literal at VA 0x00BDD930, "RIF: FXList reloaded"; its original member name is unproved.
// GameEngine::init allocates 0x2C bytes before calling 0x001E33A5 at 0x0022EB2F and registers the result through 0x0022A461 into TheFXListStore (VA 0x00DFDC3C). Construction calls map storage +0x0C at 0x001E33C9 and vector storage +0x20 at 0x001E33D5; destruction tears them down at 0x001E2B91 and 0x001E2B79..0x001E2B84. Parser 0x001E2CAE indexes the map at +0x0C, reads/writes node+8 as a pointer (0x001E2D1A/0x001E2D9D), and appends a pointer through +0x20 at 0x001E2D35. Lookup 0x001E281A uses map +0x0C and returns node+8. The storage types and field names remain neutral; lookup and static parser names/signatures come from their ledger rows and Zero Hour, not the donor's by-value map layout. Lifetime methods stay out of line.
#ifndef BFME2_FXLISTSTORE_H
#define BFME2_FXLISTSTORE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class FXList;
class INI;

class FXListStore : public SubsystemInterface {
public:
    FXListStore();
    virtual ~FXListStore();
    virtual void init();
    virtual bool vslot04(int);
    virtual void reset();
    virtual void update();

    const FXList *findFXList(const char *name) const;
    static void parseFXListDefinition(INI *ini);

private:
    unsigned char field0C[0x14];
    unsigned char field20[0x0C];
};

extern FXListStore *TheFXListStore;

#endif

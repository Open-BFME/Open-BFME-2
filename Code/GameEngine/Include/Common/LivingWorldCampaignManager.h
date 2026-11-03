/* Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
   0x0022F7E4 allocates 0x30 bytes, 0x0022F7F9 calls constructor 0x003B90DB,
   and 0x0022F81B passes global 0x00E02D6C to registration 0x0022F820 with
   the name TheLivingWorldCampaignManager. The constructor calls SubsystemInterface
   at 0x003B90E2, stores Snapshot's 0x00BBB554 at +0x0C (0x003B90E7), then
   installs 0x00C1FB04 at +0 and 0x00C1FAF4 at +0x0C (0x003B90F9/0x003B90FF).
   Destructor 0x003B923B restores those same two tables at 0x003B924C/0x003B9252;
   its later 0x003B9289 store restores Snapshot during base destruction.
   The class has virtual functions: primary table 0x00C1FB04 has 14 slots,
   targeting 003B93A0, 003B92A2, 001B5384, 000B3FD0, 005CB9FF, 0047A699,
   000D43D0, 0047A69C, 000B3FD0, 000B3FD0, 000B3FD0, 005CB9FF, 000B3FD0,
   0047A69C. Secondary table 0x00C1FAF4 has four slots: 003B912A (subtracts
   0x0C then jumps to 003B93A0), 003B8DD7, 003B9124 (returns the literal
   LivingWorldCampaignManager), 003B8F76. The primary table immediately follows.
   0x003B90EE clears the dword at +0x10; 0x003B9106/0x003B9112 construct
   three-pointer vectors at +0x14/+0x20 through 0x00211E58; 0x003B9117/0x003B911B
   clear bytes +0x2C/+0x2D. 0x003B8BAA and 0x003B8BF9 index pointer slots at
   +0x14 with stride four; 0x003B8CAC reads the end at +0x18. 0x003B8E89
   walks the +0x20 vector with stride 0x68, and 0x003B926C destroys it through
   0x003B904B. Pointer element identities and field names remain unresolved.
   Nonvirtual declarations below retain the ledger's existing spellings and ABI:
   003B8B85, 003B8BAA, 003B8BF9, 003B8C06, 003B8CAC, 003B8CE0, 003B8D06,
   003B8D4D, 003B8D71, 003B8E2B, 003B8E6C, 003B8EDC, 003B8F20, 003B92B9,
   003B930D. Tutorial caller 0x003B8F62 calls the nonthrowing name lookup
   003B8E2B out of line; the lookup only scans pointers and compares strings.
*/
#pragma once
#ifndef BFME2_LIVINGWORLDCAMPAIGNMANAGER_H
#define BFME2_LIVINGWORLDCAMPAIGNMANAGER_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0052BFE1;
class Rva00564DF2NameView;
class Rva003B8F76;
class ModuleData;
namespace _STL {
template<class T> class allocator;
template<class T, class Allocator> class vector;
}

class LivingWorldCampaignManager : public SubsystemInterface, public Snapshot
{
    friend class Rva003B8F76;
public:
    LivingWorldCampaignManager();
    virtual ~LivingWorldCampaignManager();
    virtual void init();
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset();
    virtual void update();
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const;
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer);
#endif

    bool rva003B8B85();
    void *rva003B8BAA();
    void *GetCampaign(int index);
    void StartNewCampaign(int index);
    bool rva003B8CAC();
    void *UseGenericSpawnArmyForPlayer(int playerName, int player);
    AsciiString GetCurrentActName();
    Rva00564DF2NameView *rva003B8D4D(const AsciiString &name);
    void CallActSubroutine(const AsciiString &name);
    void StartNewCampaign(const AsciiString &name);
    Rva0052BFE1 *rva003B8EDC(const AsciiString &name);
    int rva003B8F20();
    void rva003B92B9(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out);
    void rva003B930D(_STL::vector<long, _STL::allocator<long> > *out);

    int field10;
    void **field14;
    void **field18;
    void **field1C;
    void *field20;
    void *field24;
    void *field28;
    unsigned char field2C;
    unsigned char field2D;

private:
    __declspec(nothrow) int rva003B8E2B(const AsciiString &name);
};

#endif

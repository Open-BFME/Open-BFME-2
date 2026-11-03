// Target facts (code addresses are RVAs; table addresses are VAs): constructors 0x0031A257 and 0x0031A372 install 0x00C0C82C at +0 and 0x00C0C824 at +4. Destructor 0x00319D01 installs the same tables at 0x00319D18/0x00319D1E, restores the +4 base table 0x00C62A20 at 0x00319E49, then Snapshot's 0x00BBB554 at 0x00319E65. The temporary constructor table 0x00C62A20 belongs to the secondary base, whose constructor is 0x0020E346. This is a polymorphic class with no virtual bases.
// The primary table has exactly four slots: deleting destructor 0x0031A00E, loadPostProcess 0x0031A02A, GetSnapshotName 0x00319E76 and xfer 0x0031A6DB. The name getter returns "LivingWorldArmy" at VA 0x00C0C83C, immediately after the table. The secondary table has rva003191E2 at 0x003191E2 and RET8 at 0x0050B238; the base table 0x00C62A20 has two RET8 entries, followed by another class's table at 0x00C62A28. Neither secondary table has a destructor slot.
// Allocation 0x002B65EE/0x002B65F3 passes 0x98 to operator new, then 0x002B6615 calls the constructor at 0x0031A372. Both constructors call 0x00330757 at +8; that 0x10-byte list footprint is the registered Rva00330757Member layout (three pointer words and an index at +0x0C), with a listener-specific ICF spelling. Destructor 0x00319D25 uses the +8 list and 0x00319E4F frees its first pointer. Constructors initialize strings at +18/+1C/+24/+28, paired MOVSS fields +34..+50, byte flags +58/+59/+64/+65/+74/+75, float +5C, and wide strings +68/+6C. Destructor 0x00319DF5..0x00319E44 calls their string destructors. Constructor 0x0031A323 creates an ArmySummary for +78, constructs a three-pointer range at +7C through 0x00211E58 and an eight-byte member at +90 through 0x0007E81F. Unknown storage and field identities remain neutral.
// Out-of-line method identities are ledger rows: createVisualObjects 0x0031934B, KillSummaryEntry 0x00319517, TakeUnitFromArmy_Internal 0x003199D2, UseArmySummary 0x0031942B, rva00319EA3 0x00319EA3, rva00319EF9 0x00319EF9, rva00318B83 0x00318B83, initiateMove 0x0031A591, rva0031911F 0x0031911F and rva00318EC0 0x00318EC0. The setter at 0x0031911F writes +54. The ledger's U type mangling establishes struct LivingWorldArmy; no donor identity or layout is assumed.
// Remaining dword stores in the default constructor are +2C/-1 at 0x0031A29A, +30/0 at 0x0031A2A1, +54/-1 at 0x0031A2CC, +60/1 at 0x0031A2DC, +70/-1 at 0x0031A2EF and +88/+8C/0 at 0x0031A312/0x0031A318. The parameterized constructor stores its ID argument at +20; 0x002B6609..0x002B6615 obtains that argument from the logic's incremented counter. At 0x00319213 and 0x0031922A the secondary callback reads complete-object +78/+88 through its incoming this+4, confirming the secondary-base adjustment. No extra primary slot is introduced for that override.
#pragma once

#ifndef BFME2_GAMELOGIC_LIVINGWORLDARMY_H
#define BFME2_GAMELOGIC_LIVINGWORLDARMY_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../Common/Rva00330757Member.h"

class ArmySummary;
class ArmySummaryEntry;
class Coord2D;
class SpawnArmy;
class Rva00318C32Ret;
class Rva004F6093Holder;
struct Rva00318F42View;
struct Rva002B6A04Player;

class Rva0020E346
{
public:
    Rva0020E346();
    ~Rva0020E346() {}
    virtual void rva003191E2(int, int);
    virtual void slot01(int, int);
};

struct LivingWorldArmy : public Snapshot, public Rva00330757Member, public Rva0020E346
{
    LivingWorldArmy();
    LivingWorldArmy(int, SpawnArmy *, Rva002B6A04Player *);
    virtual ~LivingWorldArmy();
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
    virtual void crc(Xfer *);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &);
#else
    virtual void DoXfer(Xfer *);
#endif
#else
    virtual void xfer(Xfer *);
#endif
    virtual void rva003191E2(int, int);

    void createVisualObjects(const AsciiString *);
    void KillSummaryEntry(int);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *, const Rva004F6093Holder &);
    void UseArmySummary(SpawnArmy *);
    void rva00319EA3(LivingWorldArmy *, ArmySummaryEntry *);
    void rva00319EF9(LivingWorldArmy *, int);
    Rva00318F42View *rva00318B83() const;
    void initiateMove(const Coord2D &, Rva00318C32Ret *, int);
    void rva0031911F(int);
    void rva00318EC0();

    AsciiString field18;
    AsciiString field1C;
    int field20;
    AsciiString field24;
    AsciiString field28;
    int field2C;
    int field30;
    float field34[2];
    float field3C[2];
    float field44[2];
    float field4C[2];
    int m_54;
    bool field58;
    bool field59;
    float field5C;
    unsigned int field60;
    bool field64;
    bool field65;
    UnicodeString field68;
    UnicodeString field6C;
    int field70;
    bool field74;
    bool field75;
    ArmySummary *field78;
    unsigned char field7C[12];
    void *field88;
    int field8C;
    unsigned char field90[8];
};

typedef char LivingWorldArmySizeCheck[sizeof(LivingWorldArmy) == 0x98 ? 1 : -1];

#endif

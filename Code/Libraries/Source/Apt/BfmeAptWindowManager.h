// Target facts (code addresses are RVAs; table and global addresses are VAs):
// AptPlayer constructor 0x00224E10 calls SubsystemInterface 0x001B4E63 at 0x00224E23, stores table 0x00BE6E80 at 0x00224E30, and installs this at 0x00DFE4CC at 0x00224F35. BfmeAptWindowManager is the existing text-setter spelling for this object: caller 0x0057C910..0x0057C920 loads that global and calls bfmeSetText 0x00225301; 0x00225299 and 0x00225301 use its +0x48 table, constructed at 0x00224E53..0x00224E5A. Its parent occupies +0..+0x0B; the parent constructor clears byte +4 and dword +8 at 0x001B4E6B..0x001B4E6F.
// Destructor 0x00224A90 restores 0x00BE6E80 at 0x00224AA1 and calls SubsystemInterface destructor 0x001B4E74 at 0x00224B6B. The latter restores 0x00BD77A0. Derived constructor 0x000628EB calls AptPlayer and installs 0x00BC57E0; destructor 0x000628FD restores that derived table before jumping to AptPlayer's destructor. These are parent/derived construction tables, not competing layouts. The manager is polymorphic, with a virtual destructor declared out of line.
// 0x00BE6E80 contains 21 code pointers, ending before the text at 0x00BE6ED4. Slots 0..13 follow SubsystemInterface: 0=0x00224F50, 1=0x00224296, 2=0x001B5384, 9=0x00222471, 10=0x002251E5, 12=0x0022244D; the other inherited words equal 0x00BD77A0. Slot 14=0x0022274A, slots 15..19=__purecall 0x0003B810, and slot 20=AddLevel 0x00224710 (ledger: two by-value AsciiStrings, bool, int).
// Derived table 0x00BC57E0 preserves those 21 positions: 15/16 are 0x00062972/0x00062977, returning the two-float storage at 0x00DB4CF0/0x00DB4CF8 through 0x000A8F58/0x000A8F5E. Slot 15's caller reads both floats at 0x005D4654..0x005D465C; slot 16's caller multiplies both at 0x002225E4..0x002225F9. Slot 17=0x0006297C takes two float-pair inputs and two outputs (ret 16); 18=0x00062A1C takes an int, 19=0x00062A29 takes a bool (both ret 4). Their original method names are unproven and remain vslotNN.
// Factory 0x00041E75 pushes allocation size 0x32C before constructor call 0x00041E8E. AptPlayer writes byte +0x329 at 0x00224F27, proving a four-byte-aligned base extent of at least 0x32C; the whole derived allocation bounds it above by the same size. Constructor 0x00224E36..0x00224EAE builds 0x14-byte tables at +0x0C/20/34/48/5C/70/90/A4/B8 and a 0x0C-byte tree at +0x84; 0x00224EB3..0x00224ECC constructs fourteen 0x28-byte records at +0xCC, then 0x00224ED4 constructs the three-word vector at +0x2FC. Unexposed storage remains opaque.
// Constructor 0x00224EEA..0x00224F27 writes dword +0x30C, bytes +0x310/311/312, dwords +0x314/318/31C/320/324 and bytes +0x328/329. The pointer type of +0x314 is witnessed by 0x0051278F..0x00512794, which stores the current window through global 0x00DFE4CC, and 0x005127AC..0x005127B5, which compares and clears it; other field names remain neutral. The three existing BfmeAptWindowManager ledger members are rva00225299 (0x00225299), bfmeSetText (0x00225301), and rva00225375 (0x00225375, calls bfmeSetText at 0x002253A2). All remain declaration-only.
#ifndef BFME2_BFMEAPTWINDOWMANAGER_H
#define BFME2_BFMEAPTWINDOWMANAGER_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include BfmeAptWindowManager.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../subsystem/SubsystemInterface.h"

class UnicodeString;
class Rva00222CCB;

class BfmeAptWindowManager : public SubsystemInterface
{
public:
    BfmeAptWindowManager();
    virtual ~BfmeAptWindowManager();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void vslot12();
    virtual void vslot14();
    virtual const float *vslot15() = 0;
    virtual const float *vslot16() = 0;
    virtual void vslot17(const float *, const float *, float *, float *) = 0;
    virtual void vslot18(int) = 0;
    virtual void vslot19(bool) = 0;
    virtual int AddLevel(AsciiString, AsciiString, bool, int);

    void rva00225299(const AsciiString &, const UnicodeString &, Rva00222CCB *);
    void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
    void rva00225375(const AsciiString &, const AsciiString &, bool);

    char m_pad00C[0x30C - 0x0C];
    unsigned int field30C;
    bool field310;
    bool field311;
    bool field312;
    void *field314;
    int field318;
    int field31C;
    int field320;
    int field324;
    bool field328;
    bool field329;
};

#endif

// Target facts: constructor RVA 0x006D8860 calls the eight-byte AptValue constructor 0x006DCCC0 with type 5, stores a byte at +8 and installs VA 0x00CEA600 at +0. Factory 0x006D88C0 repeats this construction at 0x006D898D..0x006D89A0 after allocating 12 bytes at 0x006D8974. It reads the free-list link at +8 at 0x006D88E5 and writes the Boolean there at 0x006D8959; insertion 0x006D8A20 writes a next pointer at +8 into pool VA 0x00E18028. The payload is a four-byte union; sizeof is 12.
// Target table 0x00CEA600 has 15 slots with RVAs 006DCAC0, 006DCB20, 006D8A20, 0065CE90, 0073B660, 0065CE90, 00180FD0, 0003FD80, 006C8770, 006D8A20, 0069E440, 006CBD00, 0073B660, 0069E440, 006D8880; assertion text starts at VA 0x00CEA63C. Slots 2/9 override AptValue's ForceDelete/DeleteThis; slots 12/13 replace the parent's pure entries with false/return stubs and retain neutral names. Slot 14 calls destructor 0x006D88B0, which stores 0x00CEA600 then jumps to AptValue destructor 0x006DE350; the base restores 0x00CEAED0. The tables describe derived and base destruction, with one vptr at +0.
// Target declarations: ledger rows name Create(bool) at 0x006D88C0 and ClearPool() at 0x006D89E0; ClearPool calls slots 11/14 at 0x006D89F5/0x006D8A06. Retail toBool's Boolean arm calls the checked cast 0x006DCEA0 and tail-jumps from 0x006DD621 to the byte getter 0x006D89D0, bound as GetBool() const. Allocation 0x006D8976, deleting destructor 0x006D8895 and unwind 0x007A8A80 prove class allocation and sized deletion (12 bytes, 0x006D8680). Construction, virtual destruction, accessors and allocation methods are declared out of line.
#pragma once

#include "AptValue.h"

class AptBoolean : public AptValue
{
public:
    AptBoolean(bool);
    virtual ~AptBoolean();

    virtual void ForceDelete();
    virtual void DeleteThis();
    virtual bool IsGarbageCollected() const;
    virtual void RegisterReferences() const;

    static AptValue *Create(bool);
    static void ClearPool();
    bool GetBool() const;

    static void *operator new(unsigned int);
    static void operator delete(void *, unsigned int);

    union
    {
        bool field08;
        AptBoolean *field08_next;
    };
};

// Target facts: constructor RVA 0x006D84C0 calls the eight-byte AptValue constructor 0x006DCCC0 with type 7, stores a dword at +8 and installs VA 0x00CEA4C0 at +0. Factory 0x006D8520 repeats this construction at 0x006D85ED..0x006D8600 after allocating 12 bytes at 0x006D85D4. Its pool reads +8 at 0x006D8545 and stores the integer there at 0x006D85B9; pool insertion 0x006D8670 writes the next pointer at +8. The payload is a four-byte union; sizeof is 12.
// Target table 0x00CEA4C0 has 15 slots with RVAs 006DCAC0, 006DCB20, 006D8670, 0065CE90, 0073B660, 0065CE90, 00180FD0, 0003FD80, 006C8770, 006D8670, 0069E440, 006CBD00, 0073B660, 0069E440, 006D84E0; assertion text starts at VA 0x00CEA4FC. Slots 2/9 override AptValue's ForceDelete/DeleteThis; slots 12/13 replace the parent's pure entries with false/return stubs and retain neutral names. Slot 14 calls destructor 0x006D8510, which stores 0x00CEA4C0 then jumps to AptValue destructor 0x006DE350; that base teardown restores 0x00CEAED0. The different tables describe derived and base destruction, with one vptr at +0.
// Target declarations: ledger rows name Create(int) at 0x006D8520 and ClearPool() at 0x006D8630; ClearPool calls slots 11/14 at 0x006D8645/0x006D8656. Retail toBool calls GetInt() at 0x006DD62F after the checked integer cast; its existing symbol binding 0x00144010 reads dword +8. Allocation at 0x006D85D6 and unwind 0x007A8A40 prove class allocation and sized deletion (12 bytes, 0x006D8680). Construction, virtual destruction, accessors and allocation methods are declared out of line.
#pragma once

#include "../../../Libraries/Source/Apt/AptValue.h"

class AptInteger : public AptValue
{
public:
    AptInteger(int);
    virtual ~AptInteger();

    virtual void ForceDelete();
    virtual void DeleteThis();
    virtual bool IsGarbageCollected() const;
    virtual void RegisterReferences() const;

    static AptValue *Create(int);
    static void ClearPool();
    int GetInt() const;

    static void *operator new(unsigned int);
    static void operator delete(void *, unsigned int);

    union
    {
        int field08;
        AptInteger *field08_next;
    };
};

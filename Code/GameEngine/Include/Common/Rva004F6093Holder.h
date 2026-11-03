// Canonical BFME2 Rva004F6093Holder. Target addresses are RVAs.
// Target facts: pointer constructor 0x002B2F0C stores its ArmySummaryEntry argument at +0 and increments the pointee's dword +0xB0 when nonnull; copy constructor 0x004F6093 copies that same pointer and increment. Neither constructor stores a vptr or calls a base constructor. Destructor 0x002B2E8E reads +0 and tail-calls release 0x0007DEEF on pointee +0xAC when nonnull; the virtual dispatch inside release belongs to that pointee subobject, not this holder. This class has no virtual functions, vtable or base. Copy loop 0x003F74CF advances source and destination by 4 at 0x003F74E3/0x003F74E7, and fill 0x003F74F5 advances by 4 at 0x003F750E, proving sizeof 4 and the sole pointer at +0. Entry constructors 0x0040CB11/0x004F6318 call the copy constructor on their +4 holder. Placement copy 0x002B2FE2 calls 0x004F6093 without an EH frame; the copy constructor contains only pointer operations and an increment. Assignment calls at 0x002B73ED reach 0x002B2F97, whose existing Holder symbol binding names the 52-byte rowed assignment: retain the new pointee at +0xB0, release the old pointee at +0xAC and copy +0 unless self-assigned. These called bodies remain declared out of line. ArmySummary::GetEntry 0x0040CBD7 zeroes the returned holder at 0x0040CBF1 on a lookup miss, establishing null default initialization. The original holder template and member name are unknown; m_ptr denotes only its proven pointer storage.
#ifndef BFME2_CANONICAL_RVA004F6093HOLDER_H
#define BFME2_CANONICAL_RVA004F6093HOLDER_H

class ArmySummaryEntry;

class Rva004F6093Holder
{
public:
    Rva004F6093Holder() : m_ptr(0) {}
    Rva004F6093Holder(ArmySummaryEntry *); // 0x002B2F0C
    Rva004F6093Holder(const Rva004F6093Holder &) throw(); // 0x004F6093
    ~Rva004F6093Holder(); // 0x002B2E8E
    Rva004F6093Holder &operator=(const Rva004F6093Holder &); // 0x002B2F97

    ArmySummaryEntry *m_ptr;
};

#endif

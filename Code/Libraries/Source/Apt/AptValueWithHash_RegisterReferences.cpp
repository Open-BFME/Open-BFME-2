// cl: /MD
// AptValueWithHash slot 13 in retail vtable 0x008EA228 marks its hash at +8.
// AptObject slot 13 forwards here through the thunk at 0x0070DFD0.
#include "AptNativeHash.h"

class AptValueWithHash {
public:
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual void RegisterReferences() const;
    int m_b;
    AptNativeHash m_hash;
};

// Slots 3 and 4 of the same table: the hierarchy declares both and nothing
// defined them, so every object emitting an AptObject-derived vftable left
// them undefined. Both are trivial and /OPT:ICF folded them away.
//
// Slot 3 returns the ADDRESS of the hash at +8 (`lea eax,[ecx+8]`, 4 bytes).
// A `mov eax,[ecx+8]` is also four bytes and would not fold.
AptNativeHash *AptValueWithHash::GetNativeHashVirtual() { return &m_hash; }

// Slot 4 returns TRUE here. AptValue's own slot 4 returns false, at a
// different address (0x0073B660): a value that carries a hash answers yes.
bool AptValueWithHash::ContainsNativeHashVirtual() const { return true; }

void AptValueWithHash::RegisterReferences() const
{
    const_cast<AptNativeHash &>(m_hash).rva0070B220(const_cast<AptValueWithHash *>(this));
}

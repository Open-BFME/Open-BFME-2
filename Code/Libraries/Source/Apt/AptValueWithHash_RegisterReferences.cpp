// cl: /MD
// AptValueWithHash slot 13 in retail vtable 0x008EA228 marks its hash at +8.
// AptObject slot 13 forwards here through the thunk at 0x0070DFD0.
#include "AptNativeHash.h"

// AptValueGC adds no storage to the AptValue root (vptr and the flag word at +4).
class AptValueGC {
public:
    virtual bool IsGarbageCollected() const;
    int m_b;
};

class AptValueWithHash : public AptValueGC {
public:
    virtual void RegisterReferences() const;
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    AptNativeHash m_hash;
};

void AptValueWithHash::RegisterReferences() const
{
    const_cast<AptNativeHash &>(m_hash).rva0070B220(const_cast<AptValueWithHash *>(this));
}

// AptValueWithHash slot 3 in retail vtable 0x008EA228 (and in every derived
// table) holds 0x006CBFD0: the address of the hash at +8.
AptNativeHash *AptValueWithHash::GetNativeHashVirtual()
{
    return &m_hash;
}

// Slots 4 and 12 of retail vtable 0x008EA228 (and of every derived table)
// both hold the shared `mov al,1; ret` at 0x001826C0.
bool AptValueWithHash::ContainsNativeHashVirtual() const
{
    return true;
}

bool AptValueGC::IsGarbageCollected() const
{
    return true;
}

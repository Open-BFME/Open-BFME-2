// cl: /MD
// AptValueWithHash slot 13 in retail vtable 0x008EA228 marks its hash at +8.
// AptObject slot 13 forwards here through the thunk at 0x0070DFD0.
#include "AptNativeHash.h"

class AptValueWithHash {
public:
    virtual void RegisterReferences() const;
    virtual AptNativeHash *GetNativeHashVirtual();
    int m_b;
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

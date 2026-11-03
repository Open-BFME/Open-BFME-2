// cl: /MD
// AptValueWithHash slot 13 in retail vtable 0x008EA228 marks its hash at +8.
// AptObject slot 13 forwards here through the thunk at 0x0070DFD0.
#include "AptNativeHash.h"

class AptValueWithHash {
public:
    virtual void RegisterReferences() const;
    int m_b;
    AptNativeHash m_hash;
};

void AptValueWithHash::RegisterReferences() const
{
    const_cast<AptNativeHash &>(m_hash).rva0070B220(const_cast<AptValueWithHash *>(this));
}

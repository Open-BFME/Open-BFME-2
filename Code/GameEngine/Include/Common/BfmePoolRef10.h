#pragma once
// Counted reference to an 0x88-byte pooled holder whose OpaqueRefCounted sits at +0x88; constructors 0x00051931 and
// 0x00051950, destructor 0x000519AB releases through the holder's count.
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
struct BfmePoolHolder88
{
    unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};
class BfmePoolRef10
{
public:
    BfmePoolHolder88 *m_target;
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
    // ?BfmePoolRef10::BfmePoolRef10 present-unmatched
    __forceinline BfmePoolRef10() : m_target(0) {}
    BfmePoolRef10(BfmePoolHolder88 *p);
    BfmePoolRef10(const BfmePoolRef10 &other);
    BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
    void rva000519BD();
    void rva00053D26(BfmePoolHolder88 *p);
};

// cl: /O1 /Ireference/shims/bfme2_ascii
// Native 0x00564B1A / 39: assign two StringBase<char> members at +4/+8.
// Both calls reach the rowed copy-set body at 0x000366F0. No original
// class name or complete object size is established. The untouched prefix
// is opaque; it is not declared to be a vtable or given a semantic type.
// StringBase semantics come from its shared header and matched target body.
#include "string_base.h"

class Rva00564B1A
{
    unsigned char m_unknown[4];
    StringBase<char> m_first;
    StringBase<char> m_second;
public:
    Rva00564B1A& rva00564B1A(const Rva00564B1A& other);
};

// ?Rva00564B1A::rva00564B1A present-unmatched
Rva00564B1A& Rva00564B1A::rva00564B1A(const Rva00564B1A& other)
{
    m_first.set(other.m_first);
    m_second.set(other.m_second);
    return *this;
}

// ProductionPrerequisiteAssign.cpp's 12-byte BfmeStringRecord002CF5B1 copy
// assignment: its __copy (0x00564CD4) calls 0x00564B1A, where retail's ICF
// folded the two identical bodies. This view supplies that consumer's
// out-of-line operator= under its own spelling. Target fact: that matched
// __copy's call lands here, so retail's element assignment sets +4 and +8 as
// strings; the consumer's own view still spells +4 as a word (its copy
// constructor 0x002CF5B1 is rowed on that view), an open identity question.
struct BfmeStringRecord002CF5B1
{
    unsigned char m_unknown[4];
    StringBase<char> m_first;
    StringBase<char> m_second;
    BfmeStringRecord002CF5B1& operator=(const BfmeStringRecord002CF5B1& other);
};

BfmeStringRecord002CF5B1& BfmeStringRecord002CF5B1::operator=(const BfmeStringRecord002CF5B1& other)
{
    m_first.set(other.m_first);
    m_second.set(other.m_second);
    return *this;
}

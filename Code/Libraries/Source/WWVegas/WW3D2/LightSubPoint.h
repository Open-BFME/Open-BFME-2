// Target facts (RVAs): LightSubPoint has no virtual functions or vtable: ctor 0x00424CB6 calls 0x0042499E at +0 and the empty vector base 0x00211E58 at +0x0C; dtor 0x004247E3 frees [+0x0C], then calls Rva0042464E::~Rva0042464E (0x0042464E) at +0. Neither stores a vptr.
// The fill loop 0x00424D8C and destruction loop 0x004256D5 both advance 0x18; vector base 0x000B63B2 allocates 0x18-byte elements for 0x0042545A. Thus sizeof is 0x18. The first descriptor occupies +0..+8 (0x005C8C37); copy 0x0042476C copies it via 0x004244EE, then the +0x0C descriptor via four-byte-element vector copy 0x002CFAB9. Original field and element names are unknown.
// Caller 0x004257AD constructs and destroys the same temporary through 0x00424CB6 and 0x004247E3. Copying reaches 0x0042476C through 0x00424D8C -> 0x00424BF4; its ledger spelling is Rva0042476C. Special members stay out of line. The struct key and Rva0042464E teardown spelling follow the matched ledger; int denotes only four-byte scalar storage, and m_vec1/m_vec2 are neutral ordinal labels.
#ifndef BFME2_LIGHTSUBPOINT_H
#define BFME2_LIGHTSUBPOINT_H

#include <vector>

struct Rva0042464E
{
    unsigned int slot00[3];
    ~Rva0042464E();
};

struct LightSubPoint
{
    LightSubPoint(unsigned int count);
    LightSubPoint(const LightSubPoint &other);
    ~LightSubPoint();

    Rva0042464E m_vec1;
    _STL::vector<int> m_vec2;
};

#endif

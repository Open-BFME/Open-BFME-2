// Target facts (retail RVAs): copy constructor 0x0004548B copies 0x80 bytes from the argument to this through memcpy 0x006291A8 and returns this; it remains declared out of line. It has no vptr stores or base calls, and this storage has no virtual functions.
// Calls 0x002CF4A8/0x002CF4BA copy adjacent members at +4/+0x84 in a record whose native stride is 0x104 (0x002CFA12); 0x001EB7E0 copies CarryoverUnit's +0x10 member before its +0x90 scalar. The storage size is 0x80.
// 0x0035B54D/0x0035B551 set a bit in four-byte indexed words, and 0x001EB22D..0x001EB239 copy 32 words; m_bits describes that storage without asserting the original field name. 0x002AEE00..0x002AEE19 and 0x004B8175..0x004B818E clear word[bit >> 5] by AND with ~(1 << (bit & 31)); 0x003A46A5..0x003A46B6 scan all 32 words for any set bit. 0x00328357 reserves 0x80 uninitialized stack bytes passed to the builder at 0x003283C9, so default construction performs no initialization.
#pragma once

#ifndef BFME2_BFMEFIXEDSTORAGE128_H
#define BFME2_BFMEFIXEDSTORAGE128_H

struct BfmeFixedStorage128
{
    BfmeFixedStorage128() {}
    BfmeFixedStorage128(const BfmeFixedStorage128 &other);

    void clear(unsigned int bit)
    {
        m_bits[bit >> 5] &= ~(1u << (bit & 0x1F));
    }

    void clearBit(unsigned int bit)
    {
        m_bits[bit >> 5] &= ~(1u << (bit & 0x1F));
    }

    bool any() const
    {
        for (unsigned int i = 0; i < 32; ++i)
            if (m_bits[i] != 0)
                return true;
        return false;
    }

    unsigned int m_bits[32];
};

#endif

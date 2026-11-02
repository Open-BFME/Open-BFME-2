// Target: BitFlags<11> occupies one four-byte word. The native constructors
// at 0x00481B7F and their callers establish the initialization API and storage;
// AIUpdate's 0x004A2D67 returns the mask with bit 3 set. Other template values
// retain their existing definitions; this contract recovers only value 11.
#pragma once
#ifndef BFME2_BITFLAGS11_H
#define BFME2_BITFLAGS11_H

#include <string.h>

template <int N> class BitFlags;

template <> class BitFlags<11>
{
public:
    enum BogusInitType { kInit = 0 };

    BitFlags();
    BitFlags(BogusInitType, int bit)
    {
        memset(m_words, 0, sizeof(m_words));
        m_words[(unsigned int)bit >> 5] |= (1u << (bit & 31));
    }
    BitFlags(BogusInitType, int, int);
    bool any() const;

private:
    unsigned int m_words[1];
};

#endif

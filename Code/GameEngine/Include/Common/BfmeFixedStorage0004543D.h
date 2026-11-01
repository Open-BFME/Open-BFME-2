// Target facts (retail RVAs): 0x0004543D copies exactly 0x1C bytes through memcpy at 0x006291A8, returns this and has no vptr stores or base calls; this class has no virtual functions or base class.
// 0x00045411 zeroes 0x1C bytes and sets word[index >> 5] |= 1u << (index & 31); 0x003620BD..0x003620EB processes seven dwords. The storage is a 224-bit mask, with seven words at +0..+0x18 and sizeof 0x1C.
// 0x00045861/0x0004586D copy masks into +8/+0x24; 0x002AB35B/0x002AB36A call the nonthrowing copy constructor for two 0x1C-byte arguments, with no destructor calls. Both constructors remain out of line.
#pragma once

#ifndef BFME2_BFMEFIXEDSTORAGE0004543D_H
#define BFME2_BFMEFIXEDSTORAGE0004543D_H

class BfmeFixedStorage0004543D
{
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
    BfmeFixedStorage0004543D(int unused, int bit);

    unsigned int m_bytes[7];
};

#endif

// Target facts (retail RVAs): 0x00045411 zeroes 0x1C bytes through memset at 0x006291AE, then ORs a dword at this + 4 * (unsigned(bit) >> 5); the first argument is unread. This class has no virtual functions, vptr or base-constructor calls.
// 0x004797CE and 0x004A0446 reserve 0x1C bytes for this by-value mask; 0x003621C9..0x003621F7 reads its seven dwords at +0..+0x18. sizeof is 0x1C; m_bits is a neutral bit-storage label, not a recovered retail member name.
// 0x004A0456 calls the three-argument form at 0x0006EE7A; 0x0039A142 calls the six-argument form at 0x002618FA. Both zero 0x1C bytes and set the supplied bits without table stores. 0x0054567F calls the two-argument form without advancing the active EH state, supporting its nonthrowing declaration. All constructors stay out of line; no destructor body is rowed for this class.
#pragma once

#ifndef BFME2_RVA00045411BITSET_H
#define BFME2_RVA00045411BITSET_H

struct Rva00045411BitSet
{
    Rva00045411BitSet(int unused, int bit) throw();
    Rva00045411BitSet(int unused, int bit1, int bit2);
    Rva00045411BitSet(int unused, int bit1, int bit2, int bit3, int bit4, int bit5);

    unsigned int m_bits[7];
};

#endif

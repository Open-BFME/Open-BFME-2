// Target facts (all addresses are retail RVAs):
// 0x00045455 copies exactly 0x4C bytes from the source to this through memcpy
// (call 0x0004545F), without base calls or vptr stores. 0x004CAD77 calls it for
// the leading member, and 0x004CAD80 starts the next member at +0x4C.
// 0x000B3EC7 complements 19 dwords at +0x00..+0x48; 0x000B3ED3 intersects
// those words. 0x000B3FA5 updates the dword at +4*(bit>>5), including +0.
// This is a plain, nonvirtual 0x4C-byte value with no base or vtable slots;
// the first word is flag storage, not a vptr. No row names a destructor.
// 0x003317D2 and 0x0046263F call the copy constructor out of line.
// 0x0045D859 builds a 0x4C-byte temporary with 0x00045455, complements its
// 19 words, then calls 0x00045455 again into the hidden return destination.
// 0x00479092/0x004790A0 zero two default-constructed 0x4C-byte values;
// 0x004790AB/0x004790B9 clear them again. 0x000B62E3/0x000B62EE clear the
// parser's two values, and 0x000B6339..0x000B634B ORs the indexed bit.
// The copy body only calls memcpy (0x006291A8) and returns; it needs no
// throwing constructor or destructor. Its copy declaration is nonthrowing.
// The ledger names the copy constructor and the four rva methods below;
// their declarations keep calls bound to the rowed bodies. Zero Hour's
// GeneralsMD Common/BitFlags.h supplies the clear/set helper names and the
// m_bits storage spelling, not this BFME2 class's identity or layout.
#pragma once

#ifndef BFME2_WEAPONTEMPLATESETHEAD_H
#define BFME2_WEAPONTEMPLATESETHEAD_H

#include <string.h>

class WeaponTemplateSetHead
{
public:
    WeaponTemplateSetHead() { memset(m_bits, 0, sizeof(m_bits)); }
    __declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
    void rva000B3EC7();
    void rva000B3ED3(const WeaponTemplateSetHead &other);
    void rva000B3FA5(int bit, int value);
    WeaponTemplateSetHead rva0045D859() throw();

    void clear() { memset(m_bits, 0, sizeof(m_bits)); }
    void set(unsigned int bit) { m_bits[bit >> 5] |= 1U << (bit & 31); }

    unsigned int m_bits[19];
};

#endif

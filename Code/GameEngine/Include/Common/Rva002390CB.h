// Target facts: retail default constructor RVA 0x004CEE6E writes -1 at +0 and zero at +4; copy constructor RVA 0x002390CB copies the first dword and constructs the four-byte Rva0036CA00Str member at +4 through RVA 0x000A8C7C. Destructor RVA 0x004C9F38 releases the pointer at +4 through RVA 0x00050ED3. None stores a vptr: this class has no virtual functions and no evidenced base.
// Target facts: RVA 0x004151A3 passes stride 8, count 56, copy RVA 0x002390CB and destructor RVA 0x004C9F38 to the vector-copy iterator; RVA 0x00239440 indexes these records by eight bytes. RVA 0x004D9553 places the next record at +8. Size is 8, with neutral four-byte fields m_00 at +0 and m_04 at +4; their original names are unknown.
// Target facts: RVA 0x0027677C calls the default constructor out of line; RVA 0x004D9657 and RVA 0x004D9663 call the copy constructor without intervening EH states. Assignment RVA 0x002C99FB copies +0 and assigns the shared member through RVA 0x00239099; its Rva002390CB spelling is pinned for retail calls at RVAs 0x00374EDA and 0x00374F0A. All special members are declared out of line.
#pragma once
#ifndef BFME2_RVA002390CB_H
#define BFME2_RVA002390CB_H

#include "Rva0036CA00Str.h"

class Rva002390CB
{
public:
    Rva002390CB();
    __declspec(nothrow) Rva002390CB(const Rva002390CB &other);
    ~Rva002390CB();
    Rva002390CB &operator=(const Rva002390CB &other);

    int m_00;
    Rva0036CA00Str m_04;
};

#endif

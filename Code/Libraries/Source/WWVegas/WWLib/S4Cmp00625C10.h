// Target facts (BFME2 RVAs): 0x006260B0/0x006260C0 and 0x006269B9/0x006269BD copy the comparator as one four-byte word; 0x00626760/0x0062676C passes the same word to 0x006265B0. Its representation is four bytes at +0, with no base storage or virtual functions.
// 0x00625C31..0x00625C3D and 0x006265E0..0x006265EB inline a strict greater-than comparison of the element's float at +4 (unordered compares false). No constructor, destructor or operator() row names S4Cmp00625C10; copies stay trivial and operator() stays inline.
// The ledger's US4Cmp00625C10@@ spelling fixes struct. m_bfmeState is a project placeholder, and void* is only a four-byte carrier: retail forwards it without dereferencing it, so its meaning and pointee type are unknown.

#pragma once

#ifndef BFME2_S4CMP00625C10_H
#define BFME2_S4CMP00625C10_H

#include "S4SortElem8.h"

struct S4Cmp00625C10
{
    void *m_bfmeState;

    bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
    {
        return a.m_bfmeKey > b.m_bfmeKey;
    }
};

#endif

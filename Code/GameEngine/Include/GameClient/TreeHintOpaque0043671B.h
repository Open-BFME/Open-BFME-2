// Target facts (addresses are retail RVAs unless marked VA):
// TreeHintOpaque0043671B has no virtual functions or bases. Copy 0022D106
// calls UnicodeString's base copy 00037050 at +0 and 0022CE19 at +4,
// then copies dwords +DEC/+DF0. Destructor 00229840 calls 002DD1E9 at +4
// and UnicodeString cleanup 00036E70 at +0; neither body stores a vptr.
// Constructor 00229811 zeroes +0 and calls 002DD173 at +4. Allocation
// 00401FCD requests DF4 bytes before calling it at 00401FE4; 002DE4E3
// returns with RET DF4. The +4 member therefore occupies DE8 bytes.
// Assignment 00401F76 calls 00037150 at +0 and 002DDC76 at +4, then
// copies +DEC/+DF0. These owning operations are declared out of line.
// The ledger spells the outer record and member as structs. Field names below are neutral.
#pragma once
#ifndef __BFME2_TREEHINTOPAQUE0043671B_H_
#define __BFME2_TREEHINTOPAQUE0043671B_H_

#include "BfmeSubobject0022CE19.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

struct TreeHintOpaque0043671B
{
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    TreeHintOpaque0043671B &operator=(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();

    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC;
    unsigned int m_wordDF0;
};

typedef char BfmeTreeHintMemberExtent[(sizeof(BfmeSubobject0022CE19) == 0xDE8) ? 1 : -1];
typedef char BfmeTreeHintExtent[(sizeof(TreeHintOpaque0043671B) == 0xDF4) ? 1 : -1];

#endif

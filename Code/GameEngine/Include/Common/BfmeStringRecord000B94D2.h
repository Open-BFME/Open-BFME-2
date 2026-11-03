// Target facts (retail RVAs): copy constructor 0x000B94D2 calls StringBase<char> copy 0x000365F0 at +0/+4; destructor 0x000B6CF1 calls releaseBuffer 0x00036410 at +4 then +0. Neither installs a vptr; this record has no virtual functions or evidenced base class, and no constructor/destructor vftables to reconcile.
// Target facts: copy worker 0x000BBAA1 and destruction worker 0x000BDCD6 advance by eight bytes, proving sizeof 8; resize 0x000C4733 divides by eight and destroys its eight-byte value through 0x000B6CF1. The two four-byte string members occupy +0/+4; their application names are unknown.
// Target facts: resize wrapper 0x000C4D34 and parser 0x000C3824 inline two zero stores for default construction. Worker 0x000B97BC calls copy constructor 0x000B94D2, and parser 0x000C3824 calls destructor 0x000B6CF1 out of line; those rowed methods remain declarations.
#pragma once

#ifndef __BFME2_BFMESTRINGRECORD000B94D2_H_
#define __BFME2_BFMESTRINGRECORD000B94D2_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct BfmeStringRecord000B94D2
{
    BfmeStringRecord000B94D2() {}
    BfmeStringRecord000B94D2(const BfmeStringRecord000B94D2 &other);
    ~BfmeStringRecord000B94D2();

    AsciiString m_s0;
    AsciiString m_s1;
};

#endif

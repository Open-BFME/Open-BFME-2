// Target facts (BFME2 1.06; code addresses are RVAs):
// 0x000A780A stores the unsigned argument at +0 and calls StringBase<char>'s copy constructor 0x000365F0 at +4; 0x000CF475 copies the same two fields. Neither stores a vptr or constructs a base: this is a nonvirtual struct with no parent or virtual functions.
// 0x000A799B allocates a 0x18-byte tree node and constructs its value at +0x10 through 0x000A7876, which calls 0x000CF475. The key is 8 bytes; vector constructor 0x0043355F independently divides its byte span by 8.
// 0x000A795B passes node+0x10 to destructor 0x0029D7C2, which advances this by 4 and tail-calls StringBase<char>::releaseBuffer (0x00036410). The +4 member owns an AsciiString; +0 is data, not a vptr.
// 0x000A7EC3 and 0x000A816B call the unsigned/string constructor; 0x000A7892 calls the copy constructor. These constructors and the destructor remain out of line.
// Ledger comparator 0x00240CE0 uses signed comparisons at +0; Rva000A78A3Less (0x000A78A3) uses unsigned comparisons. Both compare the +4 strings through 0x0005598C. These are separate free functions, not virtual slots.
// Member labels denote offsets; retail does not establish original application names.

#pragma once

#ifndef BFME2_TREEKEY00242F5E_H
#define BFME2_TREEKEY00242F5E_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct TreeKey00242F5E
{
    unsigned int field00;
    AsciiString field04;

    TreeKey00242F5E(unsigned int, AsciiString);
    TreeKey00242F5E(const TreeKey00242F5E &);
    ~TreeKey00242F5E();
};

bool operator<(const TreeKey00242F5E &, const TreeKey00242F5E &);
bool __stdcall Rva000A78A3Less(const TreeKey00242F5E &, const TreeKey00242F5E &);

#endif

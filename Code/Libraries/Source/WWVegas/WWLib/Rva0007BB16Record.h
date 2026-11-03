// Target facts (retail RVAs): 0x0007C2D7 calls destructor 0x0007BB16 and steps 0x24 bytes; 0x00151E4D calls assignment 0x00151336 with the same stride, proving sizeof 0x24.
// 0x001513AD zeros the string handles at +0/+8 before calling 0x00151336; 0x0007BB16 releases +8 then +0 through 0x00036410. Neither body stores a vptr, and the copy preserves no vptr: this record has no virtual functions or base subobject. 0x00151248 clears +4, +0x0C (16 bytes), +0x1C (4 bytes), and +0x20 (1 byte).
// 0x001527D9 reads float +0x0C; 0x001527F5-0x0015282E transfers up to four floats from +0x0C; 0x0015283B reads int +0x1C; 0x0015284E reads bool +0x20. 0x00151336 copies these blocks separately and leaves +0x21..+0x23 as padding; m_tail0C is opaque aligned storage for that entire tail, not six recovered integer fields. SetName at 0x00151243 jumps to StringBase<char>::set at 0x000055F5. Constructors 0x00151597/0x001512F1 and assignment 0x00151336 have other ledger owner spellings; all special members are declared out of line.

#pragma once

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct Rva0007BB16Record
{
    Rva0007BB16Record();
    Rva0007BB16Record(const char *, int);
    Rva0007BB16Record(const Rva0007BB16Record &);
    ~Rva0007BB16Record();
    Rva0007BB16Record &operator=(const Rva0007BB16Record &);

    void SetName(const char *);

    AsciiString m_00;
    int m_04;
    AsciiString m_08;
    int m_tail0C[6];
};

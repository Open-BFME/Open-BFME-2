// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ??1Rva003B39C7@@QAE@XZ @0x002045AB 103B: non-virtual dtor of Rva003B39C7.
// Evidence: caller 0x00206DFF builds Rva003B39C7 at [ebp-0x8c] via ctor
// 0x003B39C7 then INI::initFromINI then calls this body; sibling caller
// 0x00206E63 same; jmp at 0x00204D66. Layout follows Rva003B39C7Ctor.cpp:
// int +0x00, AsciiString +0x04/+0x08/+0x0C, ints +0x10/+0x14, AsciiString[12]
// +0x18 via ehvec dtor 0x0048BA39 count 12 size 4, ints +0x48/+0x4C[12],
// AsciiString +0x7C (retail calls releaseBuffer 0x00036410 there, so the
// ctor TU's int m7C view is refined here). No vptr store: non-virtual.

#include "ascii_string.h"

struct Rva003B39C7
{
    int m00; // +0x00
    AsciiString m04; // +0x04
    AsciiString m08; // +0x08
    AsciiString m0C; // +0x0C
    int m10; // +0x10
    int m14; // +0x14
    AsciiString m18[12]; // +0x18
    int m48; // +0x48
    int m4C[12]; // +0x4C
    AsciiString m7C; // +0x7C
    ~Rva003B39C7();
};

Rva003B39C7::~Rva003B39C7() {}

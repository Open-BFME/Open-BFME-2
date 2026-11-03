// Target facts (RVAs; table addresses are VAs): the ledger names the nested Impl constructor at 0x0056D438; 0x0056D5D7 allocates 0x38 bytes and 0x0056D602 calls it. Impl has no virtual functions or base: its constructor stores the owner at +0, copies UnicodeStrings at +4/+8/+0xC/+0x10 through 0x00037050, and installs no vptr; teardown 0x0056C996 releases those strings and five DisplayStrings without a vptr store or base call.
// Target layout: 0x0056D48D and 0x0056D515 write the 16-bit +0x14 field; 0x0056D491 and 0x0056CA4E write the 32-bit +0x18 field. Constructor stores 0x0056D4A3, 0x0056D4B1, 0x0056D4BF, 0x0056D4CD and 0x0056D4E3 place DisplayStrings at +0x1C..+0x2C; 0x0056D501 and 0x0056D577 store the const Image pointers returned by 0x002D92F6 at +0x30/+0x34. No semantic field names are asserted.
// Target dispatch: the separate owner Rva0056D3FD stores VA 0x00C6DAA4 at 0x0056D5D9/0x0056D40E; its slots are 0x0056D61F, 0x0056D2BD and 0x0056D2C5. The latter two load its +8 Impl pointer then jump to 0x0056CA31/0x0056CCE2. Base teardown 0x004E84A4 restores VA 0x00BC6F20 on that owner, not Impl. Rowed Impl methods are ComputeIconSizes 0x0056C7F1, SetWidthAndComputeHeight 0x0056CA31, Render 0x0056CCE2 and SetupDisplayStrings 0x0056D2E9; all are called directly. The outer declaration supplies their ledger scope, without a second owner layout.

#pragma once
#ifndef BFME2_INGAMECOMMANDBUTTONHELP_H
#define BFME2_INGAMECOMMANDBUTTONHELP_H

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class AsciiString;
class DisplayString;
class Image;
class Rva0056D3FD;
struct FloatPair;

class InGameCommandButtonHelp
{
public:
    class Impl;
};

class InGameCommandButtonHelp::Impl
{
public:
    Impl(Rva0056D3FD *owner, const UnicodeString &a, const UnicodeString &b,
        const UnicodeString &c, const UnicodeString &d, const AsciiString &imageSuffix);
    ~Impl();

    void ComputeIconSizes(FloatPair *a, FloatPair *b, FloatPair *out);
    int SetWidthAndComputeHeight(int width);
    void Render(const FloatPair &position, const FloatPair &size);
    void SetupDisplayStrings();

    Rva0056D3FD *m_00;
    UnicodeString m_04;
    UnicodeString m_08;
    UnicodeString m_0C;
    UnicodeString m_10;
    unsigned short m_14;
    int m_18;
    DisplayString *m_1C;
    DisplayString *m_20;
    DisplayString *m_24;
    DisplayString *m_28;
    DisplayString *m_2C;
    const Image *m_30;
    const Image *m_34;
};

typedef char InGameCommandButtonHelpImplSize[(sizeof(InGameCommandButtonHelp::Impl) == 0x38) ? 1 : -1];

#endif

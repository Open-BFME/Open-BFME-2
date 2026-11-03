// Target facts: BFME2 1.06 SubTitleWindow has no virtual functions or base class.
// RVA 0x00260865 constructs it; 0x00260A3C destroys it. Neither stores a vftable.
// RVA 0x00047FCD and 0x00051437 allocate 0x6C bytes before calling 0x00260865.
// The constructor stores DisplayString* at +0 (0x00260885, 0x00260A1F) and
// GameFont* at +4 (0x00260887), then constructs the vector at +8 through
// 0x00211E58 (0x0026087E..0x0026088A). Its three pointers occupy +8/+C/+10.
// The destructor calls the record-vector destructor 0x00260826 at this+8
// (0x00260AC0..0x00260AC3); the shared unwind action 0x00772D10 does the same.
// RVA 0x00045837 reads +0x14 and divides the +C minus +8 span by eight.
// RVA 0x00260BBF copies a UnicodeString and the color argument into an eight-byte
// record (0x00260CF8..0x00260D21), then appends it to the vector at this+8.
// RVA 0x00260898..0x002608CA writes four-byte fields +14 through +40, including
// the arrays +34/+38 (allocated at 0x002608FF..0x00260918). Array +34 holds
// DisplayString* (0x00260925..0x00260939); +24 is their signed count.
// RVA 0x00260762..0x0026076A copies each record's color word to array +38.
// RVA 0x002608CD..0x002608FA stores floats at +44,+48,+4C,+50,+54,+58,+5C,+60,
// +64,+68. RVA 0x00260BCF..0x00260BD9 reads +64 and +5C as floats.
// The ledger names rva00045837 (0x00045837) and rva00260BBF (0x00260BBF);
// 0x00047F93 calls the nonvirtual destructor and 0x00048000 calls the constructor.

#pragma once

#ifndef __BFME2_SUBTITLEWINDOW_H_
#define __BFME2_SUBTITLEWINDOW_H_

#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class DisplayString;
class GameFont;

class SubTitleWindow
{
public:
    SubTitleWindow(GameFont *, float, float, int, int, int, int);
    ~SubTitleWindow();
    bool rva00045837() const;
    void rva00260BBF(const StringBase<unsigned short> &, unsigned int);

private:
    struct Record
    {
        UnicodeString field00;
        unsigned int field04;
    };

    DisplayString *field00;
    GameFont *field04;
    Record *field08;
    Record *field0C;
    Record *field10;
    int field14;
    int field18;
    int field1C;
    int field20;
    int field24;
    int field28;
    int field2C;
    int field30;
    DisplayString **field34;
    unsigned int *field38;
    int field3C;
    int field40;
    float field44;
    float field48;
    float field4C;
    float field50;
    float field54;
    float field58;
    float field5C;
    float field60;
    float field64;
    float field68;
};

#endif

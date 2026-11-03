// Target facts (code addresses are RVAs): owner constructor 0x005D4DA9 constructs the registered 0x10-byte Rva00330757Member at +4 (call 0x005D4DBE) before storing VA 0x00C75AAC at +0 (0x005D4DC9); using that nonpolymorphic storage as a base represents this order. Owner destructor 0x005D4C61 restores the same table at 0x005D4C73. Its two entries are deleting destructor 0x005D4E06 and float callback 0x005D4C48; VA 0x00C75AB4 starts the non-code string "_OnPosChanged". Allocations at 0x0057B51A and 0x005F3916 request 0x18 bytes before calls at 0x0057B55B and 0x005F3957 to 0x005D4DA9. The implementation pointer is stored at +0x14 by 0x005D4DF5.
// Target facts: the separate implementation is allocated with 0x28 at 0x005D4DC7 and constructed by 0x005D4CBB at 0x005D4DE9. It has no virtual functions, base-class table or vptr stores: +0 holds the owner argument (0x005D4CD3), +4 the level (0x005D4CE0), +8 an AsciiString copied by 0x005D4CE3, +0x0C the registered 0x0C-byte Rva0052413E constructed at 0x005D4CF1, floats at +0x18/+0x1C/+0x20 (0x005D4CFD..0x005D4D07) and bools at +0x24/+0x25 (0x005D4D0C/0x005D4D10). Nonvirtual destructor 0x005D4913 destroys +0x0C at 0x005D492B and +8 at 0x005D4937; 0x005D49DD is a nonvirtual deletion helper, not an implementation table slot. Callback 0x005D4867 stores +0x20 and calls owner slot 1 at 0x005D48B6.
// Target facts: the named implementation rows are SetEnabled 0x005D4949, SetVisible 0x005D498B, SetPageSize 0x005D4AD0, SetLineSize 0x005D4B1F and SetPos 0x005D4B6E. Owner forwarders 0x005D49CD/0x005D49D5 and 0x005D4BAE/0x005D4BC1/0x005D4BD4 load +0x14 and call those bodies. Lifetime rows retain neutral ledger owners Rva005D4C61 and Rva005D4913; the owner/implementation relationship follows their allocation, argument and forwarding bytes. Lifetimes and named methods remain declarations; the unnamed virtual callback and storage use neutral names.
#pragma once

#ifndef BFME2_GAMECLIENT_APTSCROLLBAR_H
#define BFME2_GAMECLIENT_APTSCROLLBAR_H

#include "../Common/Rva00330757Member.h"
#include "../Common/Rva0052413E.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class AptScrollBar : public Rva00330757Member
{
public:
    class Impl;

    AptScrollBar(int level, const AsciiString &name);
    virtual ~AptScrollBar();
    virtual void vslot01(float position);

private:
    Impl *field14;
};

class AptScrollBar::Impl
{
public:
    Impl(AptScrollBar *owner, int level, const AsciiString &name);
    ~Impl();

    void SetEnabled(bool value);
    void SetVisible(bool value);
    void SetPageSize(float value);
    void SetLineSize(float value);
    void SetPos(float value);

private:
    AptScrollBar *field00;
    int field04;
    AsciiString field08;
    Rva0052413E field0C;
    float field18;
    float field1C;
    float field20;
    bool field24;
    bool field25;
};

typedef char AptScrollBarSizeCheck[sizeof(AptScrollBar) == 0x18 ? 1 : -1];
typedef char AptScrollBarImplSizeCheck[sizeof(AptScrollBar::Impl) == 0x28 ? 1 : -1];

#endif

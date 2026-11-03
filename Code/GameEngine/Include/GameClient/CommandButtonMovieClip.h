// Target facts (code addresses are RVAs; tables are VAs): constructor 0x005E1627 clears +4, installs 0x00C77998 at +0 and stores an Impl pointer at +8. Derived constructor 0x005E1680 calls it at +0 and starts its own fields at +0x0C and +0x10, establishing a 0x0C-byte nonvirtual prefix. The separate Impl allocation is 0x44 bytes (0x005E1641/0x005E1649), constructed by 0x005E136C; it is not this object's size.
// Table 0x00C77998 has seven slots before the derived table at 0x00C779B4: deleting destructor 0x005E1334, four copies of 0x005E0D94, then two copies of 0x000B3FD0 (RET). Callback 0x005E0CEB calls slots 1..4 without arguments; 0x005E0D27/0x005E0D31 call slots 5/6. The derived table's slot 5 is the rowed CommandButtonMovieClipWithHelp::OnRollOver (0x005E1193), establishing that override's name.
// Destructor 0x005E129B (ledger Rva005E129B) restores 0x00C77998, clears the owning Impl pointer through 0x005E1246 at +8, then restores the registered Rva0007DF07 parent's 0x00BC6F20 table. Constructor unwind 0x007A3292 calls its destructor 0x004E84A4; parent constructor 0x0007DF07 clears +4 and installs 0x00BC6F20. This is a polymorphic class with an 8-byte parent and no virtual bases; its lifetime methods remain declarations.

#pragma once

#ifndef BFME2_COMMANDBUTTONMOVIECLIP_H
#define BFME2_COMMANDBUTTONMOVIECLIP_H

#include "../Common/Rva0007DF07.h"

class AptMovieClipFrame;
class AsciiString;

namespace StrategicHUD
{

class CommandButtonMovieClip : public Rva0007DF07
{
public:
    class Impl;

    CommandButtonMovieClip(AptMovieClipFrame *frame, const AsciiString &instance);
    virtual ~CommandButtonMovieClip();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void OnRollOver();
    virtual void vslot6();

private:
    Impl *m_impl;
};

}

using StrategicHUD::CommandButtonMovieClip;

#endif

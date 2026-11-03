// Target facts (code addresses are RVAs; tables are VAs): constructor 0x005FDE24 stores 0x00C7A2E8 at 0x005FDE34 and an Impl pointer at +4 at 0x005FDE63. Its allocation at 0x005FDE3A is 0x50 bytes for the separate Impl constructed by 0x005FDA39. It calls no parent constructor and installs no other subobject table. Derived constructor 0x005F4E48 calls this constructor at 0x005F4E8B, writes its own member at +8 at 0x005F4EB3 and installs 0x00C794E4 at 0x005F4EB6, bounding this base to sizeof 8; the derived allocation at 0x005F4F06 is 0x0C bytes.
// Target facts: destructor 0x005FD9FF restores the same 0x00C7A2E8 table, adds 4 to this and tail-calls the pointer cleanup 0x005FD95E. That cleanup clears the pointer and calls Impl::~Impl at 0x005FD628 before deleting it. Table 0x00C7A2E8 (RVA 0x0087A2E8) contains six slots, beginning with the scalar deleting destructor 0x005FDA1D, which calls 0x005FD9FF. Slots 1 through 5 contain the shared RET at 0x000B3FD0; string data begins immediately after them at RVA 0x0087A300.
// Target facts: the ledger names slots 1 through 5 notifyClosed, notifyExit, notifyMoveDown, notifyMoveUp and notifySwap. Impl callbacks 0x005FD3FF, 0x005FD416, 0x005FD434, 0x005FD452 and 0x005FD470 call these owner slots at table offsets +4, +8, +0x0C, +0x10 and +0x14 without arguments. The constructor and destructor rows place the class in namespace StrategicHUD and establish the constructor parameter types; these methods and the notifications are declared out of line.
#pragma once

#ifndef BFME2_ARMY_UNIT_SWAPPER_MOVIE_CLIP_H
#define BFME2_ARMY_UNIT_SWAPPER_MOVIE_CLIP_H

class AsciiString;
struct TreeHintRef00217D4C;

namespace StrategicHUD
{
class ArmyUnitSwapperMovieClip
{
public:
    class Impl;

    ArmyUnitSwapperMovieClip(int level, const AsciiString &name, const TreeHintRef00217D4C &top, const TreeHintRef00217D4C &bottom);
    virtual ~ArmyUnitSwapperMovieClip();
    virtual void notifyClosed();
    virtual void notifyExit();
    virtual void notifyMoveDown();
    virtual void notifyMoveUp();
    virtual void notifySwap();

private:
    Impl *m_impl;
};
}

using StrategicHUD::ArmyUnitSwapperMovieClip;

typedef char ArmyUnitSwapperMovieClipSizeCheck[sizeof(ArmyUnitSwapperMovieClip) == 8 ? 1 : -1];

#endif

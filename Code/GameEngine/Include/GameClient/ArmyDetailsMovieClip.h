// Target facts (code RVAs; table VAs): the ledger names StrategicHUD::ArmyDetailsMovieClip; constructor 0x005F3E93 stores 0x00C7936C at +0 (0x005F3EA3), constructs a separate 0x5C-byte Impl through 0x005F39D6, and stores its pointer at +4 (0x005F3ED2). No parent constructor or vbptr is present.
// Table 0x00C7936C has three slots before string data at 0x00C79378: deleting destructor 0x005F39BA, then two copies of RET 0x000B3FD0. Destructor 0x005F38CA restores this same table and clears the +4 owner through 0x005F35D3. Ledger notification rows and callbacks 0x005F2537/0x005F255E prove the names and no-argument calls in slots 1/2.
// The object's footprint is 8 bytes: its own writes reach +7, and derived constructor 0x005F6806 calls 0x005F3E93 at +0 before storing its additional owned pointer at +8 (0x005F6859). Constructor 0x005E54D5 and destructor 0x005E54AE install 0x00C77D10 for a derived class; that table is not ArmyDetailsMovieClip's. Lifetime methods and notification bodies are declared out of line.
#pragma once

#ifndef BFME2_ARMY_DETAILS_MOVIE_CLIP_H
#define BFME2_ARMY_DETAILS_MOVIE_CLIP_H

class AsciiString;

namespace StrategicHUD
{
class ArmyDetailsMovieClip
{
public:
    class Impl;

    ArmyDetailsMovieClip(int level, const AsciiString &name, int layout, bool backButtonVisible);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();

private:
    Impl *m_impl;
};
}

using StrategicHUD::ArmyDetailsMovieClip;

typedef char ArmyDetailsMovieClipSizeCheck[sizeof(ArmyDetailsMovieClip) == 8 ? 1 : -1];

#endif

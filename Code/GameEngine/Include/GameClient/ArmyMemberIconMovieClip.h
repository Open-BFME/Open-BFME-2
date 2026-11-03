// Target facts (code RVAs, table VAs): constructor 0x005FCEA9 clears +4 (0x005FCEB8), constructs the registered Rva00330757Member at +8 (0x005FCEC6), installs 0x00C7A1BC (0x005FCED1), and stores its implementation pointer at +0x18 (0x005FCEFD). Hero constructor 0x005FCF75 adds no storage; factory 0x005F43B4 allocates 0x1C bytes for it. ArmyMemberIconMovieClip's footprint is 0x1C; the implementation allocation at 0x005FCECB is a separate 0x38-byte object.
// Table 0x00C7A1BC has five virtual slots: deleting destructor 0x005FCF59, update 0x005FC9F8, notifyClicked 0x005FCAE4, notifyRollOut 0x005FCAF3, notifyRollOver 0x005FCB02. The next table, 0x00C7A1D0, belongs to the hero constructor. Destructor 0x005FCF0E restores 0x00C7A1BC at 0x005FCF1F and later 0x00BC6F20 at 0x005FCF49; the latter is the registered Rva0007DF07 base table (constructor 0x0007DF07, destructor 0x004E84A4, deleting destructor 0x0007E5EE). No vbptr is stored.
// The notification ledger rows prove slots 2..4; ArmyUnitIconMovieClip::DoUpdate 0x005FD197 calls 0x005FC9F8 at 0x005FD1A0, proving the base update declaration. Forwarder 0x005FC9E0 reads +0x18 and jumps to Impl::SetPortraitImage 0x005FC762. The constructor row spells namespace StrategicHUD and its parameter types. The nonvirtual +8 subobject occupies 0x10 bytes: its constructor 0x00330757 writes through +0x0C, and owner construction places the next field at +0x18; its destructor 0x0007FAB3 frees its first pointer without a table store.
#pragma once

#ifndef BFME2_ARMY_MEMBER_ICON_MOVIE_CLIP_H
#define BFME2_ARMY_MEMBER_ICON_MOVIE_CLIP_H

#include "../Common/Rva0007DF07.h"
#include "../Common/Rva00330757Member.h"

class AptMovieClipFrame;
class AsciiString;
class Image;

namespace StrategicHUD
{
class ArmyMemberIconMovieClip : public Rva0007DF07, public Rva00330757Member
{
public:
    class Impl;

    ArmyMemberIconMovieClip(AptMovieClipFrame *frame, const AsciiString &type);
    virtual ~ArmyMemberIconMovieClip();
    virtual void DoUpdate();
    virtual void notifyClicked();
    virtual void notifyRollOut();
    virtual void notifyRollOver();
    void rva005FC9E0(const Image *image);

private:
    Impl *m_impl;
};
}

using StrategicHUD::ArmyMemberIconMovieClip;

typedef char ArmyMemberIconMovieClipSizeCheck[sizeof(ArmyMemberIconMovieClip) == 0x1C ? 1 : -1];

#endif

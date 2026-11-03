/* Target facts (code and table addresses are RVAs unless marked VA): Constructor 0x005CD651 (rowed as Rva005CD651) stores VA 0x00C74FF4 at +0 at 0x005CD66D, its argument at +4 at 0x005CD673, zero at +8 at 0x005CD669 and true at byte +0x0C at 0x005CD676. ResolveBattlesBehavior constructs this member at +0x30 at 0x00576E86/0x00576E89 and stores its next word at +0x40 at 0x00576E8E; PlanRetreatsPhaseBehavior constructs it at +0x28 at 0x0057771D/0x00577720 and stores its next byte at +0x38 at 0x0057772B. The vptr, two words and flag therefore occupy 0x10 bytes with four-byte alignment.
   Destructor 0x005CD6A9 restores the class table at 0x005CD6BA, accesses pointer +8 at 0x005CD6C9 and restores the primary base table VA 0x00C6E330 at 0x005CD6DC. The class table 0x00874FF4 has five slots: 0x005CD6EC, 0x005CD649 and three copies of 0x0047A69C (RET 4). Constructor 0x005CD7B4 installs the next table at 0x00875008. The base table 0x0086E330 contains five RET 4 callbacks and ends at the separately installed table 0x0086E344 (store 0x00574265); base constructor 0x005E1871 installs 0x0086E330. Neither table contains a deleting destructor. The destructor is nonvirtual; the unregistered base's five primary slots are represented directly here.
   Ledger method OnObjectivesButtonLeftClicked (0x005CD649, slot 1) calls rva005CD625 (0x005CD625), which tests byte +0x0C at 0x005CD625. rva005CD690 (0x005CD690) calls that same predicate for message type 0x6F. Its enclosing translators pass the same members at +0x40/+0x30/+0x28 (0x00575C41/0x00576694/0x00577220). Slot 0 is the rowed rva005CD6EC (RET 4); the remaining callbacks use neutral names and one unused argument word. Field names and the original base identity are unproved. */
#pragma once

#ifndef BFME2_PLAYERSTATUSDISPLAYER_H
#define BFME2_PLAYERSTATUSDISPLAYER_H

class GameMessage;
class Rva005CD649Button;
enum GameMessageDisposition;

namespace StrategicInGameUI
{
class PlayerStatusDisplayer
{
public:
    PlayerStatusDisplayer(int value);
    ~PlayerStatusDisplayer();

    virtual void rva005CD6EC(int value);
    virtual void OnObjectivesButtonLeftClicked(Rva005CD649Button &button);
    virtual void slot02(int value);
    virtual void slot03(int value);
    virtual void slot04(int value);

    GameMessageDisposition rva005CD690(const GameMessage *message);
    bool rva005CD625();

private:
    int m_field04;
    void *m_field08;
    bool m_field0C;
};
}

using StrategicInGameUI::PlayerStatusDisplayer;

#endif

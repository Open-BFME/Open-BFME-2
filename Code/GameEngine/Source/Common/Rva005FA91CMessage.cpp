// cl: /MD
// ?OnSwapButtonLeftClicked@Rva005FA91C@@QAEXH@Z, RVA 0x005FA91C, 96 bytes.
// Builds GameMessage type 0x6B4 via MessageStreamSubsystem slot 0x48 and
// appends five ints: [[this+4]+0x14]+0x34, [this+4]+0x18, [this+4]+0x1C,
// entries[idx].key at this+idx*8+0x34, entries[idx+1].key at this+idx*8+0x3C.
// Evidence: same +0x34 stride-8 array as find 0x005FA8F5; callees rowed
// appendIntegerArgument 0x30F936; global MessageStreamSubsystem.
#include "../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;
struct Inner005FA91C {
    char m_pad[0x34];
    int m_val34;
};
struct Outer005FA91C {
    char m_pad[0x14];
    Inner005FA91C *m_ptr14;
    int m_val18;
    int m_val1C;
};
struct Rva005FA91CEntry {
    int m_key;
    int m_val;
};
struct Rva005FA91C {
    char m_pad0[4];
    Outer005FA91C *m_ptr4;
    char m_pad8[0x2C];
    Rva005FA91CEntry m_entries[3];
    int m_count;
    void OnSwapButtonLeftClicked(int idx);
};
void Rva005FA91C::OnSwapButtonLeftClicked(int idx)
{
    GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_LW_SWAP_ARMIES_IN_BATTLE);
    msg->appendIntegerArgument(m_ptr4->m_ptr14->m_val34);
    msg->appendIntegerArgument(m_ptr4->m_val18);
    msg->appendIntegerArgument(m_ptr4->m_val1C);
    msg->appendIntegerArgument(m_entries[idx].m_key);
    msg->appendIntegerArgument(m_entries[idx + 1].m_key);
}

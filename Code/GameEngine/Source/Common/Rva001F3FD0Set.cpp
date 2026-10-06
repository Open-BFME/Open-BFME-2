// cl: /Ireference/shims/bfme2_ascii /MD
// ?set@Rva001F3FD0Slot@@QAEXABVAsciiString@@@Z @0x001F3FD0 26B.
// Sets AsciiString at +0x68 via pinned ??4AsciiString@@QAEAAV0@ABV0@@Z then
// zeroes dword at +0xa0. Ghidra names it setSlaveSystemName; offset +0x68
// matches BFME1 slave-name slot. Honest Rva name; /O1 for push-arg plus
// and [m],0 idiom.
#include "ascii_string.h"
class Rva001F3FD0Slot {
public:
    void set(const AsciiString &other);
    char m_lead[0x68];
    AsciiString m_str;
    char m_pad[0xa0 - (0x68 + 4)];
    int m_a0;
};
void Rva001F3FD0Slot::set(const AsciiString &other)
{
    m_str = other;
    m_a0 = 0;
}

// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva003FF5F2@GameSlot@@QAEXABVAsciiString@@@Z @0x003FF5F2 36B
// GameSlot AsciiString setter at +0x1a8: rowed-pin AsciiString assign
// 0x000366F0 then rowed StringBase trim 0x00037CF0 then rowed toUpper
// 0x00036B60 just landed; callers 0x005A1A0B 0x005A42BF 0x005A5180.
#include "ascii_string.h"


class GameSlot {
public:
    void rva003FF5F2(const AsciiString &other);
private:
    char _pad[0x1a8];
    AsciiString m_name;
};

void GameSlot::rva003FF5F2(const AsciiString &other)
{
    m_name = other;
    m_name.trim();
    m_name.toUpper();
}

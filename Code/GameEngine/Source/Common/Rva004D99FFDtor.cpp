// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva004D99FF@@QAE@XZ @0x004D99FF 54B. Dtor releases AsciiStrings at +0x18 and +0x1C via rowed releaseBuffer 0x00036410 with EH prolog.
// Evidence: retail EH_prolog lea ecx [esi+0x1C] call releaseBuffer lea ecx [esi+0x18] call releaseBuffer; callers 0x004DAA8B Unwind 0x007913A9.
#include "ascii_string.h"
class Rva004D99FF {
public:
    ~Rva004D99FF();
private:
    char m_pad[0x18];
    AsciiString m_18;
    AsciiString m_1c;
};
Rva004D99FF::~Rva004D99FF() {}

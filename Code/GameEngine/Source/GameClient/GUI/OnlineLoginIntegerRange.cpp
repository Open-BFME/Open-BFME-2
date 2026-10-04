// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Reference: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/GameClient/GUI/OnlineLoginIntegerRange.cpp (whole TU).
// Target: Ghidra RVA 0x0056E6A4, 91 bytes, calls exported AsciiString's
// UnicodeString constructor at 0x38250, atoi, and narrow releaseBuffer at
// 0x36410. Signed comparisons establish inclusive integer bounds.
// The OnlineLogin name and source placement come from the donor, not a
// target export. Keep the function address-qualified. Shared BFME2 string
// headers replace the donor's private views without changing its protocol.
#include <stdlib.h>
#include "unicode_string.h"
#include "ascii_string.h"

bool rva0056E6A4(const UnicodeString &text, int minimum, int maximum)
{
    AsciiString narrow(text);
    int parsedValue = atoi(narrow.str());
    if (parsedValue < minimum || parsedValue > maximum)
        return false;
    return true;
}

// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// Donor: Open-BFME-1 RvaStringAccessor.cpp, originally imported at
// 6d9434269164392c5ba62aaa7c15a86b5b020d76; canonical repair reviewed at
// f98983a7d3bb405f1a4ba94bb6a2a168062a819d (18889224, 6de715ca).
// Target evidence: each complete 27-byte accessor copies the four-byte
// narrow string at receiver+0x54 or +0x58 into the caller's return slot,
// using the real StringBase<char> copy constructor at RVA 0x000365F0.
// The shared AsciiString wrapper exposes that exact constructor contract.
// Host names are retained donor address labels; their original identities
// are unknown, and the donor addresses below are not BFME2 addresses.
#include "ascii_string.h"

class Rva001A6F90Host
{
public:
    AsciiString copyStringAt54(void);
};

// BFME2 RVA 0x0027F5C1, 27 bytes.
AsciiString Rva001A6F90Host::copyStringAt54(void)
{
    return *reinterpret_cast<const AsciiString *>(
        reinterpret_cast<const char *>(this) + 0x54);
}

class Rva001A6FC0Host
{
public:
    AsciiString copyStringAt58(void);
};

// BFME2 RVA 0x0027F5DC, 27 bytes.
AsciiString Rva001A6FC0Host::copyStringAt58(void)
{
    return *reinterpret_cast<const AsciiString *>(
        reinterpret_cast<const char *>(this) + 0x58);
}

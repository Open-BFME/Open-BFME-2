// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 30DA0B..30DA25 is a complete 26-byte thiscall RET leaf.
// It tests the one-pointer string at +68 through StringBase<char>::isEmpty
// (rowed1E2F), returning its address if nonempty or the address at +64.
// The canonical AsciiString view provides the same verified one-word storage
// and inline bridge to that exact callee. Field roles below describe this
// selection only; the original entry name, owner and full extent are unknown.
#include "ascii_string.h"
struct Rva0030DA0BStringChoice {
    unsigned char prefix[0x64];
    AsciiString fallback;
    AsciiString preferred;
    const AsciiString &choose() const;
};
const AsciiString &Rva0030DA0BStringChoice::choose() const {
    if (!preferred.isEmpty()) return preferred;
    return fallback;
}

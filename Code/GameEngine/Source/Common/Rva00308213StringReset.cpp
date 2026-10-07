// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Complete 28B leaf 308213..30822F: canonical narrow StringBase setter
// 55F5 receives this+8C and the complete empty literal, then byte9C becomes
// one. This establishes the string operation and offsets; original owner,
// field spellings and allocation extent remain unknown. Borrowed prefix.
#include "string_base.h"
struct Rva00308213StringPrefix {
    unsigned char prefix[0x8C];
    StringBase<char> text;
    unsigned char gap[0xC];
    unsigned char latched9C;
    void clearAndLatch();
};
void Rva00308213StringPrefix::clearAndLatch() {
    text.set("");
    latched9C = 1;
}

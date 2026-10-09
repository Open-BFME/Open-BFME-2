// ?Rva002D56C3Construct@@YA?AVAsciiString@@AAURva002D4688@@@Z
// partial score=1.0 date=2026-10-10
// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
// Native002D56C3..002D5711: complete78B cdecl string-result wrapper.
// Twin source4E2ED9 supplies only the owning-string materialization idiom.
// Target calls106B concat conversion2D511E, rowed copy365F0 and release36410.
// Receiver name retained from rowed writer2D4688; original template unknown.
#include "ascii_string.h"

struct Rva002D4688
{
    operator AsciiString();
};

AsciiString Rva002D56C3Construct(Rva002D4688 &value)
{
    return value;
}

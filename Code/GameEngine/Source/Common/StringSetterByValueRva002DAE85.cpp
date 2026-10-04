// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP=
// BFME1 donor 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/P7ByValueStringSetters.cpp. The entire donor
// was compiled with canonical string headers before selecting this body.
// Donor carries the by-value setter pattern; its application-owner names
// and offsets are BFME1 evidence, not established BFME2 identities.
// Target: Ghidra true entry2DAE85/52, native addECX48 then set366F0 with
// [EBP+8], releaseBuffer36410 of that incoming slot and ret4 establish
// a by-value AsciiString transfer into the receiver's +48 string. The
// native two-state EH frame cleans the argument after assignment or throw.
// Canonical AsciiString uses this same one-pointer StringBase compatibility
// view. Calling the public base setter names the actual native provider.
// Original owner identity is unknown; the prefix records only this offset.
#include "ascii_string.h"
class Rva002DAE85StringOwner
{
public:
    void setText(AsciiString value);
private:
    unsigned char prefix[0x48];
    AsciiString text;
};
void Rva002DAE85StringOwner::setText(AsciiString value)
{
    StringBase<char> &destination = *reinterpret_cast<StringBase<char> *>(&text);
    destination.set(*reinterpret_cast<const StringBase<char> *>(&value));
}

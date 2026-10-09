// cl: /O1 /EHsc /MD /Ireference/shims/bfme2_ascii /arch:SSE
// Native 4E2ED9..4E2F27 is a cdecl string-result wrapper. WB1291420
// confirms conversion followed by StringBase copy and temporary release.
// SplineEffect::SetSubObjectColor at 4E34B1 passes its concatenation node
// here before the RenderObj sub-object query. The conversion owner is the
// existing rowed Rva0020F58E at 20F712 (RegistryAsciiPath.cpp).
// This call view neither constructs nor accesses the node's fields.
// The helper's original name remains unknown; code and EH match retail.
#include "ascii_string.h"

struct Rva0020F58E
{
    operator AsciiString();
};

AsciiString Rva004E2ED9Construct(Rva0020F58E &value)
{
    return value;
}

// ?rva0041541B@Rva0041541B@@QAEABVRva002390CB@@ABVAsciiString@@@Z, retail
// 0x0041541B (97B RET4). The independently pinned lookup: a find in the
// receiver's AsciiString tree at +0x1C0 (rowed _M_find 0x001F8437) returns the
// mapped 8-byte value at node+0x14, else a function-local static
// Rva002390CB at 0x00E03080 with guard 0x00E03088 and _atexit registration
// (rowed Rva002390CB ctor 0x004CEE6E, dtor 0x004C9F38). Caller
// ?rva004D9874@Rva004D97B0@@QAEXABVAsciiString@@@Z (matched) passes the
// reference straight through. The mapped payload is spelled AsciiString so
// the emitted tree find names the rowed AsciiString worker; the 8-byte value
// is recast. The branch shape (== end with the static in the taken path,
// result in the fall-through) is the retail-measured form.
// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native 0x0041541B..0x0041547C (97B) RET4: lookup in the receiver's
// AsciiString tree at +0x1C0; found returns the node payload, else a static
// 8-byte Rva002390CB default at 0x00E03080 with a guard byte at 0x00E03088
// and an atexit destructor registration. The rowed caller
// ?rva004D9874@Rva004D97B0@@QAEXABVAsciiString@@@Z passes the reference
// straight through, so the result is the mapped value (8 bytes).
// stlport
#include <map>

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
#include "../../Include/Common/Rva002390CB.h"

// The mapped payload is spelled AsciiString so the emitted tree find names
// the rowed AsciiString worker at 0x001F8437; the 8-byte value is recast.
class Rva0041541B {
public:
    const Rva002390CB &rva0041541B(const AsciiString &name);
private:
    char m_pad[0x1C0];
    _STL::map<AsciiString, AsciiString> m_tree;
};

const Rva002390CB &Rva0041541B::rva0041541B(const AsciiString &name)
{
    _STL::map<AsciiString, AsciiString>::iterator it = m_tree.find(name);
    if (it == m_tree.end())
    {
        static Rva002390CB s;
        return s;
    }
    return *(const Rva002390CB *)&it->second;
}

// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001EC349@@QAE@XZ @0x001EC349 108B.
// Non-virtual dtor: vector<AsciiString> at +0x18, owning ref at +0x10, four strings at +0xC..+0x00.
// Evidence: callees rowed 0x0002CC70 0x00050ED3 0x00036410(x4); callers at 0x001ECB94 0x001ECFCF 0x001ED30C.
#include <vector>

#include "ascii_string.h"

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
}


#include "OpaqueRefCounted.h"

#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"

class Rva001EC349
{
public:
	~Rva001EC349();
private:
	AsciiString m_00; // +0x00
	AsciiString m_04; // +0x04
	AsciiString m_08; // +0x08
	AsciiString m_0C; // +0x0C
	OpaqueRefElement4 m_10; // +0x10
	int m_14; // +0x14
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_18; // +0x18
};

Rva001EC349::~Rva001EC349()
{
}

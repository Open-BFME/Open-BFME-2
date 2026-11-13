// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ??0Rva005D32D4@@QAE@HABVAsciiString@@@Z @0x005D3628 66B new-wrapper.
// Forwards level and an AsciiString reference to rowed inner ctor 0x005D3506.
// The 4-byte holder whose destructor is 0x005D32D4 (class named after it);
// its caller 0x00578803 passes a const AsciiString reference. Allocation is
// 0x6C, then stores result at +0. No vtable. Address-derived.
#include "../../Include/Common/Rva005D309D.h"

class Rva005D32D4
{
public:
	Rva005D32D4(int level, const AsciiString &name);
protected:
	Rva005D309D *m_0;
};

Rva005D32D4::Rva005D32D4(int level, const AsciiString &name)
	: m_0(new Rva005D309D(level, name))
{
}

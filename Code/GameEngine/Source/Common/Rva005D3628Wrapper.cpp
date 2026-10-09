// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ??0Rva005D3628@@QAE@HH@Z @0x005D3628 66B new-wrapper.
// Forwards level and an AsciiString reference to rowed inner ctor 0x005D3506.
// Legacy HH wrapper symbol retains the machine-word second argument; actual
// caller 0x00578803 supplies a const AsciiString reference. Allocation is 0x6C.
// then stores result at +0. No vtable. Address-derived.
class Rva005D309D
{
public:
	Rva005D309D(int level, const AsciiString &name);
protected:
	unsigned char m_pad[0x6C];
};

class Rva005D3628
{
public:
	Rva005D3628(int a, int b);
protected:
	Rva005D309D *m_0;
};

Rva005D3628::Rva005D3628(int a, int b)
	: m_0(new Rva005D309D(a, *reinterpret_cast<const AsciiString *>(b)))
{
}

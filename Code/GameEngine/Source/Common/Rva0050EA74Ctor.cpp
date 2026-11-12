// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??0Rva0050EA74@@QAE@HABVAsciiString@@@Z @0x0050EA74 69B
// Ctor with vtable 0x0086551C plus int at +8 plus AsciiString at +0xc via
// rowed StringBase copy 0x000365F0 plus zeroed +4 and byte +0x10; ret 8.
#include "../../Include/Common/Rva0050EA74.h"

Rva0050EA74::Rva0050EA74(int a, const AsciiString &asciiString) : m_08(a), m_0c(asciiString)
{
	m_10 = 0;
}

Rva0050EA74::~Rva0050EA74()
{
}

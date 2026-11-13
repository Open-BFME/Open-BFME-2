// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva00221A58@@QAE@ABV0@@Z @0x00221A58 99B
// Copy ctor: AsciiString at +0 +4 +8 via StringBase copies plus
// Rva0022185A at +0xC via its copy plus int at +0x18. Chain after 0x22185A.
// Evidence: retail bytes caller 0x00221B56 unblocks 0x00221B42.
#include "ascii_string.h"

#include "../../Include/Common/Rva0022185A.h"

#include "../../Include/Common/Rva00221A58.h"

Rva00221A58::Rva00221A58(const Rva00221A58 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_18(other.m_18)
{
}

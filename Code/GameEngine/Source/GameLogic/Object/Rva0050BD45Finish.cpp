// ??0Made002CCC90@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG
//
// ??0Made002CCC90@@QAE@XZ retail 0x0050BD45 55B
// Evidence: pin ??0Made002CCC90 (symbols.csv 0x0050BD45); callee base
// Rva00507823 0x0050775B; caller parseLuaEventNugget 0x002CCCB5; sibling
// Made002CC774 0x00509522 (vtable 0x00864520) shares this exact shape.
// vtable 0x00864F78, then +0x128 dword, +0x130/+0x131/+0x132 bytes, and the
// float at +0x12C. ~Made002CCC90 0x0050BD9D releases a StringBase at +0x128,
// so m_128 is an AsciiString whose null buffer pointer is what retail stores
// at +0x128. That non-trivial dtor is also why retail sets the derived vptr
// BEFORE the member stores; the banked attempt modelled +0x128 as a plain int
// and MSVC then sank the vptr store to +0x31, costing 18 bytes. /arch:SSE is
// required for the xorps/movss float zero.
#include "ascii_string.h"

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
private:
	char m_pad[0x128 - 4];
};
class Made002CCC90 : public Rva00507823
{
public:
	Made002CCC90();
	virtual ~Made002CCC90();
private:
	AsciiString m_128;
	float m_12C;
	unsigned char m_130;
	unsigned char m_131;
	unsigned char m_132;
};
Made002CCC90::Made002CCC90()
{
	m_12C = 0.0f;
	m_130 = 0;
	m_131 = 0;
	m_132 = 0;
}
// cl: /O1 /MD /arch:SSE
// ??0Rva004530ED@@QAE@ABV0@@Z @0x004530ED 32B.
// Copy constructor of a 20-byte record (int, 12-byte middle block, int) in the
// Object/Behavior region. Callers 0x00453248, 0x00453BD6, 0x00453C50,
// 0x00453E10 and 0x00453ECE build the object in place (lea ecx,[local] then
// push source), and the body proves the constructor ABI: `mov eax,ecx`
// materializes this in eax before loading the source reference, while the
// middle 12 bytes are copied through an inlined memcpy (three movsd). The
// banked attempt carried a pointer-taking placeholder method name and stalled
// on a two-byte register swap; the bytes only match as the ctor. Identity is
// address-derived.
#include <string.h>
#pragma intrinsic(memcpy)

class Rva004530ED
{
public:
	Rva004530ED();
	Rva004530ED(const Rva004530ED &rhs);
private:
	int m_00;
	float m_04[3];
	float m_10;
};

// ??0Rva004530ED@@QAE@XZ, retail 0x004530D0, 29 bytes.
Rva004530ED::Rva004530ED()
{
	m_00 = 0;
	m_04[0] = 0.0f;
	m_04[1] = 0.0f;
	m_04[2] = 0.0f;
	m_10 = 0.0f;
}

Rva004530ED::Rva004530ED(const Rva004530ED &rhs)
{
	m_00 = rhs.m_00;
	memcpy(m_04, rhs.m_04, 12);
	m_10 = rhs.m_10;
}

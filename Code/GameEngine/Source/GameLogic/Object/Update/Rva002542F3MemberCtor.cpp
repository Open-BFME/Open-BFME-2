// cl: /O1 /arch:SSE /DNDEBUG /MD /GX-
//
// ??0Rva002542F3Member@@QAE@XZ, retail 0x002542F3 (119 bytes).
// Frameless member ctor (InvisibilityNugget at +0x08 in InvisibilityUpdate
// 0x255474, at +0x7C in InvisibilitySpecialPower 0x4C244D, at +0 in wrapper
// 0x4382FC which then stores +0xB8/+0xBC/+0xC0): dword 0 at +0, bitset<128>
// reset at +4 via rowed 0x24CA24, float 0.0 at +0x14, int 2 at +0x18,
// clear80 at +0x1C via rowed 0x1EAE6F, zeros at +0x9C/+0xA0/+0xA4, bitset
// reset at +0xA8, then CRT memset trio (0x10/0x80/0x10). Size 0xB8 proven
// by all three callers (0xC0-0x08, 0x134-0x7C, +0xB8 stores). Recipe:
// FireWeaponCollideModuleDataCtor (reset plus memset pair, /GX- frameless).

#include <string.h>

namespace _STL
{

template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
	bitset<_Bits> &reset();
};

}

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

class Rva002542F3Member
{
public:
	Rva002542F3Member();

private:
	int m_zero00; // +0x00
	_STL::bitset<128> m_bits04; // +0x04
	float m_float14; // +0x14
	int m_int18; // +0x18
	Rva001EAE6FHelper m_buf1C; // +0x1C
	int m_zero9C; // +0x9C
	int m_zeroA0; // +0xA0
	int m_zeroA4; // +0xA4
	_STL::bitset<128> m_bitsA8; // +0xA8
};

Rva002542F3Member::Rva002542F3Member()
{
	m_zero00 = 0;
	m_bits04.reset();
	m_float14 = 0.0f;
	m_int18 = 2;
	m_buf1C.clear80();
	m_zero9C = 0;
	m_zeroA0 = 0;
	m_zeroA4 = 0;
	m_bitsA8.reset();
	memset(&m_bits04, 0, 0x10);
	memset(&m_buf1C, 0, 0x80);
	memset(&m_bitsA8, 0, 0x10);
}

// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
#include "ascii_string.h"

// ??4Rva003B32E5@@QAEAAV0@ABV0@@Z, retail 0x003B32E5, 57 bytes.
// Evidence: __thiscall with one 4-byte arg (ret 4, ecx=this, [esp+0xc]=other);
// copies two dwords at +0/+4, StringBase::set for AsciiString at +8
// (row ?set@?$StringBase@D@@QAEXABV1@@Z), then byte at +0xc, word at +0xe,
// dword at +0x10; mov eax,esi return-this. Callers 0x003B7FE0/0x003B825F pass
// (dst in ecx, src pushed). LINK BONUS: 1 matched file waits for this row.

class Rva003B32E5
{
public:
	Rva003B32E5 &operator=(const Rva003B32E5 &other);

private:
	int m_a;
	int m_b;
	AsciiString m_str;
	unsigned char m_c;
	unsigned short m_d;
	int m_e;
};

Rva003B32E5 &Rva003B32E5::operator=(const Rva003B32E5 &other)
{
	m_a = other.m_a;
	m_b = other.m_b;
	((StringBase<char> *)&m_str)->set(*(const StringBase<char> *)&other.m_str);
	m_c = other.m_c;
	m_d = other.m_d;
	m_e = other.m_e;
	return *this;
}

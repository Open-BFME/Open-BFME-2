// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva005C962C@Rva005C962C@@QAEAAU1@ABU1@@Z, retail 0x005C962C (45B).
// Copy-assignment-like method: AsciiString set at +0 then dword +4 then
// TreeHintRef00217D4C operator= at +8 then dword +0xC returns this.
// Evidence: callees rowed set 0x000366F0 and TreeHintRef op= 0x002174A4;
// caller 0x005C97EF; neighbours Rva0020E89CFetch and treehint setter.
#include "ascii_string.h"

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

struct Rva005C962C
{
	AsciiString m_label;
	int m_04;
	TreeHintRef00217D4C m_hint;
	int m_0c;
	Rva005C962C &rva005C962C(const Rva005C962C &other);
};

Rva005C962C &Rva005C962C::rva005C962C(const Rva005C962C &other)
{
	((StringBase<char> *)&m_label)->set(*(const StringBase<char> *)&other.m_label);
	m_04 = other.m_04;
	m_hint = other.m_hint;
	m_0c = other.m_0c;
	return *this;
}

// cl: /O1 /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0040B707@@QAE@ABV0@@Z @0x0040B707 119B unlock copy ctor with vector ScienceType plus three AsciiStrings plus vector BfmeRecord0040B61A; caller 0x0040B9BB
#include <vector>
#include "ascii_string.h"

enum ScienceType
{
	ScienceType_0
};
struct BfmeRecord0040B61A
{
	char m_bytes[1];
};

class Rva0040B707
{
public:
	Rva0040B707(const Rva0040B707 &o);
private:
	int m_00;
	_STL::vector<ScienceType> m_04;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	_STL::vector<BfmeRecord0040B61A> m_1C;
};

Rva0040B707::Rva0040B707(const Rva0040B707 &o) : m_00(o.m_00), m_04(o.m_04), m_10(o.m_10), m_14(o.m_14), m_18(o.m_18), m_1C(o.m_1C)
{
}

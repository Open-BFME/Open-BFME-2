// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva0021E85A@@QAE@ABV0@@Z @0x0021E85A 250B: copy ctor with five StringBase plus ints plus hero map plus two Science vectors plus int-int map plus long-LadderPref map plus FixedStorage plus 108B tail; caller 0x0021EF82
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <map>
#include "ascii_string.h"

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class LadderPref
{
};

class BfmeFixedStorage002CF0F0
{
public:
	BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &o) throw();
private:
	int m_00;
};

struct Tail108
{
	int w[27];
};

class Rva0021E85A
{
public:
	Rva0021E85A(const Rva0021E85A &o);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	AsciiString m_20;
	_STL::map<int, _STL::vector<unsigned int> > m_24;
	_STL::vector<ScienceType> m_30;
	_STL::vector<ScienceType> m_3c;
	_STL::map<int, int> m_48;
	_STL::map<long, LadderPref> m_54;
	unsigned char m_60;
	char m_pad61[3];
	int m_64;
	BfmeFixedStorage002CF0F0 m_68;
	Tail108 m_6c;
};

Rva0021E85A::Rva0021E85A(const Rva0021E85A &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
	, m_08(o.m_08)
	, m_0c(o.m_0c)
	, m_10(o.m_10)
	, m_14(o.m_14)
	, m_18(o.m_18)
	, m_1c(o.m_1c)
	, m_20(o.m_20)
	, m_24(o.m_24)
	, m_30(o.m_30)
	, m_3c(o.m_3c)
	, m_48(o.m_48)
	, m_54(o.m_54)
	, m_60(o.m_60)
	, m_64(o.m_64)
	, m_68(o.m_68)
	, m_6c(o.m_6c)
{
}

// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva002DFA7A@@QAE@HABVAsciiString@@@Z, retail 0x002DFA7A, 87 bytes.
// Ctor: AsciiString at +0 via rowed 0x000365F0, int at +4 from first param,
// byte at +8 plus ints at +0C/+10/+14/+18/+1C/+20/+24 zeroed, +28=1, +2C=0,
// two vector<BfmeE16> at +30/+3C via rowed 0x00211E58. Returns this, ret 8.
// Evidence: unlock lane, caller 0x002E048C pushes esi plus AsciiString at
// ebp-0x10 into this at ebp-0x78, LivingWorldBuilding INI parse context,
// precedent Rva001ED0A9Ctor.cpp same AsciiString plus dual BfmeE16 vectors.
#include <vector>

#include "ascii_string.h"

struct BfmeE16 { int a[4]; };

class Rva002DFA7A
{
public:
	Rva002DFA7A(int val, const AsciiString &s);
private:
	AsciiString m_00;
	int m_04;
	bool m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_30;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_3c;
};

Rva002DFA7A::Rva002DFA7A(int val, const AsciiString &s)
	: m_00(s),
	  m_04(val),
	  m_08(false),
	  m_0c(0),
	  m_10(0),
	  m_14(0),
	  m_18(0),
	  m_1c(0),
	  m_20(0),
	  m_24(0),
	  m_28(1),
	  m_2c(0)
{
}

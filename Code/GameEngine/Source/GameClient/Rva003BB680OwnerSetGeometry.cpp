// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?setGeometryName@Rva003BB680Owner@@QAEXAAVAsciiString@@@Z @0x004E3E91 78B: push temp GeometryName then vector.
// Evidence: pin names class/method; rowed temp ctor 0x4E2382 dtor 0x4E2941 StringBase set 0x366F0 push_back 0x4E3E5A; 1 matched caller shows AAVAsciiString.
#include <set>
#include <vector>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL {
template <> struct less<AsciiString> {
	bool operator()(const AsciiString &left, const AsciiString &right) const {
		return left < right;
	}
};
}

struct BfmeE16 { float x, y, z, w; };

class Rva004E2382 {
public:
	Rva004E2382();
	~Rva004E2382();
	AsciiString m_00;
	int m_04;
	_STL::set<AsciiString> m_08;
	_STL::vector<BfmeE16> m_14;
};

struct Rva004E3E5AElement { int a[8]; };

class Rva003BB680Owner {
public:
	void setGeometryName(AsciiString &name);
private:
	char m_pad[0x14];
	_STL::vector<Rva004E3E5AElement> m_14;
};

void Rva003BB680Owner::setGeometryName(AsciiString &name)
{
	Rva004E2382 tmp;
	tmp.m_00.set(name);
	m_14.push_back(*(Rva004E3E5AElement *)&tmp);
}

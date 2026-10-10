// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001FDB55@@UAE@XZ @0x001FDBA1 74B: dtor via vtable 0x007E1BB0, set at +0x18 via rowed 0x000730DE, vector at +0xC via rowed 0x001FD882, base 0x001B4E74; evidence callees rowed, caller 0x001FDD64, ctor 0x001FDB55.
#include <vector>
#include "ascii_string.h"

struct BfmeObject476 { ~BfmeObject476(); };

class Rva00072FE6
{
public:
	~Rva00072FE6();
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva001FDB55 : public SubsystemInterface
{
public:
	virtual ~Rva001FDB55();
private:
	_STL::vector<BfmeObject476> m_vec;
	Rva00072FE6 m_set;
	int m_state24;
};

inline Rva001FDB55::~Rva001FDB55()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva001FDB55DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva001FDB55DtorInlineAnchor()
{
    static_cast<Rva001FDB55 *>(0)->Rva001FDB55::~Rva001FDB55();
}
#pragma inline_depth()

// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1ArmyUnitIconMovieClip@StrategicHUD@@UAE@XZ @0x005FCFEA 80B: +0x28 via rowed ~Rva005242D7,
// +0x1c via rowed ~Rva0052413E, base ~Rva005FCF0E (rowed 75B). Both member
// views are vector<AsciiString> and are copied member for member from
// Rva005242D7Chain.cpp / Rva0052413EDtor.cpp (their dtors resolve through
// the ledger). Destruction order in the target (0x28, then 0x1c, then base)
// fixes the declaration order below.
#include <vector>

#include "ascii_string.h"

#include "../../Include/Common/Rva0052413E.h"

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

class Rva005FCF0E
{
public:
	virtual ~Rva005FCF0E();
};

// StrategicHUD::ArmyUnitIconMovieClip: its constructor 0x005FD251 installs
// table 0x0087A1F4, whose deleting destructor 0x005FD0DE calls this body.
namespace StrategicHUD {
class ArmyUnitIconMovieClip;
}

class StrategicHUD::ArmyUnitIconMovieClip : public Rva005FCF0E
{
public:
	virtual ~ArmyUnitIconMovieClip();
private:
	unsigned char m_pad1C[0x1C - 4];
	Rva0052413E m_mem1C;
	Rva005242D7 m_mem28;
};

StrategicHUD::ArmyUnitIconMovieClip::~ArmyUnitIconMovieClip()
{
}

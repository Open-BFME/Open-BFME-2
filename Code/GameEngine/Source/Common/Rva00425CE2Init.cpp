// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?init@Rva00425CE2@@UAEXXZ, retail 0x00424DDE..0x00424E77 (153 bytes, EH):
// slot 1 -- SubsystemInterface::init -- of Rva00425CE2, the subsystem the
// "TheFormationAssistant" registration (0x0022F069) constructs (its
// constructor 0x00421A84 stores this vtable, 0x00C3BEE0). When the 0x00DC84F5
// switch is set it loads Data\INI\FormationAssistant.ini into a local INI
// (rowed ctor, loadFile with load type 1 and no Xfer, dtor) and sorts the
// global deque of formation entries (iterators 0x00E031A8 and 0x00E031B8)
// with the rowed sort and its comparator. It ignores this. WorldBuilder's twin
// (0x0113B7F0) is unnamed.

#include "ascii_string.h"
#include <deque>
#include <algorithm>

struct BfmeE12 { float x, y, z; };

struct BfmeE12Cmp00422291
{
	bool operator()(const BfmeE12 &a, const BfmeE12 &b) const;
};

namespace _STL
{
template <>
void sort<_Deque_iterator<BfmeE12, _Nonconst_traits<BfmeE12> >, BfmeE12Cmp00422291>(
	_Deque_iterator<BfmeE12, _Nonconst_traits<BfmeE12> > first,
	_Deque_iterator<BfmeE12, _Nonconst_traits<BfmeE12> > last,
	BfmeE12Cmp00422291 comp);
}

extern unsigned char g_00DC84F5;
extern _STL::deque<BfmeE12>::iterator g_00E031A8;
extern _STL::deque<BfmeE12>::iterator g_00E031B8;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1
};

class Xfer;

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
private:
	unsigned char m_data[0x87C];
};

class Rva00425CE2
{
public:
	virtual ~Rva00425CE2();
	virtual void init();
};

void Rva00425CE2::init()
{
	if (g_00DC84F5)
	{
		INI ini;
		ini.loadFile(AsciiString("Data\\INI\\FormationAssistant.ini"), INI_LOAD_OVERWRITE, 0);
		_STL::sort(g_00E031A8, g_00E031B8, BfmeE12Cmp00422291());
	}
}

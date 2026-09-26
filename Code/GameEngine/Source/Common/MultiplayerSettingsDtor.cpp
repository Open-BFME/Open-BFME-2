// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// MultiplayerSettings destructor (retail 0x00381293, 83B): tears down the
// random definition at +0x84 and the observer definition at +0x44 through
// the StringBase teardown, the +0x34 color-list member through the rowed
// color-tree dtor 0x0038103F, then the GameEngineDeletingBase base through
// its rowed dtor. Layout follows the landed getColor/newMultiplayerColor-
// Definition bodies (+0x34 list, +0x44 observer, +0x84 random, 0x88 total).
#include <map>

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class MultiplayerColorDefinition;

namespace _STL
{
template <>
class _Rb_tree<int, pair<const int, MultiplayerColorDefinition>, _Select1st<pair<const int, MultiplayerColorDefinition> >, less<int>, allocator<pair<const int, MultiplayerColorDefinition> > >
{
public:
	~_Rb_tree();

private:
	void *m_headerData;
	char m_pad04[0xC];
};
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, MultiplayerColorDefinition>, _STL::_Select1st<_STL::pair<const int, MultiplayerColorDefinition> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, MultiplayerColorDefinition> > > ColorMapTree;

class MultiplayerSettings
{
public:
	~MultiplayerSettings();

private:
	GameEngineDeletingBase m_deletingBase; // +0x00
	char m_pad0C[0x34 - 0x0C];
	ColorMapTree m_colorList; // +0x34
	AsciiString m_observer; // +0x44
	char m_pad48[0x84 - 0x48];
	AsciiString m_random; // +0x84
};

// ??1MultiplayerSettings@@QAE@XZ @0x381293
MultiplayerSettings::~MultiplayerSettings()
{
}

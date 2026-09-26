// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// MultiplayerSettings constructor (retail 0x003811D8, 159B): constructs
// the SubsystemInterface base, installs the vtable, constructs the +0x34
// color map through the rowed 0x003811A2 body and the observer/random
// definitions at +0x44/+0x84 through the rowed 0x00380C4E body, then
// stores the countdown/beacon/flag/credit defaults. The singleton is
// 0xC4 bytes (push 0xC4 at the 0x1EF393 creation site), so both color
// definitions are full 0x40-byte values. All constructions resolve to
// rowed bodies or pins; nothing extra is defined here.
#include <map>

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();

private:
	AsciiString m_tooltipName; // +0x00
	RGBColor m_rgbValue; // +0x04
	int m_color; // +0x10
	RGBColor m_rgbValueNight; // +0x14
	int m_colorNight; // +0x20
	RGBColor m_rgbExtra1; // +0x24
	RGBColor m_rgbExtra2; // +0x30
	bool m_extraFlag; // +0x3C
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad[8];
};

namespace _STL
{
template <>
class map<int, MultiplayerColorDefinition, less<int>, allocator<pair<const int, MultiplayerColorDefinition> > >
{
public:
	map();
	~map();

private:
	char m_pad[0xC];
};
}

typedef _STL::map<int, MultiplayerColorDefinition, _STL::less<int>, _STL::allocator<_STL::pair<const int, MultiplayerColorDefinition> > > MultiplayerColorList;

class MultiplayerSettings : public SubsystemInterface
{
public:
	MultiplayerSettings();
	virtual ~MultiplayerSettings();

private:
	int m_unknown0C; // +0x0C, zeroed
	int m_startCountdownTimerSeconds; // +0x10, retail default 0x2710
	int m_unknown14; // +0x14, zeroed
	int m_maxBeaconsPerPlayer; // +0x18, retail default 3
	bool m_isShroudInMultiplayer; // +0x1C
	bool m_showRandomPlayerTemplate; // +0x1D
	bool m_showRandomStartPos; // +0x1E
	bool m_showRandomColor; // +0x1F
	int m_initialCredits[5]; // +0x20 VeryLow Low Medium High VeryHigh
	MultiplayerColorList m_colorList; // +0x34 (node count at +0x38 doubles as the refill source)
	int m_numColors; // +0x40, zeroed (lazy refill)
	MultiplayerColorDefinition m_observerColor; // +0x44
	MultiplayerColorDefinition m_randomColor; // +0x84
};

// ??0MultiplayerSettings@@QAE@XZ @0x3811D8
MultiplayerSettings::MultiplayerSettings()
{
	m_unknown0C = 0;
	m_unknown14 = 0;
	m_numColors = 0;
	m_startCountdownTimerSeconds = 0x2710;
	m_maxBeaconsPerPlayer = 3;
	m_isShroudInMultiplayer = true;
	m_showRandomPlayerTemplate = true;
	m_showRandomStartPos = true;
	m_showRandomColor = true;
	m_initialCredits[0] = 0x1F4;
	m_initialCredits[1] = 0x3E8;
	m_initialCredits[2] = 0x5DC;
	m_initialCredits[3] = 0x7D0;
	m_initialCredits[4] = 0x9C4;
}

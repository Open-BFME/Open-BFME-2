// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Ported from reference/open-bfme-1/Code/GameEngine/Source/Common/MultiplayerColorPairConstructor.cpp.
// BFME2 grew MultiplayerColorDefinition to 0x40 bytes (two trailing RGBColors
// plus a flag byte; see MultiplayerColorDefinitionCtor.cpp), so the pair below
// is pair<const int, 0x40-byte MCD>, not the reference's 0x24-byte shape.
// The key/value constructor is retail 0x00380DEA (27B, frameless), reached
// from the color-list miss path (lookup 0x3812E6); the copy/dtor follow the
// reference's explicit-instantiation list.

// Give VC7.1 declared pair members that explicit instantiation can emit.
#include <utility>

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}

private:
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other);
	~AsciiString();
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
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);

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

typedef char MultiplayerColorPairValueMatchesRetail[(sizeof(MultiplayerColorDefinition) == 0x40) ? 1 : -1];

typedef int Int;

typedef _STL::pair<const int, MultiplayerColorDefinition> MultiplayerColorPair;

// The map subscript at 0x003812E6 reaches this key/value constructor.
// (Callers declare it __declspec(noinline) so the call stays out of line;
// the noinline lives on the caller side, not here, so emission is plain.)
template MultiplayerColorPair::pair(const int &, const MultiplayerColorDefinition &);
template MultiplayerColorPair::pair(const MultiplayerColorPair &);
template MultiplayerColorPair::~pair();

// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Ported from reference/open-bfme-1/Code/GameEngine/Source/Common/MultiplayerColorPairConstructor.cpp.
// ??0MultiplayerColorDefinition@@QAE@ABV0@@Z, retail 0x00380D30, 79 bytes.
// MultiplayerColorDefinition copy ctor over the BFME2 0x40-byte model (see
// MultiplayerColorPairConstructor.cpp): AsciiString base copy via 0x365F0,
// then rep-movsd member runs plus the trailing flag byte. Shard (not a graft
// into the pair TU) so the pair bodies keep calling this out of line.

class AsciiString
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other);
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

// ??0MultiplayerColorDefinition@@QAE@ABV0@@Z @0x00380D30
MultiplayerColorDefinition::MultiplayerColorDefinition(const MultiplayerColorDefinition &other)
	: m_tooltipName(other.m_tooltipName),
	  m_rgbValue(other.m_rgbValue),
	  m_color(other.m_color),
	  m_rgbValueNight(other.m_rgbValueNight),
	  m_colorNight(other.m_colorNight),
	  m_rgbExtra1(other.m_rgbExtra1),
	  m_rgbExtra2(other.m_rgbExtra2),
	  m_extraFlag(other.m_extraFlag)
{
}

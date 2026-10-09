// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ExperienceLevel construction. Keep Rva002894A2, the existing vtable/dtor
// owner at 0x00BFB840, rather than inventing a second identity there.
// BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705, Common/ExperienceLevelConstructor.cpp
// and ExperienceLevelCopyConstructor.cpp supply the semantic guide.
// Retail 0x002893BA..0x002894A2, callers 0x0028A344/0x0028A390, and the
// FieldParse table at 0x00BFBAC0 prove the 0x108 allocation and member offsets.
// The rowed LevelUpFx/Upgrades parsers establish 8-byte FX+bone records and
// const UpgradeTemplate pointers; names/attribute modifiers are AsciiStrings.
// Base 0x001E3624 adds the override index at +0x0C; name is +0x10.
// Empty vector constructors are complete emitted STLport folds of 0x00211E58.
// The real radius-decal members and visible RGBColor::setFromInt definition
// preserve the five-state exception cleanup; all bytes and EH match retail.
#include <vector>
#include "ascii_string.h"


class Rva0042526Member
{
public:
	Rva0042526Member();
	char m_pad[0x4C];
};
class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	AsciiString m_name;
	AsciiString m_secondName;
	int m_shadowType;
	float m_minOpacity, m_maxOpacity, m_opacityThrobTime;
	int m_color;
	bool m_onlyVisibleToOwningPlayer;
	float m_unmodelled20, m_unmodelled24;
	unsigned int m_unmodelled28;
	float m_unmodelled2C, m_unmodelled30;
};
class RGBColor
{
public:
	void setFromInt(int v) { red = ((v >> 16) & 0xff) / 255.0f; green = ((v >> 8) & 0xff) / 255.0f; blue = (v & 0xff) / 255.0f; }
	float red, green, blue;
};

#include "ascii_string.h"
class FXList;
class UpgradeTemplate;
struct LevelUpFXInfo { const FXList *fx; AsciiString boneName; };
class __declspec(novtable) Rva001E3624
{
public:
    Rva001E3624() : m_next(0), m_override(false), m_index(-1) {}
    virtual ~Rva001E3624();
    Rva001E3624 *m_next;
    bool m_override;
    int m_index;
};
class Rva002894A2 : public Rva001E3624
{
public:
	virtual ~Rva002894A2();
	Rva002894A2();
private:
	AsciiString m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	_STL::vector<AsciiString> m24;
	_STL::vector<AsciiString> m30;
	_STL::vector<LevelUpFXInfo> m3C;
	int m48;
	_STL::vector<const UpgradeTemplate *> m4C;
	Rva0042526Member m58;
	RadiusDecalTemplate mA4;
	unsigned char mD8;
	char m_padD9[3];
	RGBColor mDC;
	int mE8;
	int mEC;
	int mF0;
	float mF4;
	float mF8;
	int mFC;
	unsigned char m100;
	unsigned char m101;
	unsigned char m102;
	char m_pad103;
	int m104;
};

Rva002894A2::Rva002894A2()
	: m10()
	, m14(0)
	, m18(0)
	, m1C(0)
	, m20(-1)
	, m48(0)
	, mD8(0)
	, mE8(0)
	, mEC(0)
	, mF0(0)
	, mF4(0.0f)
	, mF8(0.0f)
	, mFC(0)
	, m100(0)
	, m101(0)
	, m102(0)
	, m104(-1)
{
	mDC.setFromInt(0);
}

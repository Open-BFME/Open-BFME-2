#pragma once
// BFME2 WaterTransparencySetting consumed native layout, not ZH's single-base layout.
// Native200D80 ctor/200EE4 parser and C080B0 table; evidence accompanies adoption.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../Common/Overridable.h"
struct FieldParse;
class Rva00200CB1
{
public:
	Rva00200CB1 &operator=(const Rva00200CB1 &that);
};

class Rva00200D38
{
public:
	virtual void rva00200BD9() = 0;
	virtual void slot1() = 0;
	virtual int Rva00200BBAGet() = 0;

	Rva00200D38(const AsciiString &name);

private:
	AsciiString m_name;
};

class WaterTransparencySetting : public Overridable, public Rva00200D38
{
public:
	WaterTransparencySetting();
	virtual ~WaterTransparencySetting();
	virtual void rva00200BD9();
	virtual void slot1();
	virtual int Rva00200BBAGet();
	__declspec(dllimport) __forceinline WaterTransparencySetting &operator=(const WaterTransparencySetting &that)
	{
		reinterpret_cast<Rva00200CB1 *>(this)->operator=(reinterpret_cast<const Rva00200CB1 &>(that));
		return *this;
	}

	const FieldParse *getFieldParse(void) const { return m_waterTransparencySettingFieldParseTable; }
	static const FieldParse m_waterTransparencySettingFieldParseTable[];


	float m_transparentWaterDepth; // +0x18
	float m_minWaterOpacity; // +0x1C
	RGBColor m_standingWaterColor; // +0x20
	RGBColor m_radarColor; // +0x2C
	bool m_additiveBlend; // +0x38
	AsciiString m_standingWaterTexture; // +0x3C
	float m_riverTransparencyMultiplier; // +0x40
	int m_unk44;
	int m_unk48;
	float m_unk4C;
	bool m_unk50;
	float m_unk54;
	float m_unk58;
};


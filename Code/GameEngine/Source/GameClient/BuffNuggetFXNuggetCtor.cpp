// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BuffNuggetFXNugget@@QAE@XZ 295B @0x001E2FCE: no-arg ctor called by
// BuffNuggetFXNugget::parse (0x001E323B) for the BuffNugget FXList keyword;
// class name from BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/BuffNuggetFXNuggetConstructor.cpp).
// Member names and offsets from the retail FieldParse table 0x00BDCEB8
// (BuffType@0x148 IsComplexBuff@0x14C BuffThingTemplate@0x154
// BuffOrcTemplate@0x158 BuffInfantryTemplate@0x15C BuffCavalryTemplate@0x160
// BuffTrollTemplate@0x164 BuffMumakilTemplate@0x168 BuffShipTemplate@0x16C
// BuffMonsterTemplate@0x170 BuffLifeTime@0x150 Extrusion@0x174 Color@0x178);
// parse TU notes news 0x190 and builder 0x001DFB64. Retail adds Ship and
// Monster templates over the donor six; follow retail with eight strings.
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

#include <vector>

template <typename T>
class StringBase
{
	friend class AsciiString;

protected:
	~StringBase();

	void *m_data;

private:
	StringBase(const char *str);
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *str) : StringBase<char>(str) {}
	~AsciiString();
};

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
protected:
	int m_nuggetType; // +4
	unsigned char m_pad[0x148 - 8];
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class BuffNuggetFXNugget : public Rva001DFEAABase
{
public:
	BuffNuggetFXNugget();
	virtual ~BuffNuggetFXNugget();
private:
	int m_buffType; // +0x148
	bool m_isComplexBuff; // +0x14C
	unsigned char m_padB9[3];
	unsigned int m_buffLifeTime; // +0x150
	AsciiString m_buffThingTemplate; // +0x154
	AsciiString m_buffOrcTemplate; // +0x158
	AsciiString m_buffInfantryTemplate; // +0x15C
	AsciiString m_buffCavalryTemplate; // +0x160
	AsciiString m_buffTrollTemplate; // +0x164
	AsciiString m_buffMumakilTemplate; // +0x168
	AsciiString m_buffShipTemplate; // +0x16C
	AsciiString m_buffMonsterTemplate; // +0x170
	float m_extrusion; // +0x174
	RGBColor m_color; // +0x178
	_STL::vector<AsciiString> m_member; // +0x184
};

// ??0BuffNuggetFXNugget@@QAE@XZ
BuffNuggetFXNugget::BuffNuggetFXNugget()
	: m_buffType(0)
	, m_isComplexBuff(false)
	, m_buffLifeTime(0)
	, m_buffThingTemplate("INVALID_THING")
	, m_buffOrcTemplate("INVALID_THING")
	, m_buffInfantryTemplate("INVALID_THING")
	, m_buffCavalryTemplate("INVALID_THING")
	, m_buffTrollTemplate("INVALID_THING")
	, m_buffMumakilTemplate("INVALID_THING")
	, m_buffShipTemplate("INVALID_THING")
	, m_buffMonsterTemplate("INVALID_THING")
	, m_extrusion(1.0f)
{
	m_color.red = *reinterpret_cast<volatile const float *>(0x00BC4DD8);
	m_color.green = *reinterpret_cast<volatile const float *>(0x00BCAE8C);
	m_color.blue = *reinterpret_cast<volatile const float *>(0x00BBB8D8);
	m_member.clear();
}

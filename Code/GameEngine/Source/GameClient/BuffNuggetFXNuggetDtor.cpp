// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1BuffNuggetFXNugget@@UAE@XZ 179B @0x001E32D3: virtual dtor.
// Installs no derived vptr (novtable view like Helix 0x001E116E sibling).
// Destroys _STL::vector<AsciiString> at +0x184 via rowed 0x0002CC70 then eight
// AsciiString/StringBase<char> members at +0x170 down to +0x154 via folded
// 0x00036410 then calls base ??1TransportContainModuleData@@UAE@XZ at
// 0x001DFA48. Identity: ctor 0x001E2FCE installs vtable 0x007DD9B4 whose slot 0
// ??_G 0x001E32B7 calls here; FieldParse table 0x00BDCEB8 fixes the eight
// strings; news 0x190 fixes the extent.

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

class TransportContainModuleData
{
public:
	virtual ~TransportContainModuleData();

private:
	unsigned char unknownBaseTail[0x144];
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

// The target dtor has no derived-vptr store. novtable keeps this view's dtor
// body aligned with that fact; no constructor is emitted from this file.
class __declspec(novtable) BuffNuggetFXNugget : public TransportContainModuleData
{
public:
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

typedef char BaseExtent[sizeof(TransportContainModuleData) == 0x148 ? 1 : -1];
typedef char AsciiExtent[sizeof(AsciiString) == 4 ? 1 : -1];

BuffNuggetFXNugget::~BuffNuggetFXNugget() {}

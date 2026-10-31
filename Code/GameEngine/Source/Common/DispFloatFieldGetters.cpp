// Disp32 float getters: seven-byte __thiscall members with one shape:
//
//     fld dword ptr [ecx+<DISP>] / ret
//
// One dword is loaded onto the x87 stack and left there, which is the return
// convention for `float`. BFME1 pioneered the same family in
// reference/open-bfme-1/Code/GameEngine/Source/Common/DispFloatFieldGetters.cpp.
// No // cl: line (defaults match the frameless 7-byte shape).
#define BFME_DISP_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP_FLOAT_GETTER(Rva00050F61FloatField, 0x90)
BFME_DISP_FLOAT_GETTER(Rva00050F68FloatField, 0x94)
// 0x00050F6F sits in this 0x50F61..0x50F7C getter run; a stale Zero Hour layout had
// rowed it as LightClass::Get_Intensity. BFME 2 keeps LightClass::Intensity at +0xD0:
// its getter is 0x0011C6F0, emitted with Get_Specular/Get_Spot_Direction/
// Get_Spot_Exponent (0x0011C700..0x0011C766) in dx8wrapper.cpp's Set_Light order.
BFME_DISP_FLOAT_GETTER(Rva00050F6FFloatField, 0xA0)
BFME_DISP_FLOAT_GETTER(Rva00050F76FloatField, 0xA8)
BFME_DISP_FLOAT_GETTER(Rva0006E032FloatField, 0x358)
BFME_DISP_FLOAT_GETTER(Rva000788D3FloatField, 0x200)
BFME_DISP_FLOAT_GETTER(Rva000788F8FloatField, 0x4E8)
BFME_DISP_FLOAT_GETTER(Rva000788FFFloatField, 0x4EC)
BFME_DISP_FLOAT_GETTER(Rva00078906FloatField, 0x4F0)
BFME_DISP_FLOAT_GETTER(Rva0007890DFloatField, 0x4F4)
BFME_DISP_FLOAT_GETTER(Rva00078914FloatField, 0x500)
BFME_DISP_FLOAT_GETTER(Rva0007891BFloatField, 0x504)
BFME_DISP_FLOAT_GETTER(Rva00085516FloatField, 0xF0)
BFME_DISP_FLOAT_GETTER(Rva00042F91FloatField, 0x37E8)
BFME_DISP_FLOAT_GETTER(Rva0008BC64FloatField, 0xA4)
BFME_DISP_FLOAT_GETTER(Rva0008E179FloatField, 0x1A148)
BFME_DISP_FLOAT_GETTER(Rva00091A48FloatField, 0x4D4)
BFME_DISP_FLOAT_GETTER(Rva00091A4FFloatField, 0x4D8)
BFME_DISP_FLOAT_GETTER(Rva000B228DFloatField, 0x1C0)
BFME_DISP_FLOAT_GETTER(Rva000B28CFFloatField, 0x4A8)
BFME_DISP_FLOAT_GETTER(Rva000D43D3FloatField, 0x104)
BFME_DISP_FLOAT_GETTER(Rva000EFB0DFloatField, 0x37D8)
BFME_DISP_FLOAT_GETTER(Rva0015E1A0FloatField, 0x100)
BFME_DISP_FLOAT_GETTER(Rva0015E1B0FloatField, 0x104)
BFME_DISP_FLOAT_GETTER(Rva00167EB2FloatField, 0x100)
BFME_DISP_FLOAT_GETTER(Rva001A0AD0FloatField, 0x200)
BFME_DISP_FLOAT_GETTER(Rva001E3810FloatField, 0x53C)
BFME_DISP_FLOAT_GETTER(Rva001EAE4EFloatField, 0x314)
BFME_DISP_FLOAT_GETTER(Rva0023C522FloatField, 0x4A0)
BFME_DISP_FLOAT_GETTER(Rva0023C530FloatField, 0x4E0)
BFME_DISP_FLOAT_GETTER(Rva0023C537FloatField, 0x4D0)
BFME_DISP_FLOAT_GETTER(Rva002622B0FloatField, 0x508)
BFME_DISP_FLOAT_GETTER(Rva002622E2FloatField, 0x168)
BFME_DISP_FLOAT_GETTER(Rva0026235CFloatField, 0x148)
BFME_DISP_FLOAT_GETTER(Rva0026FF56FloatField, 0x590)
BFME_DISP_FLOAT_GETTER(Rva0028A88BFloatField, 0x4AC)
BFME_DISP_FLOAT_GETTER(Rva0028A892FloatField, 0x4B0)
BFME_DISP_FLOAT_GETTER(Rva0028A899FloatField, 0x4B4)
BFME_DISP_FLOAT_GETTER(Rva0028A8A0FloatField, 0x4B8)
BFME_DISP_FLOAT_GETTER(Rva0028A8A7FloatField, 0x4CC)
BFME_DISP_FLOAT_GETTER(Rva0028A8AEFloatField, 0x4BC)
BFME_DISP_FLOAT_GETTER(Rva0028A8FEFloatField, 0x51C)
BFME_DISP_FLOAT_GETTER(Rva0028A905FloatField, 0x50C)
BFME_DISP_FLOAT_GETTER(Rva0028A90CFloatField, 0x510)
BFME_DISP_FLOAT_GETTER(Rva0028A913FloatField, 0x514)
BFME_DISP_FLOAT_GETTER(Rva0028A91AFloatField, 0x518)
BFME_DISP_FLOAT_GETTER(Rva0028A95AFloatField, 0x530)
BFME_DISP_FLOAT_GETTER(Rva0028A992FloatField, 0x610)
BFME_DISP_FLOAT_GETTER(Rva0028A9AEFloatField, 0x534)
BFME_DISP_FLOAT_GETTER(Rva002AA0B1FloatField, 0x6F8)
BFME_DISP_FLOAT_GETTER(Rva002B2383FloatField, 0x1C8)
BFME_DISP_FLOAT_GETTER(Rva002C8E60FloatField, 0x158)
BFME_DISP_FLOAT_GETTER(Rva002C8E67FloatField, 0x15C)
BFME_DISP_FLOAT_GETTER(Rva002C8E75FloatField, 0x88)
BFME_DISP_FLOAT_GETTER(Rva002C8F4FFloatField, 0x130)
BFME_DISP_FLOAT_GETTER(Rva002E6EF8FloatField, 0x52C)
BFME_DISP_FLOAT_GETTER(Rva0033A44CFloatField, 0x4DC)
BFME_DISP_FLOAT_GETTER(Rva0033F901FloatField, 0x1A0)
BFME_DISP_FLOAT_GETTER(Rva003673CEFloatField, 0x540)
BFME_DISP_FLOAT_GETTER(Rva0045D381FloatField, 0x179C)
BFME_DISP_FLOAT_GETTER(Rva004BB968FloatField, 0x608)
BFME_DISP_FLOAT_GETTER(Rva004BB96FFloatField, 0x60C)
BFME_DISP_FLOAT_GETTER(Rva004CBBC5FloatField, 0x1D4)
BFME_DISP_FLOAT_GETTER(Rva004D92F7FloatField, 0x524)
BFME_DISP_FLOAT_GETTER(Rva0055F4B5FloatField, 0x180)

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 donor
// game/GameEngine/Source/Common/DispFloatFieldGetters.cpp at /O1 /arch:SSE /G7
// supplied the expression; retail independently proves ecx+0x80 float load,
// x87 return and the complete 0x00094AF6..0x00094AFD leaf. The preceding
// adjustment thunk ends at 0x00094AF6 and the next begins at 0x00094AFD.
// Original receiver class and field purpose remain unknown.
BFME_DISP_FLOAT_GETTER(Rva00094AF6FloatField, 0x80)

// Two getters that read a GameClientRandomVariable field through its rowed
// getValue (0x002341A1): add ecx, <field>; tail jump. They bracket the 0x80
// float getter above: 0x00094AEE (8B, field +0x74) ends where it begins and
// 0x00094AFD (11B, field +0x84) starts where it ends. Receiver classes are
// unknown; names follow this file's per-address convention.
class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class Rva00094AEERandomField
{
public:
	float get() const;
private:
	char m_pad00[0x74];
	GameClientRandomVariable m_value;
};

float Rva00094AEERandomField::get() const
{
	return m_value.getValue();
}

class Rva00094AFDRandomField
{
public:
	float get() const;
private:
	char m_pad00[0x84];
	GameClientRandomVariable m_value;
};

float Rva00094AFDRandomField::get() const
{
	return m_value.getValue();
}

class Rva00098540RandomField
{
public:
	int get() const;
private:
	char m_pad00[0x30];
	GameClientRandomVariable m_value;
};

int Rva00098540RandomField::get() const
{
	return (int)m_value.getValue();
}

class Rva0009854DRandomField
{
public:
	float get() const;
private:
	char m_pad00[0x3C];
	GameClientRandomVariable m_value;
};

float Rva0009854DRandomField::get() const
{
	return m_value.getValue();
}


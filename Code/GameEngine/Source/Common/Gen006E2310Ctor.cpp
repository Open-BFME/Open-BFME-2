// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// The default constructors of the two classes whose destructors the ledger
// already names, ported from Open-BFME-1's
// GameEngine/Source/Common/Gen006E2310Ctor.cpp (donor revision
// 2f243e26d44a74a48ef0ccfe9b543874e6567883; the donor's volatile members are
// not needed under BFME 2's /O1 /arch:SSE settings):
//
//   ??0BfmeB1137@@QAE@XZ     0x00094EBF  93B: MaterialPassClass subclass,
//       vtable 0x00BC8198, dtor 0x00094F38 (BfmeConv1137Dtor.cpp); base
//       ctor MaterialPassClass 0x0013EDD0. Four texture holders at
//       +0x58..+0x64 as in the dtor's view; the other member types are read
//       off the stores (float, int, bool), names unknown.
//   ??0Gen006E2310@@QAE@XZ   0x0009525E 222B: vtable 0x00BC8208, dtor
//       0x00095360 (BfmeDtor006e2480.cpp); base Rva009519B, ctor 0x00215160
//       and dtor 0x0009519B. Creates the BfmeB1137 singleton the dtor
//       releases (global 0x00DE4880), then zeroes its members, 0xFF at +0xC4
//       and 0x555555 at +0xF8. Called by the game client factory 0x0004C62D
//       after new 0x108.
//
// Target facts: the boundaries, vtables, callees, member offsets and store
// order are from retail; the class names are the ledger's own placeholders.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass
{
public:
	MaterialPassClass(void);
	virtual ~MaterialPassClass(void);

private:
	unsigned char m_unmodelled[0x34];
};

class TextureClass;

class BfmeTexHold1137
{
public:
	BfmeTexHold1137(void) : m_texture(0) {}
	~BfmeTexHold1137(void);

private:
	TextureClass *m_texture;
};

class BfmeB1137 : public MaterialPassClass
{
public:
	BfmeB1137(void);
	virtual ~BfmeB1137(void);

private:
	float m_38;
	float m_3C;
	float m_40;
	int m_44;
	int m_48;
	float m_4C;
	float m_50;
	bool m_54;
	BfmeTexHold1137 m_tex0;
	BfmeTexHold1137 m_tex1;
	BfmeTexHold1137 m_tex2;
	BfmeTexHold1137 m_tex3;
	bool m_68;
	bool m_69;
	bool m_6A;
	unsigned char m_unmodelled[0x75];
	float m_E0;
	int m_E4;
};

// ??0BfmeB1137@@QAE@XZ
BfmeB1137::BfmeB1137(void)
	: m_38(0.0f), m_3C(0.0f), m_40(0.0f), m_44(0), m_48(0), m_4C(0.0f), m_50(0.0f), m_54(true),
	  m_68(false), m_69(false), m_6A(false), m_E0(0.0f), m_E4(0)
{
}

// The CloudEffect record class (Rva009519BCtor.cpp), only as a base here.
class Rva009519B
{
public:
	Rva009519B();
	virtual ~Rva009519B();

private:
	unsigned char m_unmodelled[0xB8];
};

// Three zeroed float triples; Set is inlined on each one's address.
struct Gen006E2310Triple
{
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	float X;
	float Y;
	float Z;
};

// Retail's global dword at 0x00DE4880 (?g_get_00710fb0@@3HA in the data
// ledger), holding the BfmeB1137 singleton; the dtor reads it the same way.
// Retail's global dword (data_ledger RVA 0x9E4880, zero .data, unowned),
// holding the BfmeB1137 singleton; defined here, nothing else defines it.
int g_get_00710fb0;

class Gen006E2310 : public Rva009519B
{
public:
	Gen006E2310(void);
	virtual ~Gen006E2310(void);

private:
	int m_BC;
	int m_C0;
	int m_C4;
	bool m_C8;
	int m_CC;
	float m_D0;
	Gen006E2310Triple m_D4;
	Gen006E2310Triple m_E0;
	Gen006E2310Triple m_EC;
	int m_F8;
	int m_FC;
	int m_100;
	int m_104;
};

// ??0Gen006E2310@@QAE@XZ
Gen006E2310::Gen006E2310(void)
{
	*reinterpret_cast<BfmeB1137 **>(&g_get_00710fb0) = new BfmeB1137;
	m_BC = 0;
	m_C0 = 0;
	m_C8 = false;
	m_CC = 0;
	m_C4 = 0xff;
	m_D0 = 0.0f;
	m_D4.Set(0.0f, 0.0f, 0.0f);
	m_E0.Set(0.0f, 0.0f, 0.0f);
	m_EC.Set(0.0f, 0.0f, 0.0f);
	m_FC = 0;
	m_100 = 0;
	m_104 = 0;
	m_F8 = 0x555555;
}

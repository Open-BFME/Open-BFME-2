// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
// Built from the banked attempt reverse/attempts/0x00263653.cpp; fix: the float
// read through g_Va00BBB8D8 is a compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.
// ??0Rva00263653@@QAE@XZ @0x00263653 (147B).
// Ctor storing vtable 0x007F91FC at [this]; constants +0xC=0x16 +0x10=0x1D
// +0x21=1, floats +0x48/+0x50=1.0 via 1.0f, +0x54 via kF7C, rest 0.
// Evidence: call site at 0x002638A1 (lea ecx,[esi+4]); no callees.

extern "C" float kF7C;

class Rva00263653
{
public:
	Rva00263653();
	virtual void rva00263653_dummy();

private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	float m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad22[2];
	float m_24;
	int m_28;
	int m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	float m_44;
	float m_48;
	unsigned char m_4C;
	unsigned char m_pad4D[3];
	float m_50;
	float m_54;
	float m_58;
	float m_5C;
	float m_60;
	float m_64;
};

Rva00263653::Rva00263653()
	: m_04(0)
	, m_08(0)
	, m_0C(0x16)
	, m_10(0x1D)
	, m_14(0)
	, m_18(0)
	, m_1C(0.0f)
	, m_20(0)
	, m_21(1)
	, m_24(0.0f)
	, m_28(0)
	, m_2C(0)
	, m_30(0.0f)
	, m_34(0.0f)
	, m_38(0.0f)
{
	float tmp = 1.0f;
	m_48 = tmp;
	m_50 = tmp;
	float tmp2 = kF7C;
	m_3C = 0.0f;
	m_40 = 0.0f;
	m_44 = 0.0f;
	m_4C = 0;
	m_54 = tmp2;
	m_58 = 0.0f;
	m_5C = 0.0f;
	m_60 = 0.0f;
	m_64 = 0.0f;
}
// _kF7C: the global at VA 0xbc292c is ?g_objectSpacingDefault@@3MA.
#pragma comment(linker, "/alternatename:_kF7C=?g_objectSpacingDefault@@3MA")
// ?rva00263653_dummy@Rva00263653@@UAEXXZ present-unmatched
void Rva00263653::rva00263653_dummy()
{
}

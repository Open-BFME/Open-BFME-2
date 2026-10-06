// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00214F14@Rva009519B@@QAEXXZ retail 0x00214F14 426 bytes.
// Virtual slot 14 (offset 0x38) of vtable 0x007C81A8, class of
// ??1Rva009519B@@UAE@XZ. Initializes the five AsciiStrings at +0x0C +0x10
// +0x14 +0x24 +0xAC from globals via rowed StringBase<char>::set 0x000366F0,
// float/int/byte defaults from g_00DFE2xx, then Cos/Sin 0x0002FBC0/0x0002FBB0
// scaled into +0x50/+0x54. Evidence: same five strings as
// SubsystemDerivedDtors.cpp, callees rowed, no caller.
#include "ascii_string.h"

extern "C" float RADS_PER_DEGREE;
extern double g_bfmeFactorBW;
extern float g_Va00BCF628;
extern float g_00BC28F8;
extern float g_00BC7824;
extern float Cos(float);
extern float Sin(float);

extern AsciiString g_00DFE280;
extern AsciiString g_00DFE284;
extern AsciiString g_00DFE288;
extern AsciiString g_00DFE294;
extern AsciiString g_00DFE314;
extern float g_00DFE28C;
extern int g_00DFE290;
extern float g_00DFE298;
extern float g_00DFE29C;
extern float g_00DFE2C0;
extern float g_00DFE2C4;
extern unsigned char g_00DFE2C8;
extern unsigned char g_00DFE2C9;
extern unsigned char g_00DFE2CA;
extern float g_00DFE2CC;
extern float g_00DFE2DC;
extern float g_00DFE2EC;
extern int g_00DFE2B8;
extern int g_00DFE2BC;
extern int g_00DFE2FC;
extern int g_00DFE300;
extern int g_00DFE304;
extern int g_00DFE308;
extern int g_00DFE30C;
extern int g_00DFE310;

struct Block12
{
	int v[3];
};
extern Block12 g_00DFE2A0;
extern Block12 g_00DFE2AC;
extern Block12 g_00DFE2D0;
extern Block12 g_00DFE2E0;
extern Block12 g_00DFE2F0;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	AsciiString m_name;
};

class Rva009519B : public SubsystemInterface
{
public:
	virtual ~Rva009519B();
	void rva00214F14();
private:
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	float m_18;
	float m_1C;
	int m_20;
	AsciiString m_24;
	float m_28;
	float m_2C;
	Block12 m_30;
	Block12 m_3C;
	int m_48;
	int m_4C;
	float m_50;
	float m_54;
	float m_58;
	unsigned char m_5C;
	char _pad5D[3];
	float m_60;
	Block12 m_64;
	float m_70;
	Block12 m_74;
	float m_80;
	Block12 m_84;
	unsigned char m_90;
	unsigned char m_91;
	char _pad92[2];
	int m_94;
	int m_98;
	int m_9C;
	int m_A0;
	int m_A4;
	int m_A8;
	AsciiString m_AC;
};

void Rva009519B::rva00214F14()
{
	((StringBase<char> *)&m_0C)->set(*(const StringBase<char> *)&g_00DFE280);
	((StringBase<char> *)&m_10)->set(*(const StringBase<char> *)&g_00DFE284);
	((StringBase<char> *)&m_14)->set(*(const StringBase<char> *)&g_00DFE288);
	m_18 = g_00BC28F8 * g_00DFE28C;
	m_1C = (float)g_00DFE290 * RADS_PER_DEGREE;
	((StringBase<char> *)&m_24)->set(*(const StringBase<char> *)&g_00DFE294);
	m_28 = g_00DFE298;
	m_2C = g_00DFE29C * g_bfmeFactorBW;
	m_30 = g_00DFE2A0;
	m_3C = g_00DFE2AC;
	m_48 = g_00DFE2B8;
	m_4C = g_00DFE2BC;
	m_58 = g_00DFE2C4;
	m_5C = g_00DFE2C8;
	m_90 = g_00DFE2C9;
	m_91 = g_00DFE2CA;
	m_60 = g_00DFE2CC;
	m_64 = g_00DFE2D0;
	m_70 = g_00DFE2DC;
	m_74 = g_00DFE2E0;
	m_80 = g_00DFE2EC;
	m_84 = g_00DFE2F0;
	m_94 = g_00DFE2FC;
	m_98 = g_00DFE300;
	m_9C = g_00DFE304;
	m_A0 = g_00DFE308;
	m_A4 = g_00DFE30C;
	m_A8 = g_00DFE310;
	((StringBase<char> *)&m_AC)->set(*(const StringBase<char> *)&g_00DFE314);
	m_50 = Cos(m_1C) * g_00BC7824 * g_00DFE2C0;
	m_54 = g_Va00BCF628 * (Sin(m_1C) * g_00DFE2C0);
}

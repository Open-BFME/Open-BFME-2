// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00214F14@Rva009519B@@QAEXXZ retail 0x00214F14 426 bytes.
// Virtual slot 14 (offset 0x38) of vtable 0x007C81A8, class of
// ??1Rva009519B@@UAE@XZ. Initializes the five AsciiStrings at +0x0C +0x10
// +0x14 +0x24 +0xAC from globals via rowed StringBase<char>::set 0x000366F0,
// float/int/byte defaults from TheCloudEffectSettings, then Cos/Sin 0x0002FBC0/0x0002FBB0
// scaled into +0x50/+0x54. Evidence: same five strings as
// SubsystemDerivedDtors.cpp, callees rowed, no caller.
#include "ascii_string.h"

extern float Cos(float);
extern float Sin(float);

// The constants are retail's .rdata literals, spelled as their values:
// 0.017453292f (0x00BBB8D0, PI/180 as INI_parseAngleReal.cpp spells it),
// 0.001f (0x00BC28F8), 0.001 (double, 0x00BC6E68), -0.01f (0x00BC7824) and
// 0.01f (0x00BCF628).
static const float RADS_PER_DEGREE = 0.017453292f;

struct Block12
{
	int v[3];
};

// The CloudEffect settings record read here is the working copy at
// 0x00DFE280; INIBfmeSettingsParsers.cpp's field table (VA 0x00BE5390)
// names each member and its parser, which gives the types below.
class Rva00214E02
{
public:
	AsciiString m_cloudTexture;		// +0x00
	AsciiString m_darkCloudTexture;		// +0x04
	AsciiString m_alphaTexture;		// +0x08
	float m_propagateSpeed;			// +0x0C
	int m_angle;				// +0x10
	AsciiString m_dissipateTexture;		// +0x14
	float m_dissipateStartLevel;		// +0x18
	float m_dissipateSpeed;			// +0x1C
	Block12 m_darkeningFactor;		// +0x20
	Block12 m_darkeningFactorRain;		// +0x2C
	int m_darkeningRate;			// +0x38
	int m_lighteningRate;			// +0x3C
	float m_cloudScrollSpeed;		// +0x40
	float m_dissipateRateScale;		// +0x44
	unsigned char m_lightningShadows;	// +0x48
	unsigned char m_jitterLightningLightPosition;	// +0x49
	unsigned char m_jitterLightningLightIntensity;	// +0x4A
	float m_lightningChance;		// +0x4C
	Block12 m_lightningShadowColor;		// +0x50
	float m_lightningShadowIntensity;	// +0x5C
	Block12 m_lightningDuration;		// +0x60
	float m_lightningFrequency;		// +0x6C
	Block12 m_lightningIntensity;		// +0x70
	int m_lightningLightPosition1[2];	// +0x7C
	int m_lightningLightPosition2[2];	// +0x84
	int m_lightningLightPosition3[2];	// +0x8C
	AsciiString m_lightningFX;		// +0x94
};
extern Rva00214E02 TheCloudEffectSettings;	// 0x00DFE280

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
	((StringBase<char> *)&m_0C)->set(*(const StringBase<char> *)&TheCloudEffectSettings.m_cloudTexture);
	((StringBase<char> *)&m_10)->set(*(const StringBase<char> *)&TheCloudEffectSettings.m_darkCloudTexture);
	((StringBase<char> *)&m_14)->set(*(const StringBase<char> *)&TheCloudEffectSettings.m_alphaTexture);
	m_18 = 0.001f * TheCloudEffectSettings.m_propagateSpeed;
	m_1C = (float)TheCloudEffectSettings.m_angle * RADS_PER_DEGREE;
	((StringBase<char> *)&m_24)->set(*(const StringBase<char> *)&TheCloudEffectSettings.m_dissipateTexture);
	m_28 = TheCloudEffectSettings.m_dissipateStartLevel;
	m_2C = TheCloudEffectSettings.m_dissipateSpeed * 0.001;
	m_30 = TheCloudEffectSettings.m_darkeningFactor;
	m_3C = TheCloudEffectSettings.m_darkeningFactorRain;
	m_48 = TheCloudEffectSettings.m_darkeningRate;
	m_4C = TheCloudEffectSettings.m_lighteningRate;
	m_58 = TheCloudEffectSettings.m_dissipateRateScale;
	m_5C = TheCloudEffectSettings.m_lightningShadows;
	m_90 = TheCloudEffectSettings.m_jitterLightningLightPosition;
	m_91 = TheCloudEffectSettings.m_jitterLightningLightIntensity;
	m_60 = TheCloudEffectSettings.m_lightningChance;
	m_64 = TheCloudEffectSettings.m_lightningShadowColor;
	m_70 = TheCloudEffectSettings.m_lightningShadowIntensity;
	m_74 = TheCloudEffectSettings.m_lightningDuration;
	m_80 = TheCloudEffectSettings.m_lightningFrequency;
	m_84 = TheCloudEffectSettings.m_lightningIntensity;
	m_94 = TheCloudEffectSettings.m_lightningLightPosition1[0];
	m_98 = TheCloudEffectSettings.m_lightningLightPosition1[1];
	m_9C = TheCloudEffectSettings.m_lightningLightPosition2[0];
	m_A0 = TheCloudEffectSettings.m_lightningLightPosition2[1];
	m_A4 = TheCloudEffectSettings.m_lightningLightPosition3[0];
	m_A8 = TheCloudEffectSettings.m_lightningLightPosition3[1];
	((StringBase<char> *)&m_AC)->set(*(const StringBase<char> *)&TheCloudEffectSettings.m_lightningFX);
	m_50 = Cos(m_1C) * -0.01f * TheCloudEffectSettings.m_cloudScrollSpeed;
	m_54 = 0.01f * (Sin(m_1C) * TheCloudEffectSettings.m_cloudScrollSpeed);
}

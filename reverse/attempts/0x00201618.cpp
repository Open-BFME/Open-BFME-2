// ??0WeatherSetting@@QAE@XZ
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ??0WeatherSetting@@QAE@XZ @0x00201618 503B.
// BFME 2's WeatherSetting constructor: Zero Hour's field defaults over the
// BFME 2 layout (the same offsets as the copy assignment 0x00201412 and
// SnowManager::updateIniSettings). The two bases are the 0x10-byte
// Overridable-style base at +0 (vptr 0x00BDDC48 during construction, the
// override link and flag, the +0x0C word set to -1) and the registered module
// base Rva00200D38 at +0x10 (built from the name "Weather" through the rowed
// constructor 0x00200D38, which also files the object in the global module
// vector); the final vptrs are 0x00BE3070 and 0x00BE3064. Snow texture
// "EXSnowFlake.tga" goes through AsciiString::set; the colour at +0x8C is
// set from the packed int 0x00886655 (RGBColor::setFromInt 0x00004EDF).
#include "ascii_string.h"

class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false), m_0C(-1) {}
	virtual ~Overridable();
protected:
	Overridable *m_nextOverride;
	bool m_isOverride;
	int m_0C;
};

class Rva00200D38
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;

	Rva00200D38(const AsciiString &name);
private:
	AsciiString m_name;
};

class RGBColor
{
public:
	void setFromInt(int color);
private:
	float m_red;
	float m_green;
	float m_blue;
};

class WeatherSetting : public Overridable, public Rva00200D38
{
public:
	WeatherSetting();
	virtual ~WeatherSetting();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();

	AsciiString m_snowTexture;			// +0x18
	float m_snowFrequencyScaleX;		// +0x1C
	float m_snowFrequencyScaleY;		// +0x20
	float m_snowAmplitude;				// +0x24
	float m_snowPointSize;				// +0x28
	float m_snowMaxPointSize;			// +0x2C
	float m_snowMinPointSize;			// +0x30
	float m_snowQuadSize;				// +0x34
	float m_snowBoxDimensions;			// +0x38
	float m_snowBoxDensity;				// +0x3C
	float m_snowVelocity;				// +0x40
	bool m_usePointSprites;				// +0x44
	bool m_snowEnabled;					// +0x45
	bool m_46;
	int m_48;
	float m_4C;
	float m_50;
	bool m_54;
	int m_58;
	float m_5C;
	float m_60;
	int m_64;
	float m_68;
	bool m_6C;
	int m_70;
	float m_74;
	float m_78;
	float m_7C;
	float m_80;
	float m_84;
	float m_88;
	RGBColor m_8C;
	bool m_98;
	float m_9C;
	float m_A0;
	float m_A4;
	float m_A8;
	float m_AC;
	float m_B0;
};

WeatherSetting::WeatherSetting() : Rva00200D38(AsciiString("Weather")), m_58(0), m_5C(0.0f), m_60(0.0f)
{
	m_snowTexture = "EXSnowFlake.tga";
	m_snowFrequencyScaleX = 0.0533f;
	m_snowFrequencyScaleY = 0.0275f;
	m_snowAmplitude = 5.0f;
	m_snowPointSize = 1.0f;
	m_snowQuadSize = 0.5f;
	m_snowBoxDimensions = 200.0f;
	m_snowMaxPointSize = 64.0f;
	m_snowMinPointSize = 0.0f;
	m_snowBoxDensity = 50.0f;
	m_snowVelocity = 100.0f;
	m_usePointSprites = true;
	m_snowEnabled = false;
	m_46 = false;
	m_48 = 4;
	m_4C = 0.0f;
	m_50 = 0.0f;
	m_68 = 0.01f;
	m_54 = false;
	m_64 = 30;
	m_6C = true;
	m_70 = 200;
	m_74 = 0.3f;
	m_78 = 0.7f;
	m_7C = 0.0f;
	m_80 = 100.0f;
	m_84 = 50.0f;
	m_88 = 20.0f;
	m_8C.setFromInt(0x886655);
	m_9C = 300.0f;
	m_A0 = 1500.0f;
	m_98 = false;
	m_A4 = 660.0f;
	m_A8 = 660.0f;
	m_AC = -0.012f;
	m_B0 = -0.018f;
}

// ??0WeatherSetting@@QAE@XZ
// partial score=0.98 date=2026-10-10
// ??0WeatherSetting@@QAE@XZ
// partial score=0.98 date=2026-10-09
// ??0WeatherSetting@@QAE@XZ
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /ICode/Libraries/Include
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
#include "Lib/Coord2D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
inline void setWeatherPair(Coord2D &v,float x,float y){v.x=x;v.y=y;}

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
	Coord2D m_4C;
	volatile bool m_54;
	int m_58;
	float m_5C;
	float m_60;
	volatile int m_64;
	float m_68;
	volatile bool m_6C;
	volatile int m_70;
	volatile Coord2D m_74;
	Coord2D m_7C;
	Coord2D m_84;
	RGBColor m_8C;
	bool m_98;
	Coord2D m_9C;
	Coord2D m_A4;
	Coord2D m_AC;
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
	m_4C.x = 0.0f;
	m_4C.y = 0.0f;
	m_68 = 0.01f;
	_ReadWriteBarrier();
	m_54 = false;
	m_64 = 30;
	m_6C = true;
	m_70 = 200;
	m_74.x = 0.3f;
	m_74.y = 0.7f;
	setWeatherPair(m_7C, 0.0f, 100.0f);
	setWeatherPair(m_84, 50.0f, 20.0f);
	m_8C.setFromInt(0x886655);
	m_9C.x = 300.0f;
	m_9C.y = 1500.0f;
	m_98 = false;
	setWeatherPair(m_A4, 660.0f, 660.0f);
	setWeatherPair(m_AC, -0.012f, -0.018f);
}

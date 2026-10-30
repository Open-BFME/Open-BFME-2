// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
//
// WeatherSetting default constructor 0x00201618 (503 B, BFME 2 retail; the
// object layout matches the view Snow.cpp and WeatherSettingAssign.cpp read).
// A dedicated TU because the class view is private to this body. Codegen
// levers (target-evidence, no donor): the volatile Coord2D m_84 pair stored x
// then y puts the two movss stores in retail's order; the e20 local keeps the
// 20.0f pool load; three back-to-back _ReadWriteBarrier() after the texture
// assignment (one or two leave the 20.0f load hoisted) finish the schedule.
//
#include "ascii_string.h"
#include "Lib/Coord2D.h"
#include "Lib/RGBColor.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
inline void setWeatherPair(Coord2D &pair,float x,float y){pair.x=x;pair.y=y;}

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

class WeatherSetting;

class Rva00200D38
{
public:
	virtual WeatherSetting *rva00201153() = 0;
	virtual void rva00201085() = 0;
	virtual int Rva00201095Get() = 0;

	Rva00200D38(const AsciiString &name);
private:
	AsciiString m_name;
};

class WeatherSetting : public Overridable, public Rva00200D38
{
public:
	WeatherSetting();
	virtual ~WeatherSetting();
	virtual WeatherSetting *rva00201153();
	virtual void rva00201085();
	virtual int Rva00201095Get();

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
	volatile Coord2D m_84;
	RGBColor m_8C;
	bool m_98;
	Coord2D m_9C;
	Coord2D m_A4;
	Coord2D m_AC;
};

WeatherSetting::WeatherSetting() : Rva00200D38(AsciiString("Weather")), m_58(0), m_5C(0.0f), m_60(0.0f)
{
	m_snowTexture = "EXSnowFlake.tga";
	_ReadWriteBarrier();
	_ReadWriteBarrier();
	_ReadWriteBarrier();
	m_snowFrequencyScaleX = 0.0533f;
	m_snowFrequencyScaleY = 0.0275f;
	{
	m_snowAmplitude = 5.0f;
	m_snowPointSize = 1.0f;
	}
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
	Coord2D *p7C = &m_7C;
	p7C->x = 0.0f;
	float e20 = 20.0f;
	p7C->y = 100.0f;
	volatile Coord2D *p84 = &m_84;
	p84->x = 50.0f;
	p84->y = e20;
	m_8C.setFromInt((0x88 << 16) | (0x66 << 8) | 0x55);
	m_9C.x = 300.0f;
	m_98 = false;
	m_9C.y = 1500.0f;
	float pairX = 660.0f;
	setWeatherPair(m_A4,pairX, 660.0f);
	setWeatherPair(m_AC, -0.012f, -0.018f);
}

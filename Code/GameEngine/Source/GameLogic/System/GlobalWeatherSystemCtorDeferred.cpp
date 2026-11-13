// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Kept separate: unresolved weather lifetimes defer this constructor, not the audio routine.
#include "Common/BfmeAudioEventPrefix136.h"

// ??0GlobalWeatherSystem@@QAE@XZ @ 0x00318588 (133B): the subsystem
// constructor (vtables 0x00C0C734 / Snapshot 0x00C0C724), the same object the
// view above and parseWeatherData (0x0031842A, five 8-byte WeatherData at
// +0x30) address. Target facts: base SubsystemInterface 0x001B4E63 then the
// Snapshot base; +0x10 weather 0, +0x14 audio handle 1, +0x18 0; the +0x1C
// filter handle (rowed ctor 0x003623E5); +0x20 string/+0x28/+0x2C cleared; the
// WeatherData array through `eh vector constructor iterator' (element ctor
// 0x00318329, dtor 0x0010F149); the +0x58 bit flags (rowed ctor 0x003B31AD).
// The +0x18..+0x2C field roles are unknown; EH state 3 before the array
// shows +0x20 is an object with a destructor; its cleanup target establishes
// the AsciiString lifetime (the string's purpose remains unknown).
typedef bool Bool;
#include "subsystem_interface.h"
#include "Common/Snapshot.h"

#include "../../../Include/GameLogic/Module/Rva003623E5Member.h"

#include "../../../Include/Common/BitFlagsTemplate.h"

struct WeatherData
{
	WeatherData();
	~WeatherData();
	OpaqueRefElement4 m_weatherSound;
	bool m_hasLightning;
};

// Native array callback318329 clears the counted sound pointer and the
// byte at +4; parseWeatherData's HasLightning table uses INI::parseBool.
WeatherData::WeatherData()
{
    m_hasLightning = false;
}

// The constructor's `eh vector constructor iterator' passes 0x0010F149 as the
// element destructor: the shared 12-byte release of the counted sound pointer
// (null check, tail jump to Release_Ref 0x00050ED3), which retail ICF-folds
// with every other one-reference destructor.
WeatherData::~WeatherData()
{
}

class GlobalWeatherSystem : public SubsystemInterface, public Snapshot
{
public:
	GlobalWeatherSystem();
	virtual ~GlobalWeatherSystem();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
private:
	int m_currentWeather;		// +0x10
	int m_audioHandle;		// +0x14
	int m_18;
	Rva003623E5Member m_1C;
	// Retail unwind 0x0077A838 calls the existing AsciiString cleanup at
	// 0x0048BA39; the complete destructor at 0x00318637 uses the same member.
	AsciiString m_20;
	int m_24;
	int m_28;
	int m_2C;
	WeatherData m_weather[5];	// +0x30
	BitFlags<11> m_58;
};

GlobalWeatherSystem::GlobalWeatherSystem() : m_currentWeather(0), m_audioHandle(1), m_18(0), m_28(0), m_2C(0)
{
}

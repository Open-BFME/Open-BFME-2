// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva003184B8@Rva003184B8@@QAEXXZ @ 0x003184B8 (119B). Unlock: TheAudio removeAudioEvent on +0x14 then array +0x30 stride 8 indexed by +0x10 then handle=1 then BfmeAudioEventPrefix136 from entry with 0 then addAudioEvent slot 0x64 storing handle. Evidence: callees BfmeAudioEventPrefix136 ctor 0x002D97D6 and BfmeStringTailRecord144 dtor 0x002D9A43 rowed plus TheAudio 0x009FE6E8 plus AudioManager slots 0x64/0x6c matching Rva00358A53Audio and Rva0030D606; callers 0x00318711 0x003187A3; neighbours GlobalWeatherSystem parseWeatherData and Rva0028C6FB.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva003184B8AudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
	virtual void slot26();
	virtual void removeAudioEvent(int handle);
};

struct Rva003184B8Entry
{
	OpaqueRefElement4 ref;
	int pad04;
};

class Rva003184B8
{
public:
	void rva003184B8();
private:
	char m_pad00[0x10];
	int m_index10;
	int m_handle14;
	char m_pad18[0x10];
	int m_28;
	int m_2C;
	Rva003184B8Entry m_entries30[5];
};

void Rva003184B8::rva003184B8()
{
	reinterpret_cast<Rva003184B8AudioView *>(TheAudio)->removeAudioEvent(m_handle14);
	Rva003184B8Entry *entry = &m_entries30[m_index10];
	m_handle14 = 1;
	if (entry->ref.referent != 0) {
		BfmeAudioEventPrefix136 evt(entry->ref, 0);
		m_handle14 = reinterpret_cast<Rva003184B8AudioView *>(TheAudio)->addAudioEvent(&evt);
	}
}

// ??0GlobalWeatherSystem@@QAE@XZ @ 0x00318588 (133B): the subsystem
// constructor (vtables 0x00C0C734 / Snapshot 0x00C0C724), the same object the
// view above and parseWeatherData (0x0031842A, five 8-byte WeatherData at
// +0x30) address. Target facts: base SubsystemInterface 0x001B4E63 then the
// Snapshot base; +0x10 weather 0, +0x14 audio handle 1, +0x18 0; the +0x1C
// filter handle (rowed ctor 0x003623E5); +0x20/+0x28/+0x2C cleared; the
// WeatherData array through `eh vector constructor iterator' (element ctor
// 0x00318329, dtor 0x0010F149); the +0x58 bit flags (rowed ctor 0x003B31AD).
// The +0x18..+0x2C field roles are unknown; EH state 3 before the array
// shows +0x20 is an object with a destructor.
typedef int Bool;
#include "subsystem_interface.h"
#include "Common/Snapshot.h"

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	int m_index;
};

template <int NUMBITS> class BitFlags
{
public:
	BitFlags() throw();
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

// A cleared handle with its own teardown (EH state 3 in retail).
struct Rva00318588Handle
{
	Rva00318588Handle() : m_ptr(0) {}
	~Rva00318588Handle();
	void *m_ptr;
};

struct WeatherData
{
	WeatherData();
	~WeatherData();
	OpaqueRefElement4 m_weatherSound;
	int m_hasLightning;
};

class GlobalWeatherSystem : public SubsystemInterface, public Snapshot
{
public:
	GlobalWeatherSystem();
	virtual ~GlobalWeatherSystem();
	virtual void init();
	virtual void reset();
	virtual void update();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	int m_currentWeather;		// +0x10
	int m_audioHandle;		// +0x14
	int m_18;
	Rva003623E5Member m_1C;
	Rva00318588Handle m_20;
	int m_24;
	int m_28;
	int m_2C;
	WeatherData m_weather[5];	// +0x30
	BitFlags<11> m_58;
};

GlobalWeatherSystem::GlobalWeatherSystem() : m_currentWeather(0), m_audioHandle(1), m_18(0), m_28(0), m_2C(0)
{
}

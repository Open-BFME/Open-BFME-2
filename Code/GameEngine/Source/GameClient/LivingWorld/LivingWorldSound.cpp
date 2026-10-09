// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/ini_bfme2 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// Semantic donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldSoundParseRva0061C410.cpp.
// WB 0x01060A40 names LivingWorldSound::ParseSound; the retail INI registration
// binds LivingWorldSound to 0x003FB07D. Full native extent ends at 0x003FB3B8.
// BFME2 uses three stack arguments at Debug slot 0x6C. The sound fields and
// flag-test order are witnessed by both bodies; CreateSound keeps its existing
// opaque return type. This view describes only the fields the parser accesses.
#include "Common/INI/INI.h"
#include "region.h"
#include "Common/Snapshot.h"
#include <string.h>

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
};
class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

class Rva003FAE68Base;
class LivingWorldManager
{
public:
	Rva003FAE68Base *CreateSound(const AsciiString &name);
};
extern LivingWorldManager *TheLivingWorldManager;
extern Region2D g_00E02EAC;
extern FieldParse g_00C37938[];

struct LivingWorldSoundParseView
{
	void *m_vtable;
	AsciiString m_name;
	float m_position[3];
	void *m_audio;
	unsigned int m_flags;
	Region2D m_zoom;
};

#define REPORT_SOUND_ERROR(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			theDebug->slot60(); \
			theDebug->slot6C(0, 0, 0)->slot38("LivingWorldSound ")->slot38(token)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)
class LivingWorldSound
{
public:
    static void ParseSound(INI *ini);
};

void LivingWorldSound::ParseSound(INI *ini)
{
	const char *token = ini->getNextToken();
	if (token == 0)
		return;
	LivingWorldSoundParseView *sound;
	{
		AsciiString name(token);
		sound = (LivingWorldSoundParseView *)
			TheLivingWorldManager->CreateSound(name);
	}
	ini->initFromINI(sound, g_00C37938);
	if (!sound->m_audio)
		REPORT_SOUND_ERROR(": Sound not found");
		int count = 0;
	if (bool((sound->m_flags >> 1) & 1)) ++count;
	if (bool(sound->m_flags & 1)) ++count;
	if (bool((sound->m_flags >> 2) & 1)) ++count;
	if (count > 1)
		REPORT_SOUND_ERROR(": Flags should include at most ONE of ZOOMED_OUT, ZOOMED_IN, and ZOOMING_IN");
	if (!bool(sound->m_flags & 1) && !bool((sound->m_flags >> 2) & 1) && !sound->m_zoom.IsExactlyEqualTo(g_00E02EAC))
	{
		REPORT_SOUND_ERROR(": No point in specifying a zoom region unless you have the flag ZOOMED_IN or ZOOMING_IN");
		return;
	}
	if (sound->m_zoom.x_min > sound->m_zoom.x_max)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow X: should be less than ZoomRegionHigh X:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.x_max);
		float low = sound->m_zoom.x_min;
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.x_min) = high;
		sound->m_zoom.x_max = low;
	}
	else if (sound->m_zoom.x_min == sound->m_zoom.x_max)
		REPORT_SOUND_ERROR(": ZoomRegionLow X: is equal to ZoomRegionHigh X:. This sound cannot play");
	if (sound->m_zoom.y_min > sound->m_zoom.y_max)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow Y: should be less than ZoomRegionHigh Y:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.y_max);
		float low = sound->m_zoom.y_min;
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.y_min) = high;
		sound->m_zoom.y_max = low;
	}
	else if (sound->m_zoom.y_min == sound->m_zoom.y_max)
		REPORT_SOUND_ERROR(": ZoomRegionLow Y: is equal to ZoomRegionHigh Y:. This sound cannot play");
}

// Target 003FAE68..003FAF13, vtable C37A08, and the rowed destructor
// 003FAFB9 establish the opaque owner. The INI parser independently witnesses
// name +4, position +8, event +14, flags +18, zoom +1C. BFME1 f98983a7d
// LivingWorldSoundCopyCtor.cpp supplies the sound-subsystem interpretation;
// it does not independently prove this owner's source name. State +2C and
// three booleans +30..32 are corroborated by the rowed xfer 003FADB5.
// The flags constructor 003B31AD is a nonthrowing memset of one word.
class Rva003B31ADMember
{
public:
    __declspec(nothrow) Rva003B31ADMember();
    void clear() { memset(&m_word, 0, sizeof(m_word)); }
private:
    unsigned int m_word;
};
class OpaqueRefCounted
{
public:
    void Release_Ref();
};
struct LivingWorldSoundEvent
{
    LivingWorldSoundEvent() : value(0) {}
    ~LivingWorldSoundEvent() { if (value) value->Release_Ref(); }
    OpaqueRefCounted *value;
};
struct LivingWorldSoundPosition
{
    LivingWorldSoundPosition() : x(0), y(0), z(0) {}
    float x, y, z;
};
struct LivingWorldSoundZoom
{
    LivingWorldSoundZoom(const Region2D &r) : x_min(r.x_min), y_min(r.y_min), x_max(r.x_max), y_max(r.y_max) {}
    float x_min, y_min, x_max, y_max;
};
class Rva003FAFB9 : public Snapshot
{
public:
    Rva003FAFB9(const AsciiString &name);
    virtual ~Rva003FAFB9();
protected:
    virtual void xfer(Xfer *);
private:
    AsciiString m_name;
    LivingWorldSoundPosition m_position;
    LivingWorldSoundEvent m_event;
    Rva003B31ADMember m_flags;
    LivingWorldSoundZoom m_zoom;
    unsigned int m_state;
    bool m_shouldFade, m_isPlaying, m_hasPlayed;
};
Rva003FAFB9::Rva003FAFB9(const AsciiString &name) : m_name(name), m_zoom(g_00E02EAC)
{
    m_state = 1;
    m_shouldFade = false;
    m_isPlaying = false;
    m_hasPlayed = false;
    m_flags.clear();
}

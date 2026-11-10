// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/ini_bfme2 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// Semantic donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldSoundParseRva0061C410.cpp.
// WB 0x01060A40 names LivingWorldSound::ParseSound; the retail INI registration
// binds LivingWorldSound to 0x003FB07D. Full native extent ends at 0x003FB3B8.
// BFME2 uses three stack arguments at Debug slot 0x6C. The sound fields and
// flag-test order are witnessed by both bodies; CreateSound keeps its existing
// opaque return type. This view describes only the fields the parser accesses.
#include "ascii_string.h"
#include <float.h>
#include "../../../../Libraries/Include/Lib/Coord2DCtorView.h"
#include "../../../../Libraries/Include/Lib/Region2D.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <string.h>

// A local INI view in place of the ini_bfme2 header: this unit's own field table
// below is reached through INI::parseCoord3D (rowed 0x0002F507) and
// INI::parseCoord2D (rowed 0x0002F558), which that shared INI view does not
// declare, and every declaration kept here is one the already-verified body
// needs with the same spelling.
typedef void (*INIFieldParseProc)(class INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/INI/FieldParse.h"

// Retail's audio-event token parser, rowed and matched at RVA 0x00339900.

// The forwarder class the ledger rows at RVA 0x003FB5F2 (BitFlags-style parse
// driver over the rowed single-token worker 0x003FB3B8).
class Rva003FB508
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

#include "../../Common/debug.h"
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

class Rva003FAE68Base;
#include "../../../Include/GameLogic/LivingWorldManager.h"
extern LivingWorldManager *TheLivingWorldManager;

// Retail's LivingWorldSound parse table, VA 0x00C37938 (.rdata, file offset
// 0x00837338): five sixteen-byte FieldParse records and one zero sentinel,
// ending exactly where retail's own "ZoomRegionHigh" string begins at
// 0x00837998.  The user-data column is null in all five records, and each parse
// target is an already-rowed body, so the definition resolves rather than
// trading one unresolved name for another.
//
//   Position       INI::parseCoord3D        +0x08  -> LivingWorldSoundPosition
//   Sound          INI::parseAudioEventRTS         +0x14  -> LivingWorldSoundEvent
//   Flags          Rva003FB508::parseFromINI +0x18 -> the flag word
//   ZoomRegionLow  INI::parseCoord2D        +0x1C  -> x_min, y_min
//   ZoomRegionHigh INI::parseCoord2D        +0x24  -> x_max, y_max
//
// The two parseCoord2D records are what make the checker's "ZoomRegionLow X:
// should be less than ZoomRegionHigh X:" branch reachable - parseCoord2D writes
// X to (char *)store and Y to +4 - and `extern` on the definition keeps the
// table external, without which a const array at namespace scope takes MSVC
// internal linkage and leaves this unit's own reference to it unresolved.
extern Region2D g_00E02EAC;
extern const FieldParse g_00C37938[];
const FieldParse g_00C37938[] =
{
	{ "Position",       &INI::parseCoord3D,          0, 0x08 },
	{ "Sound",          &INI::parseAudioEventRTS,           0, 0x14 },
	{ "Flags",          &Rva003FB508::parseFromINI,  0, 0x18 },
	{ "ZoomRegionLow",  &INI::parseCoord2D,          0, 0x1C },
	{ "ZoomRegionHigh", &INI::parseCoord2D,          0, 0x24 },
	{ 0, 0, 0, 0 }
};

// Retail's default zoom region, VA 0x00E02EAC / RVA 0x00A02EAC, in .bss. This
// unit's .text$yc initializer (.CRT$XCU 0x007AFC6B, just before its BlockParse
// node 0x007AFCB4) builds it as the whole plane: two inline Coord2D temporaries,
// {+FLT_MAX, +FLT_MAX} first, then {-FLT_MAX, -FLT_MAX} (literals VA 0x00BBB8E0 /
// 0x00BBB8DC), passed to the two-endpoint constructor 0x00004C06; the inline
// empty destructor leaves a lone ret as its atexit cleanup (0x007B816A). The
// rowed constructor at 0x003FAE68 copies the four words with four movss
// instructions and the rowed checker below compares the parsed zoom against it.
Region2D g_00E02EAC(Coord2D(-FLT_MAX, -FLT_MAX), Coord2D(FLT_MAX, FLT_MAX));

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
			theDebug->SkipNext(); \
			(theDebug->CrashBegin(0, 0, 0) << "LivingWorldSound " << token << MESSAGE).CrashDone(2); \
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
	if (sound->m_zoom.lo.x > sound->m_zoom.hi.x)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow X: should be less than ZoomRegionHigh X:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.hi.x);
		float low = sound->m_zoom.lo.x;
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.lo.x) = high;
		sound->m_zoom.hi.x = low;
	}
	else if (sound->m_zoom.lo.x == sound->m_zoom.hi.x)
		REPORT_SOUND_ERROR(": ZoomRegionLow X: is equal to ZoomRegionHigh X:. This sound cannot play");
	if (sound->m_zoom.lo.y > sound->m_zoom.hi.y)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow Y: should be less than ZoomRegionHigh Y:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.hi.y);
		float low = sound->m_zoom.lo.y;
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.lo.y) = high;
		sound->m_zoom.hi.y = low;
	}
	else if (sound->m_zoom.lo.y == sound->m_zoom.hi.y)
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
#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
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
    LivingWorldSoundZoom(const Region2D &region2D) : x_min(region2D.lo.x), y_min(region2D.lo.y), x_max(region2D.hi.x), y_max(region2D.hi.y) {}
    float x_min, y_min, x_max, y_max;
};
class Rva003FAFB9 : public Snapshot
{
public:
    Rva003FAFB9(const AsciiString &name);
    virtual ~Rva003FAFB9();
protected:
	// Retail's table 0x00C37A08: slot 1 an empty body (0x000B3FD0, folded), slot 2 the name getter.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
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

// The recovered flag family shares this sound home and its region declarations.
// Flag helpers on the map-node payload whose pinned callers sit at
// 0x00213AA1..0x00213C4C, with their shared 0x003FAC83 dispatcher.
// Each body is independently byte-verified.
// Names are address-derived (see the symbols.csv pins).

class Rva003FAB93 { public: void rva003FAB93(); };
#include "../../../Include/Common/Rva003FAC3F.h"

class Rva003FAC83
{
public:
	void rva003FAC83();
	void rva003FAD9A();
	void rva003FAD2B();
	void rva003FACB4();
	void rva003FACE9(void *position);
	void rva003FAD4A(void *position);
	void rva003FADA3();

private:
	// WB 0x0105FE70 carries BitFlags<7>::test at the two call sites.
	// Its indexed mask preserves the distinct bit-zero byte read and higher shifts.
	__forceinline bool test(int bit) const
	{ return ((&m_state)[bit >> 5] & (1u << (bit & 31))) != 0; }
	char m_pad00[0x18];
	unsigned int m_state;
	char m_pad1c[0x14];
	bool m_30;
	bool m_31;
	bool m_32;
};

// Native 0x003FAC83..0x003FACB4; WB 0x0105FE70 confirms both guards
// and calls. The concrete payload and member names remain unresolved.
void Rva003FAC83::rva003FAC83()
{
	if (m_31 == 0 || m_32 == 0)
		goto checkBit5;
	if (test(4) && m_30 != 0)
		return;
	((Rva003FAB93 *)this)->rva003FAB93();
	return;
checkBit5:
	if (test(5))
		return;
	((Rva003FAC3F *)this)->rva003FAC3F();
}

// 0x003FAD9A 9B
void Rva003FAC83::rva003FAD9A()
{
	m_32 = true;
	rva003FAC83();
}

// 0x003FADA3 18B
void Rva003FAC83::rva003FADA3()
{
	m_32 = !((m_state >> 3) & 1);
	rva003FAC83();
}

// Native 0x003FAD2B..0x003FAD4A: a byte test for bit zero is distinct
// from the indexed word test. This is a read of the same little-endian flags.
void Rva003FAC83::rva003FAD2B()
{
 if (test(0) || test(2))
  m_31 = false;
 else
  m_31 = true;
 rva003FAC83();
}

// Native 0x003FACE9..0x003FAD2B; WB 0x010601F0 witnesses the
// region predicate at +0x1C and the flag-driven +0x31 update.
void Rva003FAC83::rva003FACE9(void *position)
{
 if (test(1))
  m_31 = false;
 else if (test(0) || test(2))
  m_31 = ((const Region2D *)((const char *)this + 0x1c))->isInside(*(const Coord2D *)position);
 else
  m_31 = true;
 rva003FAC83();
}

// Native 0x003FAD4A..0x003FAD9A; WB 0x01060540 adds the early
// return when the position is inside and flag two remains set.
void Rva003FAC83::rva003FAD4A(void *position)
{
 if (test(1))
  m_31 = false;
 else if (test(0) || test(2)) {
  m_31 = ((const Region2D *)((const char *)this + 0x1c))->isInside(*(const Coord2D *)position);
  if (m_31 && test(2))
   return;
 } else
  m_31 = true;
 rva003FAC83();
}

// Native 0x003FACB4..0x003FACE4; WB 0x0105FFE0 initializes all
// three state bytes before dispatching. The indexed mask helper is inlined.
void Rva003FAC83::rva003FACB4()
{
 m_30 = false;
 if (test(0) || test(2))
  m_31 = false;
 else
  m_31 = true;
 m_32 = !test(3);
 rva003FAC83();
}

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007AFCB4, node 0x00DC17EC). It is the last entry before its run's pool-init marker 0x007AFCC9,
// so it is the marker unit's own node, not a marker-less INI wrapper's; this file defines its
// callback.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theLivingWorldSoundBlockParse( "LivingWorldSound", LivingWorldSound::ParseSound );

void Rva003FAFB9::loadPostProcess()
{
}

const char *Rva003FAFB9::GetSnapshotName() const
{
	return "LivingWorldSound";
}

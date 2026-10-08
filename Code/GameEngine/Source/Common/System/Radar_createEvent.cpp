// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?createEvent@Radar@@QAEXPBUCoord3D@@W4RadarEventType@@M@Z, retail
// 0x002D88A4 (151 bytes).
// Donor (Zero Hour Radar.cpp Radar::createEvent): look the event's two
// colours up in radarColorLookupTable (terminated by RADAR_EVENT_INVALID),
// fall back to two static whites, and hand both to internalCreateEvent.
// Target evidence: WorldBuilder lead names 0x002D88A4 Radar::createEvent;
// retail walks a 0x24-byte {event, colour, colour} table at 0x00DBCD08 until
// event 0x0B (BFME 2's RADAR_EVENT_INVALID), copies the two 16-byte colours,
// falls back to the statics at 0x00DBCECC/0x00DBCEBC, and calls 0x002D8395
// with (world, type, seconds, &color[0], &color[1]) -- the Zero Hour
// internalCreateEvent argument list, pinned from this body's REL32.
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D;
class Object;

enum RadarEventType
{
	RADAR_EVENT_INVALID = 0x0B
};

struct RGBAColorInt
{
	UnsignedInt red, green, blue, alpha;
};

struct RadarColorLookup
{
	RadarEventType event;
	RGBAColorInt color1;
	RGBAColorInt color2;
};

struct Rva002D893BColorSource;

extern RadarColorLookup radarColorLookupTable[];

class Radar
{
public:
	void tryInfiltrationEvent(const Object *object);
	void createEvent(const Coord3D *world, RadarEventType type, Real secondsToLive);
	void rva002D893B(const Rva002D893BColorSource *source, const Coord3D *world, RadarEventType type, Real scale);

protected:
	void internalCreateEvent(const Coord3D *world, RadarEventType type, Real secondsToLive,
		const RGBAColorInt *color1, const RGBAColorInt *color2);
};

// Retail reads the color selector at +0x280 from argument one. Its identity
// is not established here; only this accessed offset is target evidence.
struct Rva002D893BColorSource
{
	char m_pad[0x280];
	int m_color;
};

extern void GameGetColorComponents(int color, unsigned char *a, unsigned char *b,
	unsigned char *c, unsigned char *d);
extern float g_00BC7810;

void Radar::createEvent(const Coord3D *world, RadarEventType type, Real secondsToLive)
{
	if (world == 0)
		return;

	RGBAColorInt color[2];
	int i;
	for (i = 0; radarColorLookupTable[i].event != RADAR_EVENT_INVALID; ++i)
	{
		if (radarColorLookupTable[i].event == type)
		{
			color[0] = radarColorLookupTable[i].color1;
			color[1] = radarColorLookupTable[i].color2;
			break;
		}
	}

	if (radarColorLookupTable[i].event == RADAR_EVENT_INVALID)
	{
		static RGBAColorInt color1 = { 255, 255, 255, 255 };
		static RGBAColorInt color2 = { 255, 255, 255, 255 };

		color[0] = color1;
		color[1] = color2;
	}

	internalCreateEvent(world, type, secondsToLive, &color[0], &color[1]);
}

void Radar::rva002D893B(const Rva002D893BColorSource *source, const Coord3D *world,
	RadarEventType type, Real scale)
{
	if (source == 0 || world == 0)
		return;

	unsigned char alpha, blue, green, red;
	GameGetColorComponents(source->m_color, &alpha, &blue, &green, &red);
	RGBAColorInt color[2];
	color[0].red = alpha;
	color[0].green = blue;
	color[0].blue = green;
	color[0].alpha = red;
	color[1] = color[0];
	color[1].red += (UnsignedInt)(color[0].red * g_00BC7810);
	color[1].green += (UnsignedInt)(color[0].green * g_00BC7810);
	color[1].blue += (UnsignedInt)(color[0].blue * g_00BC7810);
	internalCreateEvent(world, type, scale, &color[0], &color[1]);
}

// Target 002D8A1B..002D8AF7, RET4: the RADAR:Infiltration literal,
// event kind4 and Object owner comparison independently establish the donor
// purpose. BFME1@9cbfb551fe20 RadarTryInfiltrationEvent.cpp provides control
// flow; target uses a local 136-byte event, MiscAudio ref+8 and UI/audio slots
// 3C/138/64 instead of the donor's static sound and slots30/124/44.
class Player;
class Object
{
public:
    Player *getControllingPlayer() const;
};
class BfmeMemberRV;
class BfmeThingRV
{
public:
    BfmeMemberRV *bfmePickRV();
};
class PlayerList;
extern PlayerList *ThePlayerList;
class InGameUI;
extern InGameUI *TheInGameUI;
class AudioManager;
extern AudioManager *TheAudio;

#define INFILTRATION_SLOT(n) virtual void slot##n();
class RadarInfiltrationUI
{
public:
    INFILTRATION_SLOT(0)
    INFILTRATION_SLOT(1)
    INFILTRATION_SLOT(2)
    INFILTRATION_SLOT(3)
    INFILTRATION_SLOT(4)
    INFILTRATION_SLOT(5)
    INFILTRATION_SLOT(6)
    INFILTRATION_SLOT(7)
    INFILTRATION_SLOT(8)
    INFILTRATION_SLOT(9)
    INFILTRATION_SLOT(10)
    INFILTRATION_SLOT(11)
    INFILTRATION_SLOT(12)
    INFILTRATION_SLOT(13)
    INFILTRATION_SLOT(14)
    virtual void __cdecl message(AsciiString label, ...);
};
struct RadarInfiltrationMiscAudio
{
    char opaque00[8];
    OpaqueRefElement4 sound;
};
class RadarInfiltrationAudio
{
public:
    INFILTRATION_SLOT(0)
    INFILTRATION_SLOT(1)
    INFILTRATION_SLOT(2)
    INFILTRATION_SLOT(3)
    INFILTRATION_SLOT(4)
    INFILTRATION_SLOT(5)
    INFILTRATION_SLOT(6)
    INFILTRATION_SLOT(7)
    INFILTRATION_SLOT(8)
    INFILTRATION_SLOT(9)
    INFILTRATION_SLOT(10)
    INFILTRATION_SLOT(11)
    INFILTRATION_SLOT(12)
    INFILTRATION_SLOT(13)
    INFILTRATION_SLOT(14)
    INFILTRATION_SLOT(15)
    INFILTRATION_SLOT(16)
    INFILTRATION_SLOT(17)
    INFILTRATION_SLOT(18)
    INFILTRATION_SLOT(19)
    INFILTRATION_SLOT(20)
    INFILTRATION_SLOT(21)
    INFILTRATION_SLOT(22)
    INFILTRATION_SLOT(23)
    INFILTRATION_SLOT(24)
    virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
    INFILTRATION_SLOT(26)
    INFILTRATION_SLOT(27)
    INFILTRATION_SLOT(28)
    INFILTRATION_SLOT(29)
    INFILTRATION_SLOT(30)
    INFILTRATION_SLOT(31)
    INFILTRATION_SLOT(32)
    INFILTRATION_SLOT(33)
    INFILTRATION_SLOT(34)
    INFILTRATION_SLOT(35)
    INFILTRATION_SLOT(36)
    INFILTRATION_SLOT(37)
    INFILTRATION_SLOT(38)
    INFILTRATION_SLOT(39)
    INFILTRATION_SLOT(40)
    INFILTRATION_SLOT(41)
    INFILTRATION_SLOT(42)
    INFILTRATION_SLOT(43)
    INFILTRATION_SLOT(44)
    INFILTRATION_SLOT(45)
    INFILTRATION_SLOT(46)
    INFILTRATION_SLOT(47)
    INFILTRATION_SLOT(48)
    INFILTRATION_SLOT(49)
    INFILTRATION_SLOT(50)
    INFILTRATION_SLOT(51)
    INFILTRATION_SLOT(52)
    INFILTRATION_SLOT(53)
    INFILTRATION_SLOT(54)
    INFILTRATION_SLOT(55)
    INFILTRATION_SLOT(56)
    INFILTRATION_SLOT(57)
    INFILTRATION_SLOT(58)
    INFILTRATION_SLOT(59)
    INFILTRATION_SLOT(60)
    INFILTRATION_SLOT(61)
    INFILTRATION_SLOT(62)
    INFILTRATION_SLOT(63)
    INFILTRATION_SLOT(64)
    INFILTRATION_SLOT(65)
    INFILTRATION_SLOT(66)
    INFILTRATION_SLOT(67)
    INFILTRATION_SLOT(68)
    INFILTRATION_SLOT(69)
    INFILTRATION_SLOT(70)
    INFILTRATION_SLOT(71)
    INFILTRATION_SLOT(72)
    INFILTRATION_SLOT(73)
    INFILTRATION_SLOT(74)
    INFILTRATION_SLOT(75)
    INFILTRATION_SLOT(76)
    INFILTRATION_SLOT(77)
    virtual const RadarInfiltrationMiscAudio *getMiscAudio();
};
#undef INFILTRATION_SLOT
class Rva0033F15DDwordSlot
{
public:
    void set(int value);
};
struct RadarInfiltrationPlayer
{
    char opaque00[0x54];
    int index;
};
void Radar::tryInfiltrationEvent(const Object *object)
{
    Player *owner = object->getControllingPlayer();
    if (owner != reinterpret_cast<Player *>(reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV()))
        return;
    createEvent(reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(object) + 0x38),
        static_cast<RadarEventType>(4), 4.0f);
    RadarInfiltrationPlayer *player = reinterpret_cast<RadarInfiltrationPlayer *>(
        reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV());
    if (player == 0)
        return;
    reinterpret_cast<RadarInfiltrationUI *>(TheInGameUI)->message("RADAR:Infiltration");
    BfmeAudioEventPrefix136 sound(reinterpret_cast<RadarInfiltrationAudio *>(TheAudio)->getMiscAudio()->sound, 0);
    reinterpret_cast<Rva0033F15DDwordSlot *>(&sound)->set(player->index);
    reinterpret_cast<RadarInfiltrationAudio *>(TheAudio)->addAudioEvent(&sound);
}

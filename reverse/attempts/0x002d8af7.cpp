// ?tryEvent@Radar@@QAE_NW4RadarEventType@@PBUCoord3D@@@Z
// partial score=0.9 date=2026-10-08
// ?tryEvent@Radar@@QAE_NW4RadarEventType@@PBUCoord3D@@@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
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
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D { Real x, y, z; };

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

struct BfmeRadarEventRecord
{
    RadarEventType type;
    char opaque04[4];
    UnsignedInt createFrame;
    char opaque0C[0x28];
    Coord3D worldLoc;
    char opaque40[0x10];
};

class GameClient;
extern GameClient *TheGameClient;
extern int g_009BA4E8;

// Same frame interface used by DrawableFade.cpp: retail calls slot +0x7C.
class Rva00DFE77CHolder
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
    virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual UnsignedInt slot1F();
};

extern RadarColorLookup radarColorLookupTable[];

class Radar
{
public:
	void createEvent(const Coord3D *world, RadarEventType type, Real secondsToLive);
	void rva002D893B(const Rva002D893BColorSource *source, const Coord3D *world, RadarEventType type, Real scale);
    bool tryEvent(RadarEventType type, const Coord3D *world);

protected:
	void internalCreateEvent(const Coord3D *world, RadarEventType type, Real secondsToLive,
		const RGBAColorInt *color1, const RGBAColorInt *color2);
private:
    char opaque00[0x2C];
    BfmeRadarEventRecord m_event[64];
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

// ZH Radar.cpp::tryEvent and BFME1 9cbfb551f RadarTryEvent.cpp supply the
// semantic lead. Target 002D8AF7..002D8B9D, RET 8, rejects event>=11/null,
// scans 64 records at this+2C with stride50 and frame+8/location+34, compares
// true squared distance to 360000, and calls the matched createEvent with
// lifetime 4.0f. Caller 002D8B9D uses this helper after its object checks.
// Unlike the donor expression, the target squares the two coordinate deltas.
bool Radar::tryEvent(RadarEventType type, const Coord3D *world)
{
    if (type >= RADAR_EVENT_INVALID || world == 0)
        return false;

    UnsignedInt currentFrame = ((Rva00DFE77CHolder *)TheGameClient)->slot1F();
    const UnsignedInt framesBetweenEvents = g_009BA4E8 * 10;
    BfmeRadarEventRecord *event = m_event;
    for (int i = 0; i < 64; ++i, ++event)
    {
        if (event->type == type)
        {
            const Real *posY = &world->y;
            Real distSquared = (world->x - event->worldLoc.x) *
                               (world->x - event->worldLoc.x) +
                               (*posY - event->worldLoc.y) *
                               (*posY - event->worldLoc.y);
            if (distSquared <= 360000.0f)
            {
                if (currentFrame - event->createFrame < framesBetweenEvents)
                    return false;
            }
        }
    }
    createEvent(world, type, 4.0f);
    return true;
}

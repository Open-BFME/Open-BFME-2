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

struct Coord3D;

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

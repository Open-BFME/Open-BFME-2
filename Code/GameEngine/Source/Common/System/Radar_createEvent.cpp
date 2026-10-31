// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
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

#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object;

// Event values with target evidence: construction 1 (DozerAIUpdate), battle
// plan 7 (BattlePlanUpdate), stealth discovered/neutralized 8/9
// (InvisibilityManager), invalid 0x0B (this table's terminator). The other
// slots keep their numbers; their colours are Zero Hour's but their names are
// not established for BFME 2.
enum RadarEventType
{
	RADAR_EVENT_CONSTRUCTION = 1,
	RADAR_EVENT_BATTLE_PLAN = 7,
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9,
	RADAR_EVENT_INVALID = 0x0B
};

struct RGBAColorInt
{
	unsigned int red, green, blue, alpha;
};

struct RadarColorLookup
{
	RadarEventType event;
	RGBAColorInt color1;
	RGBAColorInt color2;
};

struct Rva002D893BColorSource;

class RadarEventRef;
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
class RadarEventRefSlot
{
public:
	void clearRef();
	RadarEventRef *m_ref; // +0x00
};

class RadarEvent
{
public:
    RadarEvent();
    ~RadarEvent();
    RadarEventType type;
    bool active;
    unsigned int createFrame;
    unsigned int dieFrame;
    unsigned int fadeFrame;
    RGBAColorInt color1;
    RGBAColorInt color2;
    Coord3D worldLoc;
    ICoord2D radarLoc;
    bool soundPlayed;
    RadarEventRefSlot ref; // +0x4C
};

class GameClient;
extern GameClient *TheGameClient;
extern int BfmeClientFramesPerSecond;

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



// Zero Hour's colour table (retail rva 0x009BCD08, 12 x 36 B): BFME 2 adds slot 0
// and moves the terminator to 0x0B; slot 4 carries Zero Hour's infiltration
// colours and slots 5/6 its information/beacon colours.
RadarColorLookup radarColorLookupTable[] =
{
	{ (RadarEventType)0,                 { 255, 255,   0, 255 },  { 255, 255, 128, 255 } },
	{ RADAR_EVENT_CONSTRUCTION,          { 128, 128, 255, 255 },  { 128, 255, 255, 255 } },
	{ (RadarEventType)2,                 { 128,   0,  64, 255 },  { 255, 185, 220, 255 } },
	{ (RadarEventType)3,                 { 255,   0,   0, 255 },  { 255, 128, 128, 255 } },
	{ (RadarEventType)4,                 {   0, 255, 255, 255 },  { 128, 255, 255, 255 } },
	{ (RadarEventType)5,                 { 255, 255,   0, 255 },  { 255, 255, 128, 255 } },
	{ (RadarEventType)6,                 { 255, 255,   0, 255 },  { 255, 255, 128, 255 } },
	{ RADAR_EVENT_BATTLE_PLAN,           { 255, 255, 255, 255 },  { 255, 255, 255, 255 } },
	{ RADAR_EVENT_STEALTH_DISCOVERED,    {   0, 255,   0, 255 },  {   0, 128,   0, 255 } },
	{ RADAR_EVENT_STEALTH_NEUTRALIZED,   {   0, 255,   0, 255 },  {   0, 128,   0, 255 } },
	{ (RadarEventType)10,                {   0,   0,   0,   0 },  {   0,   0,   0,   0 } },
	{ RADAR_EVENT_INVALID,               {   0,   0,   0,   0 },  {   0,   0,   0,   0 } }
};

class Object;
class RadarObject;
class GameWindow;
class TerrainLogic;
class RadarEventRef;
struct Rva002D76C6Owner;
struct Rva002D76C6Node;
struct Rva002D893BColorSource;
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
typedef float Real;
typedef int Int;
typedef bool Bool;
enum RadarPriorityType { RADAR_PRIORITY_INVALID, RADAR_PRIORITY_NOT_ON_RADAR, RADAR_PRIORITY_STRUCTURE, RADAR_PRIORITY_UNIT, RADAR_PRIORITY_LOCAL_UNIT_ONLY };
struct RadarExtent
{
	Real minX;
	Real minY;
	Int reserved;
	Real maxX;
	Real maxY;

	Real width() const { return maxX - minX; }
	Real height() const { return maxY - minY; }
};

struct RadarRect16
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"
class Radar : public Snapshot
{
public:

    Radar();
    virtual ~Radar();
    void rva002D790A(float *widthRatio, float *heightRatio);
    bool screenPixelToWorld(const ICoord2D *pixel, Coord3D *world);
    Object *objectUnderRadarPixel(const ICoord2D *pixel);
    void removeObject(Rva002D76C6Owner *owner);
    bool rva002D76C6(Rva002D76C6Owner *owner, Rva002D76C6Node **head);
    bool tryEvent(RadarEventType type, const Coord3D *world);
    void tryUnderAttackEvent(const Object *object);
    void tryInfiltrationEvent(const Object *object);
    void createEvent(const Coord3D *world, RadarEventType type, float secondsToLive);
    void createPlayerEvent(const Rva002D893BColorSource *source, const Coord3D *world, RadarEventType type, float scale);
	void newMap();
	bool radarToWorld(const ICoord2D *, Coord3D *);
	void rva002D7E68(void *);
	bool isPriorityVisible(RadarPriorityType priority) const;
	void addObject(Object *object);
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	bool rva002D782C(const Coord3D *world, Coord2D *radar);
	Object *searchListForRadarLocationMatch(RadarObject *list, ICoord2D *target);
	void findDrawPositions(Int startX, Int startY, Int width, Int height,
		ICoord2D *ul, ICoord2D *lr);
	virtual void refreshTerrain(TerrainLogic *terrain);
	virtual void queueTerrainRefresh();
	virtual void loadPostProcess();
	virtual void s06();
	virtual void s07();
	virtual void s09();
	virtual void s10(int a, int b, int c);
	virtual void s11();
	virtual void s12(int a, int b, int c);
	void rva002D7BB7(void const *src);
	Bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);

protected:
	void deleteListResources();
	void internalCreateEvent(const Coord3D *world, RadarEventType type, float secondsToLive,
		const RGBAColorInt *color1, const RGBAColorInt *color2);
	virtual void xfer(Xfer *);
private:
	unsigned char m_pad04[0x0C];
	bool m_hidden;
	bool m_forceOn;
	char m_pad12[2];
	RadarObject *m_objectList;
	RadarObject *m_localObjectList;
	float m_averageTerrainZ; // +0x1C: native ground sample accumulator
	float m_averageWaterZ; // +0x20: native underwater sample accumulator
	float m_xSample; // +0x24
	float m_ySample; // +0x28
	RadarEvent m_events[64]; // native 80-byte event stride
	int m_nextFree; // +0x142C
	GameWindow *m_radarWindow; // +0x1430
	RadarExtent m_extent; // +0x1434..+0x1447
	char m_pad1448[0x144C - 0x1448];
	RadarRect16 m_rect; // +0x144C 16B copied from arg
	unsigned char m_dirty; // +0x145C
	char m_pad145D[0x1460 - 0x145D];
	unsigned int m_queueTerrainRefreshFrame;
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

void Radar::createPlayerEvent(const Rva002D893BColorSource *source, const Coord3D *world,
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
	color[1].red += (UnsignedInt)(color[0].red * -0.75f);
	color[1].green += (UnsignedInt)(color[0].green * -0.75f);
	color[1].blue += (UnsignedInt)(color[0].blue * -0.75f);
	internalCreateEvent(world, type, scale, &color[0], &color[1]);
}

// Target 002D8A1B..002D8AF7, RET4: the RADAR:Infiltration literal,
// event kind4 and Object owner comparison independently establish the donor
// purpose. BFME1@9cbfb551fe20 RadarTryInfiltrationEvent.cpp provides control
// flow; target uses a local 136-byte event, MiscAudio ref+8 and UI/audio slots
// 3C/138/64 instead of the donor's static sound and slots30/124/44.
class Player;
class Player;
class RadarObject;
class Team;
class Rva00373EC6;
class Object
{
public:
	Object *getNextObject() { return m_next; }
	void friend_setRadarData(RadarObject *data) { m_radarData = data; }
	ObjectID getID() const { return m_id; }
	bool isNeutralControlled() const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	int getIndicatorColor() const;
	bool isLocallyControlled() const;
	unsigned char m_pad0[4];
	void *m_4;
	unsigned char m_pad8[0x38-8];
	Coord3D m_pos; // +0x38, retained for the existing list search
	unsigned char m_pad44[0x74-0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x8C-0x78];
	Object *m_next; // +0x8C
	unsigned char m_pad90[0x94-0x90];
	unsigned int m_destroyed; // native load-side radar guard
	unsigned char m_pad98[0x250-0x98];
	void *m_250;
	unsigned char m_pad254[0x260-0x254];
	RadarObject *m_radarData;
	unsigned char m_pad264[0x304-0x264];
	Team *m_304;
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

class RadarInfiltrationUI
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
    virtual void __cdecl message(AsciiString label, ...);
};
struct RadarInfiltrationMiscAudio
{
    OpaqueRefElement4 harvesterSound;    // +0x00, the under-attack event's harvester case
    OpaqueRefElement4 underAttackSound;  // +0x04, its unit, structure and default cases
    OpaqueRefElement4 sound;
};
class RadarInfiltrationAudio
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
    virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual const RadarInfiltrationMiscAudio *getMiscAudio();
};
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
    const UnsignedInt framesBetweenEvents = BfmeClientFramesPerSecond * 10;
    RadarEvent *event = m_events;
    for (int i = 0; i < 64; ++i, ++event)
    {
        if (event->type == type)
        {
            Real dx=world->x-event->worldLoc.x; Real dy=world->y-event->worldLoc.y; Real distSquared=dx*dx+dy*dy;
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

// Zero Hour Radar::tryUnderAttackEvent is the semantic guide. Target
// 002D8B9D..002D8DC7 (WB 11096E0 twin): after tryEvent(3, position) succeeds
// it refreshes the control bar (0x0031AEC9), then picks the message and sound
// from the object's template kind bits 8/9 (unit, with bit 16 the harvester
// case), 7 and 37 (structure), else the generic message, and plays the sound
// for the local player. Retail tests every kind bit as its own byte test;
// the early-return spelling of the test keeps MSVC from merging bits 8 and 9.
class ControlBar {public: void rva0031AEC9();};
extern ControlBar *TheControlBar;
struct RadarAttackTemplate {char opaque[0x108];unsigned char kind[16];};
struct RadarAttackObject {void *vtable;const RadarAttackTemplate *objectTemplate;};
struct RadarAttackPlayerList {char opaque[0x10];RadarInfiltrationPlayer *localPlayer;};
__forceinline bool radarObjectKind(const Object *object,int kind) {
 const unsigned char *k=((const RadarAttackObject *)object)->objectTemplate->kind;
 if (k[kind>>3] & (1<<(kind&7))) return true;
 return false;
}
struct RadarAttackRef : OpaqueRefElement4 {
 RadarAttackRef() {referent=0;}
 ~RadarAttackRef() {if(referent)referent->Release_Ref();}
};
void Radar::tryUnderAttackEvent(const Object *object)
{
 if(object==0) return;
 if(tryEvent((RadarEventType)3,(const Coord3D *)((const char *)object+0x38))) {
  TheControlBar->rva0031AEC9();
  RadarInfiltrationPlayer *player=((RadarAttackPlayerList *)ThePlayerList)->localPlayer;
  if(radarObjectKind(object,8)||radarObjectKind(object,9))
  {
   RadarAttackRef ref;
   if(radarObjectKind(object,16)) {
    ((RadarInfiltrationUI *)TheInGameUI)->message("RADAR:HarvesterUnderAttack");
    ref.OpaqueRefElement4::operator=(((RadarInfiltrationAudio *)TheAudio)->getMiscAudio()->harvesterSound);
   } else {
    ((RadarInfiltrationUI *)TheInGameUI)->message("RADAR:UnitUnderAttack");
    ref.OpaqueRefElement4::operator=(((RadarInfiltrationAudio *)TheAudio)->getMiscAudio()->underAttackSound);
   }
   BfmeAudioEventPrefix136 sound(ref,0);
   ((Rva0033F15DDwordSlot *)&sound)->set(player->index);
   ((RadarInfiltrationAudio *)TheAudio)->addAudioEvent(&sound);
  }
  else if(radarObjectKind(object,7)&&radarObjectKind(object,37))
  {
   ((RadarInfiltrationUI *)TheInGameUI)->message("RADAR:StructureUnderAttack");
   BfmeAudioEventPrefix136 sound(((RadarInfiltrationAudio *)TheAudio)->getMiscAudio()->underAttackSound,0);
   ((Rva0033F15DDwordSlot *)&sound)->set(player->index);
   ((RadarInfiltrationAudio *)TheAudio)->addAudioEvent(&sound);
  }
  else
  {
   ((RadarInfiltrationUI *)TheInGameUI)->message("RADAR:UnderAttack");
   BfmeAudioEventPrefix136 sound(((RadarInfiltrationAudio *)TheAudio)->getMiscAudio()->underAttackSound,0);
   ((Rva0033F15DDwordSlot *)&sound)->set(player->index);
   ((RadarInfiltrationAudio *)TheAudio)->addAudioEvent(&sound);
  }
 }
}

// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD
// platformsdk
// Radar conversions and event initialization. Native2D8395..2D84F6 and
// named createEvent callers establish the new353B member and50-byte records.
// The visible inline+noinline worldToRadar body keeps its own99B exact and
// exposes output-temp behavior to the caller; the old133B conversion stays exact.
// Frame-rate access reuses the existing30-valued global owner. The writable
// fade multiplier below has target-observed initial0.5 and current usage;
// its descriptive name is not an original identifier claim.

#include <windows.h>
#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "Code/Libraries/Include/Lib/Coord3D.h"

class BfmeTerrainHeightView
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual float getGroundHeight(float x, float y, Coord3D *normal = NULL);
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct RGBAColorInt
{
	unsigned int red, green, blue, alpha;
};
enum RadarEventType
{
	RADAR_EVENT_CONSTRUCTION = 1,
	RADAR_EVENT_BATTLE_PLAN = 7,
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9,
	RADAR_EVENT_INVALID = 0x0B
};

class ClientFrameSubsystem
{
public:
	virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
	virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
	virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
	virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
	virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
	virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
	virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
	virtual int v28(); virtual int v29(); virtual int v30();
	virtual int getFrame();
};

class GameClient;extern GameClient *TheGameClient;

extern int BfmeClientFramesPerSecond;
float BfmeRadarEventFadeFraction=0.5f;

class RadarEventRef
{
public:
	void release();
	virtual void m_spare0();
	virtual void m_deleter();
private:
	int m_refCount; // +0x04
};

class RadarEventRefSlot
{
public:
	void clearRef();
	RadarEventRef *m_ref; // +0x00
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
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
#include "../../../../Libraries/Include/Lib/Coord3D.h"
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

// ?radarToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z
bool Radar::radarToWorld(const ICoord2D *radar, Coord3D *world)
{
	if (radar == NULL || world == NULL)
		return false;

	int x = radar->x;
	int y = radar->y;
	if (x < 0)
		x = 0;
	if (x >= 128)
		x = 128 - 1;
	if (y < 0)
		y = 0;
	if (y >= 128)
		y = 128 - 1;

	world->x = x * m_xSample;
	world->y = y * m_ySample;

	BfmeTerrainHeightView *terrain = (BfmeTerrainHeightView *)TheTerrainLogic;
	world->z = terrain->getGroundHeight(world->x, world->y);

	return true;
}

inline __declspec(noinline) bool Radar::worldToRadar(const Coord3D *world, ICoord2D *radar)
{
	if (world == NULL || radar == NULL)
		return false;

	radar->x = (int)(world->x / m_xSample);
	radar->y = (int)(world->y / m_ySample);

	if (radar->x < 0)
		radar->x = 0;
	if (radar->x >= 128)
		radar->x = 128 - 1;
	if (radar->y < 0)
		radar->y = 0;
	if (radar->y >= 128)
		radar->y = 128 - 1;

	return true;
}
// ?TheTerrainLogic@@3PAVBfmeTerrainHeightView@@A: the global at VA 0xdfec50 is ?TheTerrainLogic@@3PAVTerrainLogic@@A.

void Radar::internalCreateEvent(const Coord3D *pos, RadarEventType tag, float scale, const RGBAColorInt *rGBAColorInt, const RGBAColorInt *b)
{
 ICoord2D tmp; if(!pos||!rGBAColorInt||!b)return; worldToRadar(pos,&tmp);
 m_events[m_nextFree].type=tag;
 m_events[m_nextFree].active=true;
 m_events[m_nextFree].createFrame=reinterpret_cast<ClientFrameSubsystem*>(TheGameClient)->getFrame();
 m_events[m_nextFree].dieFrame=(unsigned int)((float)(unsigned)reinterpret_cast<ClientFrameSubsystem*>(TheGameClient)->getFrame()+(float)BfmeClientFramesPerSecond*scale);
 m_events[m_nextFree].fadeFrame=(unsigned int)((float)m_events[m_nextFree].dieFrame-(float)BfmeClientFramesPerSecond*BfmeRadarEventFadeFraction);
 m_events[m_nextFree].color1=*rGBAColorInt;
 m_events[m_nextFree].color2=*b;
 m_events[m_nextFree].worldLoc=*pos;
 m_events[m_nextFree].radarLoc=tmp;
 m_events[m_nextFree].soundPlayed=false;
 m_events[m_nextFree].ref.clearRef();
 if(++m_nextFree>=64)m_nextFree=0;
}


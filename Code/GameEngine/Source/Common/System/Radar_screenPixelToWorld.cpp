// cl: /DNDEBUG /MD
// platformsdk
//
// ?screenPixelToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z,
// retail 0x002D82E4, 106 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// matched 126 bytes there): null-guard the arguments, bail when there is no
// radar window, translate the screen pixel into a window-local pixel via the
// GameWindow, then fold through the local-pixel-to-radar and radar-to-world
// helpers. BFME2 keeps the radar window at Radar+0x1430 (proven by the
// landed Radar::newMap); the 20-byte delta is under investigation.

#include <windows.h>
#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class GameWindow
{
public:
	int winGetSize(int *width, int *height);
	int winGetScreenPosition(int *x, int *y);
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
enum RadarEventType
{
	RADAR_EVENT_CONSTRUCTION = 1,
	RADAR_EVENT_BATTLE_PLAN = 7,
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9,
	RADAR_EVENT_INVALID = 0x0B
};
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

class RadarEventRefSlot
{
public:
	void clearRef();
	RadarEventRef *m_ref; // +0x00
};

struct RGBAColorInt
{
	unsigned int red, green, blue, alpha;
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

// ?screenPixelToWorld@Radar@@QAE_NPBUICoord2D@@PAUCoord3D@@@Z
bool Radar::screenPixelToWorld(const ICoord2D *pixel, Coord3D *world)
{
	if (pixel == NULL || world == NULL)
		return false;

	if (m_radarWindow == NULL)
		return false;

	ICoord2D localPixel;
	ICoord2D screenPos;
	m_radarWindow->winGetScreenPosition(&screenPos.x, &screenPos.y);
	localPixel.x = pixel->x - screenPos.x;
	localPixel.y = pixel->y - screenPos.y;

	ICoord2D radar;
	if (localPixelToRadar(&localPixel, &radar) == false)
		return false;

	return radarToWorld(&radar, world);
}

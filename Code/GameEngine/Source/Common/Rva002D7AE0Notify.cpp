// cl: /O1 /DNDEBUG /MD /Oy-
//
// ?rva002D7AE0@@YAXHHH@Z @0x002D7AE0 56B and ?rva002D7B18@@YAXHHH@Z
// @0x002D7B18 56B: twin notification posts (cdecl, 3 int args, void).
// Each forwards (a, b, c) to a virtual on TheDisplay (slots 0x130 / 0x13c,
// null-guarded) then to TheRadar slot 0x24 / 0x2c (null-guarded).
// Display/Radar views use the numbered-placeholder idiom for slot
// resolution; /Oy- keeps the ebp frame retail has with no locals.
// Exact identities unproven, honest address-derived names.
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75();
	virtual void v76(int a, int b, int c);
	virtual void v77();
	virtual void v78();
	virtual void v79(int a, int b, int c);
};
extern Display *TheDisplay;

class Object;
class RadarObject;
class GameWindow;
class TerrainLogic;
class RadarEventRef;
struct Rva002D76C6Owner;
struct Rva002D76C6Node;
struct Rva002D893BColorSource;
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
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
extern Radar *TheRadar;

// ?rva002D7AE0@@YAXHHH@Z
void __cdecl rva002D7AE0(int a, int b, int c)
{
	if (TheDisplay != 0)
		TheDisplay->v76(a, b, c);
	if (TheRadar != 0)
		TheRadar->s10(a, b, c);
}

// ?rva002D7B18@@YAXHHH@Z
void __cdecl rva002D7B18(int a, int b, int c)
{
	if (TheDisplay != 0)
		TheDisplay->v79(a, b, c);
	if (TheRadar != 0)
		TheRadar->s12(a, b, c);
}

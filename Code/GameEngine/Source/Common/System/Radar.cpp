// cl: /O1 /DNDEBUG /MD /arch:SSE
// platformsdk
// Radar.cpp: Radar bodies retail links from this TU (tu_map approved), folded
// from six split units that shared these exact flags. The canonical Snapshot
// base and retained field view preserve every verified Radar offset:
//   +0x24/+0x28 x/y sample, +0x1430 radar window, +0x1434 draw extent,
//   +0x144C draw rect, +0x145C dirty byte, +0x1460 cleared dword.
// Bodies that reach Radar through its second base (the frame tick at
// 0x002D7DD5) keep their own unit, since their `this` is that subobject.

typedef bool Bool;
typedef int Int;
typedef float Real;

#define BFME_SNAPSHOT_NAME_SLOT
#include <windows.h>
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class GameWindow
{
public:
	int winGetSize(int *width, int *height);
	int winGetScreenPosition(int *x, int *y);
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

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;


class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Object;
class RadarObject;
class Team;
class Player;
class PlayerList;
class BfmeMemberRV;
class Rva00373EC6;

enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};

class Rva0028E58E
{
public:
	int rva0028E58E();
};

enum RadarPriorityType { RADAR_PRIORITY_INVALID, RADAR_PRIORITY_NOT_ON_RADAR, RADAR_PRIORITY_STRUCTURE, RADAR_PRIORITY_UNIT, RADAR_PRIORITY_LOCAL_UNIT_ONLY };
int __cdecl rva002D7BFD(int v);

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class BfmeMemberRV
{
public:
	bool bfmeAskRV();
	unsigned char m_pad[0x2EC];
	Team *m_team; // +0x2EC
};

class PlayerList : public BfmeThingRV
{
public:
	Player *getNthPlayer(int i);
};

extern PlayerList *ThePlayerList;

class Player
{
public:
	Relationship getRelationship(const Team *t) const;
	char m_pad00[0x280];
	int m_280; // +0x280
};

class Player;
class RadarObject;
class Team;
class Rva00373EC6;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"
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

class Rva00373EC6
{
public:
	unsigned char m_pad[0x38];
	int m_38; // +0x38
	int m_3C; // +0x3C
};

struct I250Vtbl
{
	virtual void _V00();
	virtual void _V01();
	virtual void _V02();
	virtual void _V03();
	virtual void _V04();
	virtual void _V05();
	virtual void _V06();
	virtual void _V07();
	virtual void _V08();
	virtual void _V09();
	virtual void _V10();
	virtual void _V11();
	virtual void _V12();
	virtual void _V13();
	virtual void _V14();
	virtual void _V15();
	virtual void _V16();
	virtual void _V17();
	virtual void _V18();
	virtual int getV(void *p);
};

// Native C035D0: deleting destructor, empty post-load, name getter,
// and the owned RadarObject::xfer. Snapshot contributes the witnessed
// BBB554 base lifetime; all object/next/color offsets remain 4/8/C.
class RadarObject : public Snapshot
{
public:
	RadarObject();
	RadarObject *friend_getNext() const { return m_next; }
	virtual ~RadarObject();
	Object *m_object;
	RadarObject *m_next;
	int m_color;
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
};

// ?RadarObject::RadarObject present-unmatched
inline RadarObject::RadarObject()
{
	m_object=0;
	m_next=0;
	m_color=-1;
}

// Native terrain vslots 6/9/19: height, extent and underwater query.
// The full 326-byte consumer proves these calls and offsets; the declarations
// retain the banked ABI view rather than asserting the original method names.
class TerrainLogic
{
public:
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual float getGroundHeight(float x, float y, int unk);
	virtual void t07();
	virtual void t08();
	virtual void getMapExtent(RadarExtent *extent);
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual bool queryWater(float x, float y, int *out, int a, int b);
};

// Secondary Radar interface at this+4; native dispatches its slot 9.
class RadarSecond
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void refresh();
};


class RadarEventRef;
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

enum RadarEventType
{
	RADAR_EVENT_CONSTRUCTION = 1,
	RADAR_EVENT_BATTLE_PLAN = 7,
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9,
	RADAR_EVENT_INVALID = 0x0B
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

enum
{
	RADAR_CELL_WIDTH = 128,
	RADAR_CELL_HEIGHT = 128
};

// ?rva002D782C@Radar@@QAE_NPBUCoord3D@@PAVCoord2D@@@Z @0x002D782C 120B Radar float
// radar from world via samples plus float clamp.
// Evidence: same this as rowed worldToRadar with m_xSample at +0x24 and
// m_ySample at +0x28; caller 0x0004F53B in FUN_0044f515; prev worldToRadar
// and next searchListForRadarLocationMatch share flags and Radar class; float
// limits live in .rdata at 0x007C4E90 and 0x007C4DBC.
bool Radar::rva002D782C(const Coord3D *world, Coord2D *radar)
{
	if (world == 0 || radar == 0)
		return false;
	radar->x = world->x / m_xSample;
	radar->y = world->y / m_ySample;
	if (radar->x < 0.0f)
		radar->x = 0.0f;
	if (radar->x >= 128.0f)
		radar->x = 127.0f;
	if (radar->y < 0.0f)
		radar->y = 0.0f;
	if (radar->y >= 128.0f)
		radar->y = 127.0f;
	return true;
}

// ?searchListForRadarLocationMatch@Radar@@QAEPAVObject@@PAVRadarObject@@PAUICoord2D@@@Z
// @0x002D78A4 102B Radar list search: walks a RadarObject list (m_object at +4,
// m_next at +8), runs rowed worldToRadar on each Object pos at +0x38 into a stack
// ICoord2D, and returns the first Object whose radar cell is within +-1 of the
// target ICoord2D. Evidence: same this as rowed worldToRadar; caller 0x002D834E
// passes m_localObjectList +0x18 then m_objectList +0x14 with a localPixelToRadar
// ICoord2D; prev/next are Radar_radarToWorld / findDrawPositions with same flags.
Object *Radar::searchListForRadarLocationMatch(RadarObject *list, ICoord2D *target)
{
	if (list == 0 || target == 0)
		return 0;
	for (RadarObject *node = list; node != 0; node = node->m_next)
	{
		Object *obj = node->m_object;
		if (obj == 0)
			continue;
		ICoord2D tmp;
		worldToRadar(&obj->m_pos, &tmp);
		if (tmp.x >= target->x - 1 && tmp.x <= target->x + 1
			&& tmp.y >= target->y - 1 && tmp.y <= target->y + 1)
			return obj;
	}
	return 0;
}

// Clear the queued terrain refresh frame. The terrain argument is unused.
void Radar::refreshTerrain(TerrainLogic *)
{
	m_queueTerrainRefreshFrame = 0;
}

// ?rva002D7BB7@Radar@@QAEXPBX@Z @0x002D7BB7 28B Radar copy draw rect and set dirty.
// Evidence: copies 16B from arg to +0x144C via 4x movsd then byte 1 at +0x145C;
// same offsets as sibling rva002D7BD3 invalidate; caller 0x002D3275 passes
// this+0x68 rect with global Radar this; prev newMap and next rva002D7BD3 share class.
void Radar::rva002D7BB7(void const *src)
{
	m_rect = *(RadarRect16 const *)src;
	m_dirty = 1;
}

// ?localPixelToRadar@Radar@@QAE_NPBUICoord2D@@PAU2@@Z retail 0x002D81EC, 248 bytes.
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/RadarLocalPixelToRadar.cpp):
// null-guard the arguments, fetch the window size, fold the full-window
// draw extents through findDrawPositions, reject degenerate or
// out-of-range pixels, then scale into the 128-cell radar space (integer
// path along the long axis, float path along the short one).
// Defined before findDrawPositions so the call stays a call.
Bool Radar::localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar)
{
	if (pixel == NULL || radar == NULL)
		return false;

	Int sizeX;
	Int sizeY;
	{
		ICoord2D size;
		m_radarWindow->winGetSize(&size.x, &size.y);
		sizeX = size.x;
		sizeY = size.y;
	}

	ICoord2D ul;
	ICoord2D lr;
	findDrawPositions(0, 0, sizeX, sizeY, &ul, &lr);

	Int scaledWidth = lr.x - ul.x;
	Int scaledHeight = lr.y - ul.y;

	if (scaledWidth < 1)
		return false;
	if (scaledHeight < 1)
		return false;

	if (pixel->x < ul.x || pixel->x > lr.x ||
		pixel->y < ul.y || pixel->y > lr.y)
		return false;

	if (scaledWidth >= scaledHeight)
	{
		radar->x = (pixel->x - ul.x) * RADAR_CELL_WIDTH / scaledWidth;
		Real yNumerator = (Real)(pixel->y - ul.y);
		Real yDenominator = (Real)scaledHeight;
		radar->y = (Int)((yNumerator / yDenominator) * sizeY);
		radar->y = (sizeY - radar->y) * RADAR_CELL_HEIGHT / sizeY;
	}
	else
	{
		Real xNumerator = (Real)(pixel->x - ul.x);
		Real xDenominator = (Real)scaledWidth;
		radar->x = (Int)((xNumerator / xDenominator) * sizeX);
		radar->x = radar->x * RADAR_CELL_WIDTH / sizeX;
		radar->y = (sizeY - pixel->y) * RADAR_CELL_HEIGHT / sizeY;
	}

	return true;
}

// ?findDrawPositions@Radar@@QAEXHHHHPAUICoord2D@@0@Z, retail 0x002D799C, 266 bytes.
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// Radar::findDrawPositions): preserve the map aspect ratio into the draw
// window, centering along the short axis. BFME2 deltas (all retail-measured):
// - the extent is four plain floats (no Region2D calls; the width/height
//   differences are inline here),
// - the int dimensions divide directly (no width * 1.0f),
// - the axis fit multiplies by the precomputed reciprocal (1.0f / ratio),
//   reusing it for both axes.
void Radar::findDrawPositions(Int startX, Int startY, Int width, Int height,
	ICoord2D *ul, ICoord2D *lr)
{
	Real fWidth = (Real)width;
	Real fHeight = (Real)height;
	Real ratioWidth = m_extent.width() / fWidth;
	Real ratioHeight = m_extent.height() / fHeight;
	Coord2D radar;

	if (ratioWidth >= ratioHeight) {
		Real invRatio = 1.0f / ratioWidth;
		radar.x = m_extent.width() * invRatio;
		radar.y = m_extent.height() * invRatio;
		ul->x = 0;
		ul->y = (Int)(((Real)height - radar.y) / 2.0f);
		lr->x = (Int)radar.x;
		lr->y = height - ul->y;
	} else {
		Real invRatio = 1.0f / ratioHeight;
		radar.x = m_extent.width() * invRatio;
		radar.y = m_extent.height() * invRatio;
		ul->x = (Int)(((Real)width - radar.x) / 2.0f);
		ul->y = 0;
		lr->x = width - ul->x;
		lr->y = (Int)radar.y;
	}

	// make them pixel positions
	ul->x += startX;
	ul->y += startY;
	lr->x += startX;
	lr->y += startY;
}

// ?addObject@Radar@@QAEXPAVObject@@@Z at native 002D7FEC, full 512 bytes.
// Named WB1108090/1645 and ZH/BF1 Radar::addObject establish its purpose.
// BF1 donor revision 9cbfb551fe20dae985f91f2319d8997287b6a705 was reviewed
// and compiled under BF2 settings (no placements). Target evidence fixes
// the flag words, Object fields 250/260/304, Player color280/team2EC,
// module38/3C, virtual slot4C, and the two radar lists at14/18.
// A single current-player variable and direct virtual argument preserve
// retail evaluation order; sorted insertion follows both donors and retail.
void Radar::addObject(Object *object)
{
	if (object == 0)
		return;
	int key = ((Rva0028E58E *)object)->rva0028E58E();
	if (!isPriorityVisible((RadarPriorityType)key))
		return;
	void *t = object->m_4;
	int flags = *(int *)((char *)t + 0x108);
	if ((flags & 0x80) != 0)
	{
		if ((flags & 0x20000) != 0)
			goto alloc;
		if ((*((unsigned char *)t + 0x116) & 0x40) != 0)
			goto alloc;
		if ((*((unsigned char *)t + 0x10E) & 4) != 0)
			goto alloc;
		if (object->isNeutralControlled())
			return;
		BfmeMemberRV *rv = ThePlayerList->bfmePickRV();
		if (rv == 0)
			return;
		if ((int)((Player *)rv)->getRelationship(object->m_304) != 1)
			goto alloc;
		return;
	}
	else
	{
		if ((*((unsigned char *)t + 0x10F) & 0x30) != 0)
			return;
	}
alloc:
	RadarObject *mod = new RadarObject;
	mod->m_object = object;
	Player *alt = object->getControllingPlayer();
	bool useAlt = true;
	Rva00373EC6 *r = object->rva0028F4BC();
	if (r != 0 && r->m_3C != 0)
	{
		BfmeMemberRV *rv2 = ThePlayerList->bfmePickRV();
		if (rv2 != 0)
		{
			if ((int)alt->getRelationship(rv2->m_team) != 2)
			{
				if (rv2->bfmeAskRV())
				{
					alt = ThePlayerList->getNthPlayer(r->m_38);
					if (alt != 0)
					{
						useAlt = false;
					}
				}
			}
		}
	}
	void *iface = object->m_250;
	if (iface != 0)
	{
		alt = (Player *)(void *)((I250Vtbl *)iface)->getV(ThePlayerList->bfmePickRV());
		if (alt != 0)
		{
			useAlt = false;
		}
	}
	if(useAlt || alt==0)
		mod->m_color=rva002D7BFD(object->getIndicatorColor());
	else
		mod->m_color=rva002D7BFD(alt->m_280);
	object->m_radarData = mod;
	bool local = object->isLocallyControlled();
	RadarObject **headp;
	if (local)
		headp = &m_localObjectList;
	else
		headp = &m_objectList;

	if (*headp == 0) {
		*headp=mod;
	} else {
		RadarObject *prev=0;
		int prevKey=0;
		RadarObject *cur, *next;
		for(cur=*headp;cur;cur=next) {
			next=cur->m_next;
			int currentKey=((Rva0028E58E *)cur->m_object)->rva0028E58E();
			if((prev==0 || prevKey<key) && currentKey>=key) {
				if(prev) {
					mod->m_next=prev->m_next;
					prev->m_next=mod;
				} else {
					mod->m_next=cur;
					*headp=mod;
				}
				break;
			} else if(next==0) {
				cur->m_next=mod;
			}
			prev=cur;
			prevKey=currentKey;
		}
	}
}

// Native C035D0's deleting slot calls the same canonical Snapshot
// destructor fold at 49B47C; this complete seven-byte body has no own address.
RadarObject::~RadarObject() {}

// Native C035D0 slot 1 is the shared empty post-load body at B3FD0.
void RadarObject::loadPostProcess() {}

struct XferException {char *text; int tag;};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result,int tag,const char *format,...);
extern int g_guardTargetTypeThrowInfo;
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *, const _s__ThrowInfo *);

// Native 2D84F6..2D85D7 (225 bytes): ZH Radar.cpp list transfer spine.
// Reference inputs reviewed at BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// WB110A280 and caller 2D85D7 prove identity and the private EDI/EAX ABI.
// Retail throw-info CFFD18 names XferException (8-byte payload); the formatter
// and CRT throw calls explicitly construct and throw that payload. Both throw
// edges are non-returning. The donor's inline next getter preserves native
// traversal and register allocation. Radar::xfer below supplies both callers.
static __declspec(noinline) void xferRadarObjectList(Xfer*xfer,RadarObject**head) {
 xfer->Version1(); unsigned short count=0;
 RadarObject*r;
 for(r=*head;r;r=r->m_next)++count;
 *xfer==count;
 if(xfer->IsStoring()) {
  for(r=*head;r;r=r->m_next) *xfer==*reinterpret_cast<Snapshot *>(r);
 }else {
  for(r=*head;r;r=r->m_next) {
   if(!(r->m_object->m_destroyed&1)) {
    XferException e;bfmeFormatText(&e,5,0);
    _CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_guardTargetTypeThrowInfo));__assume(0);
   }
  }
  unsigned short i=0;
  if(count>i) do {
   r=new RadarObject;
   if(!*head)*head=r;
   else {RadarObject*other=*head;for(;other->friend_getNext()!=0;other=other->friend_getNext()){};other->m_next=r;}
   *xfer==*reinterpret_cast<Snapshot *>(r);
   ++i;
  }while(i<count);
 }
}

// Native 2D85D7..2D87B9 (482 bytes), WB1109E60 Radar::DoXfer.
// ZH event transfer spine; target version 1/3, 64 events and tail field slots.
// Native slots 70/44 transfer four floats and the 16-byte integer draw rect.
void XferRadarEventType(Xfer*,int*);
class RadarEventRef;
void Radar::xfer(Xfer*xfer) {
 if(xfer->IsLightCRC())return;
 Xfer::Version version(1,3); *xfer==version;
 *xfer==m_hidden;*xfer==m_forceOn;
 xferRadarObjectList(xfer,&m_localObjectList);xferRadarObjectList(xfer,&m_objectList);
 unsigned short count=64;*xfer==count;
 if(count!=64){XferException e;bfmeFormatText(&e,5,0);_CxxThrowException(&e,reinterpret_cast<const _s__ThrowInfo *>(&g_guardTargetTypeThrowInfo));__assume(0);}
 unsigned short i=0;
 do {
  XferRadarEventType(xfer,reinterpret_cast<int*>(&m_events[i].type));
  *xfer==m_events[i].active;*xfer==m_events[i].createFrame;*xfer==m_events[i].dieFrame;*xfer==m_events[i].fadeFrame;
  *xfer==*reinterpret_cast<RGBAColorInt*>(&m_events[i].color1);*xfer==*reinterpret_cast<RGBAColorInt*>(&m_events[i].color2);
  *xfer==*reinterpret_cast<Coord3DBase*>(&m_events[i].worldLoc);*xfer==*reinterpret_cast<ICoord2D*>(&m_events[i].radarLoc);
  *xfer==m_events[i].soundPlayed;
  if(!xfer->IsStoring())reinterpret_cast<RadarEventRefSlot*>(&m_events[i].ref)->clearRef();
  ++i;
 }while(i<count);
 *xfer==m_nextFree;
 if(version.m_minimum<3){int oldIndex=0;*xfer==oldIndex;}
 *xfer==m_averageTerrainZ;
 *xfer==m_averageWaterZ;
 *xfer==m_xSample;
 *xfer==m_ySample;
 *xfer==*reinterpret_cast<IRegion2D*>(&m_rect);*xfer==*reinterpret_cast<bool*>(&m_dirty);*xfer==*reinterpret_cast<IRegion2D*>(&m_rect);*xfer==*reinterpret_cast<unsigned int*>(&m_queueTerrainRefreshFrame);
 if(version.m_minimum==2){int old;unsigned int old2;*xfer==old;*xfer==old2;}
}

// Native 2D7E68..2D7FAE RET4, 326 bytes; WB1107E00 unnamed twin.
// ZH/BF1 Radar::newMap supplies terrain sampling and average semantics.
// Reviewed BFME1 donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// BF2 uses the existing no-argument window reset, second interface+4, extent
// +1434 and 128x128 samples; native integer ground heights feed the averages.
// The witnessed Y store occurs once per row, after inner X initialization;
// counter zeros precede accumulator zeros. Original target method name unknown.
void Radar::rva002D7E68(void *terrainParam)
{
	newMap();
	reinterpret_cast<RadarSecond *>((char *)this+4)->refresh();
	TerrainLogic *terrain = (TerrainLogic *)terrainParam;
	RadarExtent *ext = &m_extent;
	terrain->getMapExtent(ext);
	m_xSample = (ext->maxX - ext->minX) / 128.0f;
	m_ySample = (ext->maxY - ext->minY) / 128.0f;
	int countTerrain = 0;
	int countWater = 0;
	m_averageTerrainZ = 0.0f;
	m_averageWaterZ = 0.0f;
	ICoord2D cell;
	Coord3D world;
	for (int y = 0; y < 128; ++y)
	{
		int x = 0;
		cell.y = y;
		for (; x < 128; ++x)
		{
			cell.x = x;
			radarToWorld(&cell, &world);
			int hi = (int)terrain->getGroundHeight(world.x, world.y, 0);
			int tmp;
			bool water = terrain->queryWater(world.x, world.y, &tmp, 0, 0);
			if (water)
			{
				m_averageWaterZ += (float)hi;
				++countWater;
			}
			else
			{
				m_averageTerrainZ += (float)hi;
				++countTerrain;
			}
		}
	}
	if (countTerrain == 0)
		countTerrain = 1;
	if (countWater == 0)
		countWater = 1;
	m_averageTerrainZ /= (float)countTerrain;
	m_averageWaterZ /= (float)countWater;
}

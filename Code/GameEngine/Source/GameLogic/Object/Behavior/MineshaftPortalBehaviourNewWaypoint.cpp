// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
//
// Link repair: retail native methods retain frames; delayed STLport instances
// use /O1 frame omission and the verified bfmealloc provider. The complete
// scalar ObjectID vector cleanup folds to 0x0007FAB3 (14B including free REL32);
// its former 0x005F120F pin described a different 30B nontrivial-element clear.
// Pin admission verifies every owner relocation, not only the masked bytes.
//
// ?rva00372DFA@MineshaftPortalBehaviour@@QAEPAVWaypoint@@PBUCoord3D@@@Z,
// retail 0x00372DFA..0x00372ED3 (217B), thiscall ret 4.
//
// Allocates the portal's private Waypoint (0xC0 bytes): id 0x7FFFFFFE, name
// "#mineshaftportal_wp", the given location, three empty labels, not
// bi-directional, 8 and an empty trailing name (rowed
// ??0Waypoint@@QAE@IVAsciiString@@PBUCoord3D@@000_NH0@Z 0x00282212). The
// waypoint then takes the object's +0x74 word at +0xB0 and the module data's
// +0x118 / +0x119 bytes at +0xA8 / +0xA9, and its +0x48 byte is cleared.
//
// Evidence (target): the only caller is MineshaftPortalBehaviour::createWaypoint
// (unrowed 0x003738F6; WorldBuilder twin 0xF3CD30 carries that name) at
// 0x003739E9 with ecx = the behaviour and the result stored at +0x34.
// WorldBuilder twin 0xF3D100 (strings lead) reads the +0x04 module data
// into a local before the new. The string literal is at 0x00817D9C; the
// labels copy AsciiString::TheEmptyString (0x009E0878). Field names stay
// address-derived.
// stlport
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <math.h>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const { return a < b; }
}

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;

#include "../../../../Include/Common/BfmeXfer.h"
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "Common/Snapshot.h"
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Player { public: char pad[0x54]; int key; };
struct Rva00373B70Template
{
	char pad00[0x114];
	unsigned int m_kindOf;
};
class Rva00373B70Contain;
class GeometryInfo;
class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned int isKindOf6D() const { return m_template->m_kindOf & 0x2000; }
	char pad00[4];
	const Rva00373B70Template *m_template;
	char pad08[0x38 - 0x08];
	float x, y; // +0x38, +0x3C
	char pad40[4];
	float angle; // +0x44
	char pad48[0x74 - 0x48];
	ObjectID m_id;
	char pad78[0x104 - 0x78];
	GeometryInfo *geometry; // +0x104
	char pad108[0x250 - 0x108];
	Rva00373B70Contain *m_contain;
	char pad254[0x258 - 0x254];
	char *m_ai;
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Thing;
class ModuleData;
class BehaviorModuleBase
{
private:
	virtual void unused();
public:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleOther
{
	virtual void unused();
};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();
 virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};
class MineshaftPortalInterfaceA
{
public:
	virtual void ifaceA() = 0;
};
class MineshaftPortalInterfaceB
{
public:
	virtual void ifaceB() = 0;
};
typedef int WaypointID;
const WaypointID INVALID_WAYPOINT_ID = 0x7FFFFFFF;
void XferWaypointID(Xfer *xfer, WaypointID *value);
void XferObjectID(Xfer *xfer, ObjectID *value);
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern void *TheMineshaftPortalNetworkManager;


class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pLoc, AsciiString label1, AsciiString label2, AsciiString label3, bool biDirectional, int bfmeType, AsciiString bfmeName);
	__forceinline int getID() const { return id; }
	void addLink(Waypoint *other);
	char m_pad00[0x4];
	int id; // +0x04
	char m_pad08[0x40];
	unsigned char m_48; // +0x48
	char m_pad49[0x5F];
	unsigned char m_A8; // +0xA8
	unsigned char m_A9; // +0xA9
	char m_padAA[0x6];
	int m_B0; // +0xB0
	char m_padB4[0xC];
};

class __declspec(novtable) Rva00253487Base
{
public:
	Rva00253487Base();
	virtual ~Rva00253487Base();

private:
	// +0x00 vptr (novtable: installed explicitly by each ctor).
	// Remainder is opaque here (0x114 bytes: UpdateModuleData tail plus the
	// +8 member the base ctor constructs); only the 0x118 size matters.
	unsigned char m_opaque[0x114];
};

class MultiIniFieldParse;

class __declspec(novtable) MineshaftPortalBehaviourModuleData : public Rva00253487Base
{
public:
	MineshaftPortalBehaviourModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

public:
	// +0x118/+0x119 trailing behavior flags (false).
	bool m_trailingFlag0; // +0x118
	bool m_trailingFlag1; // +0x119
	char m_pad11A[2]; // to the rowed 0x11C instance size
};

// createWaypoint's geometry bounds: the rowed GeometryInfo helper 0x006BDEE0
// fills two corners; the first positive x extent wins.
struct Rva0087E650Bounds { Coord3D lo, hi; };
class GeometryInfo { public: void rva0087E650(Rva0087E650Bounds *bounds); };

// Coord3D member-wise set, inlined at the use (WB F3CD30 builds pos from two
// evaluated temporaries and a zero z before adding the object position).
static __forceinline void setCoord(Coord3D *p, float x, float y, float z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

// WWMath Vector3 subset used by createWaypoint (WB F3CD30 names
// Vector3::Rotate_Z, vector3.h). As in the BFME 1 vector3.h donor, the angle
// form forwards sinf(angle), cosf(angle) (the CRT inline float wrappers; sin
// is called first) to the X-first two-argument rotate.
struct Vector3
{
	float x, y, z;
	Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
	__forceinline void Rotate_Z(float angle)
	{
		Rotate_Z(sinf(angle), cosf(angle));
	}
	__forceinline void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = x;
		float tmp_y = y;
		x = c_angle * tmp_x - s_angle * tmp_y;
		y = s_angle * tmp_x + c_angle * tmp_y;
	}
};

struct Rva003738F6Terrain
{
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual float groundHeight(float x, float y, void *normal);
};
// The 10.0f pad beyond the geometry's x extent: a four-byte .data float at
// VA 0x00DC039C read only by createWaypoint (data_xrefs). Descriptive name;
// the original identifier is unknown.
float BfmeMineshaftPortalWaypointPad = 10.0f;

struct Coord3D;
class Waypoint;
class MineshaftPortalBehaviour : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void DoXfer(Xfer *xfer);
	void addArrivingObject(void *p);
	Waypoint *rva00372DFA(const Coord3D *pos);
	void createWaypoint();

private:
	_STL::vector<ObjectID> m_pending; // +0x28
	Waypoint *m_waypoint; // +0x34
	bool m_registered; // +0x38
	bool m_mode39; // +0x39
};

// Emit the already-used enum-vector operations with their verified provider flags.
template void _STL::vector<ObjectID>::push_back(const ObjectID &);
template void _STL::vector<ObjectID>::_M_insert_overflow(ObjectID *,
    const ObjectID &, const _STL::__false_type &, unsigned int, bool);

// Retain the retail frames only for the native methods below.
#pragma optimize("y", off)
Waypoint *MineshaftPortalBehaviour::rva00372DFA(const Coord3D *pos)
{
	const MineshaftPortalBehaviourModuleData *data = (const MineshaftPortalBehaviourModuleData *)m_moduleData;
	Waypoint *wp = new Waypoint(0x7FFFFFFE, AsciiString("#mineshaftportal_wp"), pos,
		AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
		false, 8, AsciiString::TheEmptyString);
	wp->m_B0 = m_object->m_id;
	wp->m_A8 = data->m_trailingFlag0;
	wp->m_A9 = data->m_trailingFlag1;
	wp->m_48 = 0;
	return wp;
}

// MineshaftPortalNetworkManager::addWaypoint, retail 00373871..003738F6,
// 133 bytes, RET8. WB F3E6E0 names it in MineshaftPortalBehaviour.cpp:
// the player's index (+54) selects the manager's map (+10); a missing
// network gets a sixteen-byte Rva0037307F (rowed 23-byte constructor).
// Append the waypoint's ObjectID (+4) to its vector header (+0), then
// set its dirty byte (+C). The constructor's older BfmeE16 element view
// proves the header and flag, not element identity. This caller appends
// an ObjectID through the existing ObjectID-specialized push_back pin.
// The neutral constructor name is retained; no original network-record
// class name is asserted. WB F3CD30 and native caller 373A03 corroborate
// the manager/waypoint/player roles. Native signed-key searches and the
// complete map helper bodies establish the container ABI independently.
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
class Rva0037307F
{
public:
	Rva0037307F();
	_STL::vector<BfmeE16> m_vec; // +0
	bool changed; // +0x0C
};
class Rva00373373Portal;
class MineshaftPortalNetworkManager : public SubsystemInterface, public Snapshot
{
public:
    MineshaftPortalNetworkManager();
    virtual ~MineshaftPortalNetworkManager();
    virtual void xfer(Xfer *xfer);
    virtual void reset();
    virtual void update();
    void rva00373158(Rva00373373Portal *portal, int key);
    void rva003731CB(Rva00373373Portal *portal, Player *player);
    bool hasUsableNetwork(void *p);
    void addWaypoint(Waypoint *waypoint, Player *player);
    _STL::map<int, void *> m_map; // +0x10, after the 0xC subsystem base and the Snapshot pointer
};
typedef std::map<int, Rva0037307F *> NetworkMap;
void MineshaftPortalNetworkManager::addWaypoint(Waypoint *waypoint, Player *player)
{
    int key = player->key;
    NetworkMap::iterator it = ((NetworkMap *)&m_map)->find(key);
    if (it == ((NetworkMap *)&m_map)->end()) {
        // Retail's allocation has no unwind state: the record constructor cannot throw.
        Rva0037307F *record = (Rva0037307F *)::operator new(sizeof(Rva0037307F));
        Rva0037307F *network = record ? &record->Rva0037307F::Rva0037307F() : 0;
        int insertionKey = player->key;
        (*(NetworkMap *)&m_map)[insertionKey] = network;
        int lookupKey = player->key;
        it = ((NetworkMap *)&m_map)->find(lookupKey);
    }
    ObjectID id = (ObjectID)waypoint->id;
    ((_STL::vector<ObjectID> *)&it->second->m_vec)->push_back(id);
    it->second->changed = true;
}

// DoXfer role named by WB F3D290 (MineshaftPortalBehaviour.cpp:231..267).
// Native373A0F..373B54 RET4: UpdateModule transfer, light-CRC bypass,
// version1/1; resolve and register the loaded waypoint or save its id;
// transfer bytes38/39 and pending ObjectIDs at28. Original access and
// virtual declaration are not asserted by this neutral method label.
void MineshaftPortalBehaviour::DoXfer(Xfer *xfer)
{
    ((UpdateModule *)this)->xfer(xfer);
    if (xfer->IsLightCRC())
        return;
    Xfer::Version version(1, 1);
    *xfer == version;
    if (xfer->IsLoading()) {
        WaypointID id;
        XferWaypointID(xfer, &id);
        struct TerrainWaypointView {
            virtual void slot0(); virtual void slot1(); virtual void slot2();
            virtual void slot3(); virtual void slot4(); virtual void slot5();
            virtual void slot6(); virtual void slot7(); virtual void slot8();
            virtual void slot9(); virtual void slot10(); virtual void slot11();
            virtual void slot12(); virtual void slot13(); virtual void slot14();
            virtual void slot15(); virtual void slot16(); virtual void slot17();
            virtual void slot18(); virtual void slot19(); virtual void slot20();
            virtual void slot21(); virtual void slot22(); virtual void slot23();
            virtual void slot24(); virtual void slot25(); virtual void slot26();
            virtual void slot27(); virtual void slot28(); virtual void slot29();
            virtual void slot30(); virtual void slot31(); virtual void slot32();
            virtual void slot33(); virtual void slot34();
            virtual Waypoint *findWaypoint(WaypointID id);
        };
        m_waypoint = id == INVALID_WAYPOINT_ID ? 0 : ((TerrainWaypointView *)TheTerrainLogic)->findWaypoint(id);
        if (m_waypoint)
            ((MineshaftPortalNetworkManager *)TheMineshaftPortalNetworkManager)->addWaypoint(m_waypoint, m_object->getControllingPlayer());
    } else {
        WaypointID id = m_waypoint ? m_waypoint->getID() : INVALID_WAYPOINT_ID;
        XferWaypointID(xfer, &id);
    }
    *xfer == m_registered;
    *xfer == m_mode39;
    unsigned int count = m_pending.size();
    *xfer == count;
    if (xfer->IsStoring()) {
        std::vector<ObjectID>::const_iterator end = m_pending.end();
        for (std::vector<ObjectID>::const_iterator it = m_pending.begin(); it != end; ++it) {
            ObjectID id = *it;
            XferObjectID(xfer, &id);
        }
    } else if (xfer->IsLoading()) {
        for (unsigned int i = 0; i < count; ++i) {
            ObjectID id = INVALID_OBJECT_ID;
            XferObjectID(xfer, &id);
            m_pending.push_back(id);
        }
    }
}

// MineshaftPortalBehaviour::createWaypoint, retail 0x003738F6..0x00373A0F
// (281 B). WB F3CD30 carries the name (MineshaftPortalBehaviour.cpp:188
// asserts m_waypoint). Once per behaviour: place the private waypoint just
// outside the geometry's x extent, rotated by the object's angle, on the
// terrain, and register it with the portal network for the controlling player.
void MineshaftPortalBehaviour::createWaypoint()
{
	if (!m_registered) {
		float angle = m_object->angle;
		Rva0087E650Bounds bounds;
		m_object->geometry->rva0087E650(&bounds);
		float extent = bounds.lo.x > 0.0f ? bounds.lo.x : bounds.hi.x;
		Vector3 offset(extent + BfmeMineshaftPortalWaypointPad, 0.0f, 0.0f);
		offset.Rotate_Z(angle);
		Coord3D pos;
		setCoord(&pos, offset.x, offset.y, 0.0f);
		pos.x += m_object->x;
		pos.y += m_object->y;
		pos.z = ((Rva003738F6Terrain *)TheTerrainLogic)->groundHeight(pos.x, pos.y, 0);
		m_waypoint = rva00372DFA(&pos);
		((MineshaftPortalNetworkManager *)TheMineshaftPortalNetworkManager)->addWaypoint(
			m_waypoint, m_object->getControllingPlayer());
		m_registered = true;
	}
}

// MSVC emits delayed template instances after the native methods.
#pragma optimize("", on)

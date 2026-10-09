// ?createWaypoint@MineshaftPortalBehaviour@@QAEXXZ
// partial score=0.91 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
#include <math.h>
#include <map>
#include <vector>
enum ObjectID { INVALID_OBJECT_ID = 0 };
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const { return a < b; }
}

struct Coord3D { float x, y, z; };
struct Rva0087E650Bounds { Coord3D lo, hi; };
class GeometryInfo { public: void rva0087E650(Rva0087E650Bounds *bounds); };
class Player;
class Object { public: Player *getControllingPlayer() const; };
struct Vector3 {
    float x, y, z;
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    __forceinline void Rotate_Z(float angle) {
        float s = (float)sin((double)angle);
        float c = (float)cos((double)angle);
        Rotate_Z(s, c);
    }
    __forceinline void Rotate_Z(float s, float c) {
        float oldX = x, oldY = y;
        y = s * oldX + c * oldY;
        x = c * oldX - s * oldY;
    }
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
struct Rva003738F6Terrain {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual float groundHeight(float x, float y, void *normal);
};
extern float g_Va00DC039C;
extern void *g_Va00E01EDC;

class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, bool biDirectional, int bfmeType, AsciiString bfmeName);

	unsigned char m_pad00[4];
	ObjectID id;
	unsigned char m_pad08[0x48 - 8];
	unsigned char m_48;		// +0x48
	unsigned char m_pad49[0xA8 - 0x49];
	unsigned char m_A8;		// +0xA8
	unsigned char m_A9;		// +0xA9
	unsigned char m_padAA[0xB0 - 0xAA];
	int m_B0;			// +0xB0
	unsigned char m_padB4[0xC0 - 0xB4];
};

struct MineshaftPortalBehaviourModuleData
{
	unsigned char m_pad00[0x118];
	unsigned char m_118;		// +0x118
	unsigned char m_119;		// +0x119
};

struct Rva00372DFAObject
{
	unsigned char m_pad00[0x38];
    float x, y;
    unsigned char m_pad40[4];
    float angle;
    unsigned char m_pad48[0x74 - 0x48];
	int m_74;			// +0x74
    unsigned char m_pad78[0x104 - 0x78];
    GeometryInfo *geometry;
};

class MineshaftPortalBehaviour
{
public:
	Waypoint *rva00372DFA(const Coord3D *pos);
    void createWaypoint();

private:
	void *m_vtbl;
	const MineshaftPortalBehaviourModuleData *m_moduleData;	// +0x04
	Rva00372DFAObject *m_object;				// +0x08
    unsigned char m_pad0C[0x34 - 0x0C];
    Waypoint *m_waypoint;
    bool m_registered;
};

Waypoint *MineshaftPortalBehaviour::rva00372DFA(const Coord3D *pos)
{
	const MineshaftPortalBehaviourModuleData *data = m_moduleData;
	Waypoint *wp = new Waypoint(0x7FFFFFFE, AsciiString("#mineshaftportal_wp"), pos,
		AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
		false, 8, AsciiString::TheEmptyString);
	wp->m_B0 = m_object->m_74;
	wp->m_A8 = data->m_118;
	wp->m_A9 = data->m_119;
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
class Rva0037307F {
public:
    Rva0037307F() throw();
    std::vector<ObjectID> ids;
    bool changed;
};
class Player {
public:
    char unknown00[0x54];
    int index;
};
class MineshaftPortalNetworkManager {
public:
    void addWaypoint(Waypoint *waypoint, Player *player);
private:
    char unknown00[0x10];
    std::map<int, Rva0037307F *> networks;
};
void MineshaftPortalNetworkManager::addWaypoint(Waypoint *waypoint, Player *player)
{
    int key = player->index;
    std::map<int, Rva0037307F *>::iterator it = networks.find(key);
    if (it == networks.end()) {
        Rva0037307F *network = new Rva0037307F;
        int insertionKey = player->index;
        networks[insertionKey] = network;
        int lookupKey = player->index;
        it = networks.find(lookupKey);
    }
    ObjectID id = waypoint->id;
    it->second->ids.push_back(id);
    it->second->changed = true;
}

// Native 003738F6..00373A0F, whole281B. WB F3CD30 names createWaypoint
// and its Vector3::Rotate_Z expansion. Native supplies receiver offsets,
// the mutable exit-distance word, and the terrain slot6 call.
void MineshaftPortalBehaviour::createWaypoint()
{
    if (!m_registered) {
        float angle = m_object->angle;
        Rva0087E650Bounds bounds;
        m_object->geometry->rva0087E650(&bounds);
        float extent = bounds.lo.x > 0.0f ? bounds.lo.x : bounds.hi.x;
        Vector3 offset(extent + g_Va00DC039C, 0.0f, 0.0f);
        offset.Rotate_Z(angle);
        Coord3D pos;
        pos.x = offset.x;
        pos.y = offset.y;
        pos.z = 0.0f;
        pos.x += m_object->x;
        pos.y += m_object->y;
        pos.z = ((Rva003738F6Terrain *)TheTerrainLogic)->groundHeight(pos.x, pos.y, 0);
        m_waypoint = rva00372DFA(&pos);
        ((MineshaftPortalNetworkManager *)g_Va00E01EDC)->addWaypoint(
            m_waypoint, ((Object *)m_object)->getControllingPlayer());
        m_registered = true;
    }
}

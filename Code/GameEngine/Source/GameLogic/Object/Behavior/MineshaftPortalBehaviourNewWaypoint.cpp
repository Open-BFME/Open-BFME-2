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
#include <map>
#include <vector>
enum ObjectID { INVALID_OBJECT_ID = 0 };
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const { return a < b; }
}

struct Coord3D;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3D &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Player;
class Object { public: Player *getControllingPlayer() const; };
class UpdateModule { public: void xfer(Xfer *xfer); };
typedef int WaypointID;
const WaypointID INVALID_WAYPOINT_ID = 0x7FFFFFFF;
void XferWaypointID(Xfer *xfer, WaypointID *value);
void XferObjectID(Xfer *xfer, ObjectID *value);
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern void *g_Va00E01EDC;


class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pLoc, AsciiString label1,
		AsciiString label2, AsciiString label3, bool biDirectional, int bfmeType, AsciiString bfmeName);

	unsigned char m_pad00[4];
	int id;
    __forceinline int getID() const { return id; }
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
	unsigned char m_pad00[0x74];
	int m_74;			// +0x74
};

class MineshaftPortalBehaviour
{
public:
	Waypoint *rva00372DFA(const Coord3D *pos);
    void rva00373A0F(Xfer *xfer);

private:
	void *m_vtbl;
	const MineshaftPortalBehaviourModuleData *m_moduleData;	// +0x04
	Rva00372DFAObject *m_object;				// +0x08
    unsigned char m_pad0C[0x28 - 0x0C];
    std::vector<ObjectID> m_pending;
    Waypoint *m_waypoint;
    bool m_registered;
    bool m_39;
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
    ObjectID id = (ObjectID)waypoint->id;
    it->second->ids.push_back(id);
    it->second->changed = true;
}

// DoXfer role named by WB F3D290 (MineshaftPortalBehaviour.cpp:231..267).
// Native373A0F..373B54 RET4: UpdateModule transfer, light-CRC bypass,
// version1/1; resolve and register the loaded waypoint or save its id;
// transfer bytes38/39 and pending ObjectIDs at28. Original access and
// virtual declaration are not asserted by this neutral method label.
void MineshaftPortalBehaviour::rva00373A0F(Xfer *xfer)
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
            ((MineshaftPortalNetworkManager *)g_Va00E01EDC)->addWaypoint(m_waypoint, ((Object *)m_object)->getControllingPlayer());
    } else {
        WaypointID id = m_waypoint ? m_waypoint->getID() : INVALID_WAYPOINT_ID;
        XferWaypointID(xfer, &id);
    }
    *xfer == m_registered;
    *xfer == m_39;
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

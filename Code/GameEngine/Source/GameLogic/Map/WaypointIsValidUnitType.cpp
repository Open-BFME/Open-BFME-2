// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// Waypoint::isValidUnitType, retail 0x00281AED (266 bytes).
// Identity (lead): WorldBuilder's debug build names the method and puts it in
// TerrainLogic.cpp (reverse/wb_name_leads.csv); its body supplies the order of
// the tests. Offsets and callees are retail's.
//
// Waypoint layout (target evidence: retail ctor 0x00282212 and the rowed dtor
// 0x00282500 in GameClient/Rva00282500Dtor.cpp, vtable 0x007FB21C):
//   +0x04 id, +0x08 name, +0x0C location, +0x18/+0x1C prev/next list links,
//   +0x20 links[8], +0x40 link source, +0x44 intermediate, +0x48 flag (1),
//   +0x4C link count, +0x50..+0x58 path labels, +0x5C bidirectional,
//   +0x60 type, +0x64 label, +0x68/+0x88 has-mask flags, +0x6C/+0x8C 0x1C
//   masks, +0xA8/+0xA9 flags, +0xAC portal cell, +0xB0, +0xB4, +0xB8, +0xBC
//   pool member with a destructor.
// Member names m_intermediate (+0x44), m_type (+0x60) and m_portalCell (+0xAC)
// come from WB asserts (reverse/wb_members.csv); the rest follow the BFME1
// donor game/GameEngine/Source/GameLogic/Map/WaypointConstructor.cpp and the
// ZH TerrainLogic.h shape (donor-carried, not target-proven names).
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

class Player;

// Shared 0x1C mask: out-of-line ctor 0x0024C7B3 (rowed).
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	bool test(int bit) const { return ((m_bits[0] >> bit) & 1) != 0; }

private:
	unsigned int m_bits[7];
};

// Thing::isAnyKindOf's rowed spelling takes BitFlags<69>.
template <int N> class BitFlags;

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;	// 0x0030ADC7

private:
	unsigned char m_pad00[0x48];
};

enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class Rva003A2BD4Owner
{
public:
	unsigned char m_pad[0x3cf];
	bool m_flag3CF;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	Player *getControllingPlayer() const;			// 0x0028AFA9
	bool testStatusBit22() const { return ((m_status124 >> 22) & 1) != 0; }

	unsigned char m_pad48[0x124 - 0x48];
	unsigned int m_status124;		// +0x124
	unsigned char m_pad128[0x258 - 0x128];
	Rva003A2BD4Owner *m_owner258;		// +0x258
};

class Player
{
public:
	bool rva002AA245() const;		// 0x002AA245
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
};

extern Rva002A8F24 *g_00DFEEF8;

extern GameLogic *TheGameLogic;

// Pool-aware object filter member: ctor 0x003623E5, dtor 0x00360D26 and
// accepts 0x00362437 (all rowed under placeholder names).
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	bool accepts(Object *obj, Player *player);

private:
	unsigned m_handle;
};

enum { MAX_LINKS = 8 };

class Waypoint
{
public:
	virtual ~Waypoint();

	bool isValidUnitType(Object *obj);

private:
	int m_id;				// +0x04
	AsciiString m_name;			// +0x08
	Coord3D m_location;			// +0x0C
	Waypoint *m_prev;			// +0x18
	Waypoint *m_next;			// +0x1C
	Waypoint *m_links[MAX_LINKS];		// +0x20
	Waypoint *m_linkSource;			// +0x40
	int m_intermediate;			// +0x44
	bool m_flag48;				// +0x48
	int m_numLinks;				// +0x4C
	AsciiString m_pathLabel1;		// +0x50
	AsciiString m_pathLabel2;		// +0x54
	AsciiString m_pathLabel3;		// +0x58
	bool m_biDirectional;			// +0x5C
	int m_type;				// +0x60
	AsciiString m_typeOption;		// +0x64
	bool m_hasIncludeMask;			// +0x68
	Rva0024C7B3Member m_includeMask;	// +0x6C
	bool m_hasExcludeMask;			// +0x88
	Rva0024C7B3Member m_excludeMask;	// +0x8C
	bool m_flagA8;				// +0xA8
	bool m_flagA9;				// +0xA9
	int m_portalCell;			// +0xAC
	ObjectID m_fieldB0;			// +0xB0, object whose allies may use this waypoint
	unsigned int m_fieldB4;			// +0xB4, first usable logic frame
	bool m_flagB8;				// +0xB8
	Rva003623E5Member m_memberBC;		// +0xBC
};

bool Waypoint::isValidUnitType(Object *obj)
{
	if (m_fieldB0 != INVALID_OBJECT_ID)
	{
		Object *linked = TheGameLogic->findObjectByID(m_fieldB0);
		if (!m_flagA8)
		{
			if (linked == 0 || linked->getRelationship(obj) != ALLIES)
				return false;
		}
		if (!m_flagA9)
		{
			if (!obj->getControllingPlayer()->rva002AA245())
				return false;
			if (g_00DFEEF8->rva002A8AB1(obj->getControllingPlayer()) == 0)
				return false;
		}
		if (m_type == 7)
		{
			if (obj->m_owner258 == 0 || obj->m_owner258->m_flag3CF)
				return false;
		}
	}
	if (m_flagB8 && !m_memberBC.accepts(obj, 0))
		return false;
	if (m_hasIncludeMask && !obj->isAnyKindOf(*(const BitFlags<69> *)&m_includeMask))
		return false;
	if (m_hasExcludeMask)
	{
		if (obj->isAnyKindOf(*(const BitFlags<69> *)&m_excludeMask))
			return false;
		if (m_excludeMask.test(9) && obj->testStatusBit22())
			return false;
	}
	if (m_fieldB4 > 0 && TheGameLogic->getFrame() < m_fieldB4)
		return false;
	return true;
}

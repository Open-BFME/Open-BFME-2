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

#include "../../Common/Thing/thing.h"

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

	unsigned char m_pad60[0x124 - 0x60];
	unsigned int m_status124;		// +0x124
	unsigned char m_pad128[0x258 - 0x128];
	Rva003A2BD4Owner *m_owner258;		// +0x258
};


#include "../../../Include/Common/Player.h"



#include "../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

extern GameLogic *TheGameLogic;

// Pool-aware object filter member: ctor 0x003623E5, dtor 0x00360D26 and
// accepts 0x00362437 (all rowed under placeholder names; accepts is the rowed
// Rva2225E0Filter::accepts, which the old Rva003623E5Member::accepts pin duplicated).
#include "../../../Include/GameLogic/Module/Rva2225E0Filter.h"
class Rva003623E5Member : public Rva2225E0Filter
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	unsigned m_handle;
};

#include "../../../Include/GameLogic/Waypoint.h"

bool Waypoint::isValidUnitType(Object *obj)
{
	if ((ObjectID)m_fieldB0 != INVALID_OBJECT_ID)
	{
		Object *linked = TheGameLogic->findObjectByID((ObjectID)m_fieldB0);
		if (!m_fieldA8)
		{
			if (linked == 0 || linked->getRelationship(obj) != ALLIES)
				return false;
		}
		if (!m_fieldA9)
		{
			if (!obj->getControllingPlayer()->rva002AA245())
				return false;
			if (TheSkirmishAIManager->rva002A8AB1(obj->getControllingPlayer()) == 0)
				return false;
		}
		if (m_field60 == 7)
		{
			if (obj->m_owner258 == 0 || obj->m_owner258->m_flag3CF)
				return false;
		}
	}
	if (m_fieldB8 && !((Rva003623E5Member *)&m_fieldBC)->accepts(obj, 0))
		return false;
	if (m_field68 && !obj->isAnyKindOf(*(const BitFlags<69> *)m_field6C))
		return false;
	if (m_field88)
	{
		if (obj->isAnyKindOf(*(const BitFlags<69> *)m_field8C))
			return false;
		if (((const Rva0024C7B3Member *)m_field8C)->test(9) && obj->testStatusBit22())
			return false;
	}
	if (m_fieldB4 > 0 && TheGameLogic->getFrame() < m_fieldB4)
		return false;
	return true;
}

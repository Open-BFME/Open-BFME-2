// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
//
// TerrainResourceClaimFeedback::Impl (WB debug twin: C:\Projects\bfme2\Code\GameEngine\Source\GameClient\Gui\
// TerrainResourceClaimFeedback.cpp, lines 223..247). updateClaimedDecalForClaimant is the WB name of retail
// 0x004E7FCA, reached from the claimant callback 0x004E81DE; the layout is the one the sibling refresh
// 0x004E7E3A (ResourceEntryOwnerRva004E7E3A.cpp) reads. Field, element and type names below are inferred.
//
// Codegen evidence: retail keeps the claimed decal in EBX across the Coord3D equality call and shares one stack
// slot between the compared position and the new list element, which MSVC does only when the callee's body is
// visible here; retail's TU saw Coord3D::operator== as an inline definition.
// stlport
#include <list>
#include <map>

// Compare typed nodes locally; retail inlines this comparison in the caller.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva004E7A76
{
public:
	void rva004E7A76();
};

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_name;		// +0x00
		AsciiString m_second;		// +0x04
		Int m_type;			// +0x08
		Real m_sizeX;			// +0x0C
		Real m_sizeY;			// +0x10
		Real m_offsetX;			// +0x14
		Real m_offsetY;			// +0x18
		Real m_float1C;			// +0x1C
		Real m_float20;			// +0x20
		Bool m_byte24;			// +0x24
		Bool m_allowUpdates;		// +0x25
		Bool m_allowWorldAlign;		// +0x26
	};
	const Coord3D *getPosition() const { return &m_position; }
	Coord3D getPositionValue() const { return m_position; }
	void setPosition(const Coord3D *pos) { m_position = *pos; }
	void setOpacity(Int value);			// 0x003308F6
	void setColor(Int color);			// 0x00330995
	unsigned char m_pad00[0x08];
	Coord3D m_position;				// +0x08
	unsigned char m_pad14[0x20 - 0x14];
	Real m_angle;					// +0x20
	unsigned char m_pad24[0x58 - 0x24];
	Real m_decalSizeX;				// +0x58
	Real m_decalSizeY;				// +0x5C
	unsigned char m_pad60[0x64 - 0x60];
	Bool m_byte64;					// +0x64
};

class ProjectedShadowManager
{
public:
	virtual void v00(); virtual void v01();
	virtual Shadow *addDecal(Shadow::ShadowTypeInfo *shadowInfo);	// +0x08
};
extern ProjectedShadowManager *TheProjectedShadowManager;

enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED };
class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	Coord3D *getPosition() { return &m_position; }
	char m_pad[0x38];
	Coord3D m_position;
};

#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

struct ClaimedDecal
{
	ClaimedDecal() : m_key(INVALID_OBJECT_ID), m_radius(0.0f), m_decal(0) {}
	~ClaimedDecal() { reinterpret_cast<Rva004E7A76 *>(this)->rva004E7A76(); }
	ObjectID m_key;
	Real m_radius;
	Shadow *m_decal;
};

typedef _STL::list<ClaimedDecal> ClaimedDecalList;
typedef _STL::map<ObjectID, ClaimedDecalList::iterator> ClaimedDecalMap;

class TerrainResourceClaimFeedback
{
public:
	class Impl;
};

class TerrainResourceClaimFeedback::Impl
{
public:
	void updateClaimedDecalForClaimant(ClaimedDecalList *pending, ObjectID id, Real radius);
private:
	char m_pad00[4];
	int m_users;				// +0x04
	AsciiString m_decalName;		// +0x08
	ClaimedDecalList m_claimedDecals;	// +0x0C
	ClaimedDecalMap m_claimedDecalMap;	// +0x14
};


inline bool Coord3D::operator==(const Coord3D &r)
{
	return x == r.x && y == r.y && z == r.z;
}

void TerrainResourceClaimFeedback::Impl::updateClaimedDecalForClaimant(ClaimedDecalList *pending, ObjectID id, Real radius)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	Player *local = ThePlayerList->getLocalPlayer();
	if (obj->getShroudStatusForPlayer(local ? local->m_playerIndex : 0) > CELLSHROUD_SHROUDED)
		obj = 0;
	ClaimedDecalMap::iterator it = m_claimedDecalMap.find(id);
	if (it != m_claimedDecalMap.end())
	{
		if (obj == 0)
		{
			m_claimedDecals.erase(it->second);
			m_claimedDecalMap.erase(it);
		}
		else
		{
			m_claimedDecals.splice(m_claimedDecals.end(), *pending, it->second);
			ClaimedDecal &claimedDecal = *it->second;
			if (radius != claimedDecal.m_radius)
			{
				claimedDecal.m_radius = radius;
				Shadow *decal = claimedDecal.m_decal;
				decal->m_decalSizeX = radius * 2.0f;
				decal->m_decalSizeY = radius * 2.0f;
			}
			if (!(*obj->getPosition() == claimedDecal.m_decal->getPositionValue()))
				claimedDecal.m_decal->setPosition(obj->getPosition());
		}
	}
	else if (obj)
	{
		Shadow::ShadowTypeInfo info;
		info.m_name = m_decalName;
		info.m_allowUpdates = false;
		info.m_allowWorldAlign = true;
		info.m_type = 0x20;
		info.m_sizeX = info.m_sizeY = radius * 2.0f;
		Shadow *decal = TheProjectedShadowManager->addDecal(&info);
		if (decal)
		{
			decal->m_angle = 0.0f;
			decal->setColor(0xff6464c8);
			decal->m_position = *obj->getPosition();
			decal->m_byte64 = true;
			decal->setOpacity(0x80);
			ClaimedDecalList::iterator newIt = m_claimedDecals.insert(m_claimedDecals.end(), ClaimedDecal());
			newIt->m_key = id;
			newIt->m_radius = radius;
			newIt->m_decal = decal;
			m_claimedDecalMap[id] = newIt;
		}
	}
}

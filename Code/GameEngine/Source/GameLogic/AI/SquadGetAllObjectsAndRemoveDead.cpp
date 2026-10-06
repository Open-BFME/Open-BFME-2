// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport

// Retail 0x0018BB10, 282 bytes. Shape-twin of Zero Hour's Squad::getAllObjects
// (zh_fuzzy_twins 0.85): clear a cached Object* vector at +0x10, then walk an
// ObjectID vector at +0x04, resolving each id through TheGameLogic's object hash
// and erasing ids that no longer resolve. The +0x04 id vector is the same claim
// the re-homed 0x0018B520 sibling makes, and matched Squad rows put Squad's
// m_objectIDs at +0x08, so the owner keeps its address token rather than a
// guessed class name.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

// An enum, as in the game: STLport then copies ids element by element on
// erase instead of memmove, which is what retail does.
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_32 = 0x7fffffff
};

class Object;

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

typedef _STL::vector<ObjectID> VecObjectID;
typedef _STL::vector<Object *> VecObjectPtr;

class Squad
{
public:
	const VecObjectPtr &rva004D6CAC();
	const VecObjectPtr &getAllObjectsAndRemoveDead();

private:
	void *m_vtable;						// +0x00
	VecObjectID m_objectIDs;			// +0x04
	VecObjectPtr m_objectsCached;		// +0x10
};

// Retail 0x004D6CAC, 75B, directly before getAllObjectsAndRemoveDead: the
// same cache rebuild without pruning -- ids that no longer resolve are skipped
// and left in the id vector. Player's selection (+0x730) walks this
// (0x002AABBC). Landed upstream on a Rva0018BB10Roster owner; same object.
const VecObjectPtr &Squad::rva004D6CAC()
{
	m_objectsCached.clear();
	for (VecObjectID::iterator it = m_objectIDs.begin(); it != m_objectIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
			m_objectsCached.push_back(obj);
	}

	return m_objectsCached;
}

const VecObjectPtr &Squad::getAllObjectsAndRemoveDead()
{
	m_objectsCached.clear();
	for (VecObjectID::iterator it = m_objectIDs.begin(); it != m_objectIDs.end(); )
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			m_objectsCached.push_back(obj);
			++it;
		}
		else
		{
			it = m_objectIDs.erase(it);
		}
	}

	return m_objectsCached;
}

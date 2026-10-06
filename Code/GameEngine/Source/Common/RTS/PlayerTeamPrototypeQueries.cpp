// cl: /DNDEBUG /MD
//
// Player's team-prototype queries (retail 0x002AB260..0x002AB427): each
// walks the +0x32C list of TeamPrototype pointers (STL list nodes: next,
// prev, value; end() reread every pass) and answers true as soon as the
// matching TeamPrototype walk (TeamPrototypeTeamIterators.cpp) does, as
// Zero Hour's Player::hasAnyBuildings/hasAnyUnits/hasAnyObjects do. Names
// follow the TeamPrototype callees.
typedef bool Bool;
typedef int Int;

struct Rva0039DDC2Filter
{
	Rva0039DDC2Filter(const Rva0039DDC2Filter &other);
	unsigned int w[7];
};

struct Rva0039DF1CFilter
{
	Rva0039DF1CFilter(const Rva0039DF1CFilter &other);
	unsigned int w[7];
};

class BfmeTab1026;
class ThingTemplate;
class Object;
typedef Int (*ObjectIterateFunc)(Object *obj, void *userData);

template <int N>
class BitFlags
{
public:
	BitFlags();
	BitFlags(const BitFlags &other);
private:
	unsigned int m_bits[7];
};
typedef BitFlags<116> KindOfMaskType;

struct Coord3D
{
	float x, y, z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad[0x38];
	Coord3D m_pos; // +0x38
};

// The 0x4C-byte search record of the rowed callback Rva002AA3D4Closest
// (PlayerRva002AA3D4Closest.cpp); its constructor 0x002A991D is pinned.
struct Rva002AA3D4Search
{
	Rva002AA3D4Search();
	KindOfMaskType m_mustBeSet;	// +0x00
	KindOfMaskType m_mustBeClear;	// +0x1C
	Coord3D m_pos;			// +0x38
	Object *m_closest;		// +0x44
	float m_closestDistSq;		// +0x48
};

Int __cdecl Rva002AA3D4Closest(Object *obj, void *userData);

class TeamPrototype
{
public:
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;
	Int countBuildings();
	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
	void healAllObjects();
	Int rva0039ED9C(ObjectIterateFunc func, void *userData);
	void updateState();
	Bool rva0039EDE1(Bool flag);
	Bool rva0039EE21(Rva0039DDC2Filter filter, Bool flag);
	Bool rva0039EE70(BfmeTab1026 *tab, Bool flag);
	Bool rva0039EEB4();
	Bool rva0039EEEE(Rva0039DF1CFilter filter1, Rva0039DF1CFilter filter2);
	Bool rva0039EF46(BfmeTab1026 *tab);
	Bool hasAnyObjects(Bool flag);
	Bool rva0039EFC6();
};

// The player's team prototype list (an STL list node: next, prev, value).
struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
public:
	void healAllObjects();
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;
	Int countBuildings();
	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
	Object *findClosestByKindOf(Object *queryObject, KindOfMaskType setMask, KindOfMaskType clearMask);
	Object *findClosestToPosByKindOf(const Coord3D *pos, KindOfMaskType setMask, KindOfMaskType clearMask);
	void updateTeamStates();
	Bool rva002AB260(Bool flag) const;
	Bool rva002AB295(Rva0039DDC2Filter filter, Bool flag) const;
	Bool rva002AB2D9(BfmeTab1026 *tab, Bool flag) const;
	Bool rva002AB312() const;
	Bool rva002AB341(Rva0039DF1CFilter filter1, Rva0039DF1CFilter filter2) const;
	Bool rva002AB390(BfmeTab1026 *tab) const;
	Bool hasAnyObjects(Bool flag) const;
	Bool rva002AB3FA() const;

private:
	unsigned char m_pad[0x32C];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C list head node
};

// Zero Hour's Player::healAllObjects, iterateObjects (BFME: int callback,
// stops when a team prototype's walk answers 0), countObjectsByThingTemplate,
// countBuildings and countObjects (retail 0x002AB06A..0x002AB184), forwarding
// to the TeamPrototype walks of the same names.
void Player::healAllObjects()
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
		it->m_value->healAllObjects();
}

Int Player::iterateObjects(ObjectIterateFunc func, void *userData) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (!it->m_value->rva0039ED9C(func, userData))
			return 0;
	}
	return 1;
}

void Player::countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for (Int i = 0; i < numTmplates; ++i)
		counts[i] = 0;
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
		it->m_value->countObjectsByThingTemplate(numTmplates, things, ignoreDead, counts, ignoreUnderConstruction);
}

Int Player::countBuildings()
{
	Int retVal = 0;
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
		retVal += it->m_value->countBuildings();
	return retVal;
}

Int Player::countObjects(KindOfMaskType setMask, KindOfMaskType clearMask)
{
	Int retVal = 0;
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
		retVal += it->m_value->countObjects(setMask, clearMask);
	return retVal;
}

Bool Player::rva002AB260(Bool flag) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EDE1(flag))
			return true;
	}
	return false;
}

Bool Player::rva002AB295(Rva0039DDC2Filter filter, Bool flag) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EE21(filter, flag))
			return true;
	}
	return false;
}

Bool Player::rva002AB2D9(BfmeTab1026 *tab, Bool flag) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EE70(tab, flag))
			return true;
	}
	return false;
}

Bool Player::rva002AB312() const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EEB4())
			return true;
	}
	return false;
}

Bool Player::rva002AB341(Rva0039DF1CFilter filter1, Rva0039DF1CFilter filter2) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EEEE(filter1, filter2))
			return true;
	}
	return false;
}

Bool Player::rva002AB390(BfmeTab1026 *tab) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EF46(tab))
			return true;
	}
	return false;
}

Bool Player::hasAnyObjects(Bool flag) const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->hasAnyObjects(flag))
			return true;
	}
	return false;
}

Bool Player::rva002AB3FA() const
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		if (it->m_value->rva0039EFC6())
			return true;
	}
	return false;
}

// Player::updateTeamStates, retail 0x002AB429 (33B): Zero Hour's
// Player::updateTeamStates, stepping past each node before the call (the
// prototype's updateState may delete teams); TeamPrototype::updateState
// 0x003A34AC is pinned from this call.
void Player::updateTeamStates()
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; )
	{
		TeamPrototype *proto = it->m_value;
		it = it->m_next;
		proto->updateState();
	}
}

// Player::findClosestByKindOf, retail 0x002AB185 (89B), next after
// countObjects as in Zero Hour: fills
// the search record with the two masks and the query object's position and
// lets iterateObjects run the rowed nearest-match callback over it.
// 0x002AB1DE (74B) is BFME's twin taking a position instead of an object.
Object *Player::findClosestByKindOf(Object *queryObject, KindOfMaskType setMask, KindOfMaskType clearMask)
{
	if (queryObject == 0)
		return 0;
	Rva002AA3D4Search data;
	data.m_mustBeSet = setMask;
	data.m_mustBeClear = clearMask;
	data.m_pos = *queryObject->getPosition();
	iterateObjects(Rva002AA3D4Closest, &data);
	return data.m_closest;
}

Object *Player::findClosestToPosByKindOf(const Coord3D *pos, KindOfMaskType setMask, KindOfMaskType clearMask)
{
	Rva002AA3D4Search data;
	data.m_mustBeSet = setMask;
	data.m_mustBeClear = clearMask;
	data.m_pos = *pos;
	iterateObjects(Rva002AA3D4Closest, &data);
	return data.m_closest;
}

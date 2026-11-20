// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG
// Out-of-line copies of BFME2 partition-filter constructors. Each stores the
// base's zero next link (+0x04), the filter's vftable and its members, as the
// filters AIClosestObjectQueries.cpp, AIAreaEnemySearch.cpp,
// AIAttackApproachTargetStateOnEnter.cpp and Drawable_rva00272AD5.cpp declare
// them (class names and vftables from those units; this unit repeats only
// what the constructors touch). Retail keeps these copies out of line beside
// their callers; here each constructor is select-any like every other unit's
// inline copy, and an anchor keeps the noinline body emitted.
#include <new.h>

class Object;
class Player;
class PolygonTrigger;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10: Rva0026119DFilter, out-of-line constructor copy at 0x0026FFA4 (13B).
class Rva0026119DFilter : public Rva000421C8
{
public:
	Rva0026119DFilter();
	virtual bool allow(Object *obj);
};

__declspec(noinline) inline Rva0026119DFilter::Rva0026119DFilter()
{
}

// ?bfmeAnchorRva0026FFA4 absent-from-retail
void *bfmeAnchorRva0026FFA4(void *where)
{
	return ::new (where) Rva0026119DFilter();
}

// vftable 0x00BFAD04: Rva00260E2AFilter, out-of-line constructor copy at 0x0026FF8E (22B).
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(const Player *player);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Player *m_player;
};

__declspec(noinline) inline Rva00260E2AFilter::Rva00260E2AFilter(const Player *player) : m_player(player)
{
}

// ?bfmeAnchorRva0026FF8E absent-from-retail
void *bfmeAnchorRva0026FF8E(void *where, const Player *player)
{
	return ::new (where) Rva00260E2AFilter(player);
}

// vftable 0x00BFAD28: Rva0026137EFilter, out-of-line constructor copy at 0x0026FFBE (29B).
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match);
	// BFAD28 slot0 is395A19: keep its call to the seven-byte base reset49C38A.
	__declspec(noinline) virtual ~Rva0026137EFilter() {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

__declspec(noinline) inline Rva0026137EFilter::Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match)
{
}

// ?bfmeAnchorRva0026FFBE absent-from-retail
void *bfmeAnchorRva0026FFBE(void *where, Player *player, bool match)
{
	return ::new (where) Rva0026137EFilter(player, match);
}

// vftable 0x00BF91BC: Rva002611BFFilter, out-of-line constructor copy at 0x002623AB (22B).
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002611BFFilter::Rva002611BFFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002623AB absent-from-retail
void *bfmeAnchorRva002623AB(void *where, const Object *obj)
{
	return ::new (where) Rva002611BFFilter(obj);
}

// vftable 0x00BFBC90: Rva00260EB1Filter, out-of-line constructor copy at 0x0028AABB (36B).
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

__declspec(noinline) inline Rva00260EB1Filter::Rva00260EB1Filter(const Object *obj, int flags, bool match) : m_obj(obj), m_flags(flags), m_match(match)
{
}

// ?bfmeAnchorRva0028AABB absent-from-retail
void *bfmeAnchorRva0028AABB(void *where, const Object *obj, int flags, bool match)
{
	return ::new (where) Rva00260EB1Filter(obj, flags, match);
}

// vftable 0x00C07150: Rva002619C1Filter, out-of-line constructor copy at 0x002FD66B (22B).
struct Coord3D;

class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(const Object *obj);
	virtual bool allow(Object *obj);
	virtual bool rva0026163A(const Coord3D *target);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002619C1Filter::Rva002619C1Filter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD66B absent-from-retail
void *bfmeAnchorRva002FD66B(void *where, const Object *obj)
{
	return ::new (where) Rva002619C1Filter(obj);
}

// vftable 0x00C0716C: Rva00261353Filter, out-of-line constructor copy at 0x002FD69E (22B).
class Rva00261353Filter : public Rva000421C8
{
public:
	Rva00261353Filter(int playerIndex);
	virtual bool allow(Object *obj);
	int m_playerIndex;
};

__declspec(noinline) inline Rva00261353Filter::Rva00261353Filter(int playerIndex) : m_playerIndex(playerIndex)
{
}

// ?bfmeAnchorRva002FD69E absent-from-retail
void *bfmeAnchorRva002FD69E(void *where, int playerIndex)
{
	return ::new (where) Rva00261353Filter(playerIndex);
}

// vftable 0x00C07178: Rva00261BFBFilter, out-of-line constructor copy at 0x002FD6B4 (22B).
class Rva00261BFBFilter : public Rva000421C8
{
public:
	Rva00261BFBFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva00261BFBFilter::Rva00261BFBFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD6B4 absent-from-retail
void *bfmeAnchorRva002FD6B4(void *where, const Object *obj)
{
	return ::new (where) Rva00261BFBFilter(obj);
}

// vftable 0x00C07184: Rva00261723Filter, out-of-line constructor copy at 0x002FD6CA (22B).
class Rva00261723Filter : public Rva000421C8
{
public:
	Rva00261723Filter(const PolygonTrigger *trigger);
	virtual bool allow(Object *obj);
	const PolygonTrigger *m_trigger;
};

__declspec(noinline) inline Rva00261723Filter::Rva00261723Filter(const PolygonTrigger *trigger) : m_trigger(trigger)
{
}

// ?bfmeAnchorRva002FD6CA absent-from-retail
void *bfmeAnchorRva002FD6CA(void *where, const PolygonTrigger *trigger)
{
	return ::new (where) Rva00261723Filter(trigger);
}

// vftable 0x00C07190: Rva002614DFFilter, out-of-line constructor copy at 0x002FD6E0 (22B).
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj);
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

__declspec(noinline) inline Rva002614DFFilter::Rva002614DFFilter(const Object *obj) : m_obj(obj)
{
}

// ?bfmeAnchorRva002FD6E0 absent-from-retail
void *bfmeAnchorRva002FD6E0(void *where, const Object *obj)
{
	return ::new (where) Rva002614DFFilter(obj);
}

// vftable 0x00BCECF0: Rva002614ECFilter (allow 0x002614EC in
// BfmeThreeHundredFifteen.cpp), out-of-line constructor copy at 0x000E9E03 (36B).
class Rva2225E0Filter;
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(Rva2225E0Filter *sub, void *extra, bool flag);
	virtual bool allow(Object *what);
	Rva2225E0Filter *m_bfmeSub;
	void *m_bfmeExtra;
	bool m_bfmeFlag;
};

__declspec(noinline) inline Rva002614ECFilter::Rva002614ECFilter(Rva2225E0Filter *sub, void *extra, bool flag) : m_bfmeSub(sub), m_bfmeExtra(extra), m_bfmeFlag(flag)
{
}

// ?bfmeAnchorRva000E9E03 absent-from-retail
void *bfmeAnchorRva000E9E03(void *where, Rva2225E0Filter *sub, void *extra, bool flag)
{
	return ::new (where) Rva002614ECFilter(sub, extra, flag);
}

// Three (int, bool) partition filters with out-of-line constructor copies at
// 0x003BA6F1 / 0x003BA70E / 0x003BA72B (29B each). vftable 0x00C1FDE0 is
// Rva002613AFFilter's (allow 0x002613AF, getPlayerMask 0x002613A3, as
// ScriptConditions_Rva003EA764.cpp declares it); 0x00C1FDEC and 0x00C1FDF8
// hold the allow bodies at 0x00261750 and 0x0026176E and keep the base
// getPlayerMask, so those two classes carry address-derived names.
class Rva002613AFFilter : public Rva000421C8
{
public:
	Rva002613AFFilter(int playerMask, bool match);
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	int m_playerMask;
	bool m_match;
};

__declspec(noinline) inline Rva002613AFFilter::Rva002613AFFilter(int playerMask, bool match) : m_playerMask(playerMask), m_match(match)
{
}

// ?bfmeAnchorRva003BA6F1 absent-from-retail
void *bfmeAnchorRva003BA6F1(void *where, int playerMask, bool match)
{
	return ::new (where) Rva002613AFFilter(playerMask, match);
}

class ThingTemplate;
// vftable 0x00C1FDEC is pinned as ??_7Rva00261750Filter (Zero Hour's PartitionFilterThing
// at ScriptActions::doMoveUnitTowardsNearest): +0x08 the thing template.
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *thing, bool match);
	virtual bool allow(Object *obj);
	const ThingTemplate *m_thing;
	bool m_match;
};

__declspec(noinline) inline Rva00261750Filter::Rva00261750Filter(const ThingTemplate *thing, bool match) : m_thing(thing), m_match(match)
{
}

// ?bfmeAnchorRva003BA70E absent-from-retail
void *bfmeAnchorRva003BA70E(void *where, const ThingTemplate *thing, bool match)
{
	return ::new (where) Rva00261750Filter(thing, match);
}

class Rva0026176EFilter : public Rva000421C8
{
public:
	Rva0026176EFilter(int value, bool match);
	virtual bool allow(Object *obj);
	int m_value;
	bool m_match;
};

__declspec(noinline) inline Rva0026176EFilter::Rva0026176EFilter(int value, bool match) : m_value(value), m_match(match)
{
}

// ?bfmeAnchorRva003BA72B absent-from-retail
void *bfmeAnchorRva003BA72B(void *where, int value, bool match)
{
	return ::new (where) Rva0026176EFilter(value, match);
}

// vftable 0x00BF91F0: Rva00263077Filter (allow 0x00263077, base getPlayerMask), out-of-line
// constructor copy at 0x00263061 (22B): one pointer member at +0x08. Class name
// address-derived from its allow body.
class Rva00263077Filter : public Rva000421C8
{
public:
	Rva00263077Filter(const void *target);
	virtual bool allow(Object *obj);
	const void *m_target;
};

__declspec(noinline) inline Rva00263077Filter::Rva00263077Filter(const void *target) : m_target(target)
{
}

// ?bfmeAnchorRva00263061 absent-from-retail
void *bfmeAnchorRva00263061(void *where, const void *target)
{
	return ::new (where) Rva00263077Filter(target);
}

// vftable 0x00BFAF88: Rva00271B3CFilter (allow 0x00271B3C, base getPlayerMask), out-of-line
// constructor copy at 0x00271B26 (22B): one pointer member at +0x08. Class name
// address-derived from its allow body.
class Rva00271B3CFilter : public Rva000421C8
{
public:
	Rva00271B3CFilter(const void *target);
	virtual bool allow(Object *obj);
	const void *m_target;
};

__declspec(noinline) inline Rva00271B3CFilter::Rva00271B3CFilter(const void *target) : m_target(target)
{
}

// ?bfmeAnchorRva00271B26 absent-from-retail
void *bfmeAnchorRva00271B26(void *where, const void *target)
{
	return ::new (where) Rva00271B3CFilter(target);
}

class SkirmishAI;
struct Coord3D;

// vftable 0x00C071A8: PartitionFilterSkirmishAI (allow 0x00261535 (rowed Allow)), out-of-line constructor copy at
// 0x002FD71E (29B).
class PartitionFilterSkirmishAI : public Rva000421C8
{
public:
	PartitionFilterSkirmishAI(Object * owner, SkirmishAI * ai);
	virtual bool allow(Object *obj);
	Object * m_owner;
	SkirmishAI * m_ai;
};

__declspec(noinline) inline PartitionFilterSkirmishAI::PartitionFilterSkirmishAI(Object * owner, SkirmishAI * ai) : m_owner(owner), m_ai(ai)
{
}

// ?bfmeAnchorRva002FD71E absent-from-retail
void *bfmeAnchorRva002FD71E(void *where, Object * owner, SkirmishAI * ai)
{
	return ::new (where) PartitionFilterSkirmishAI(owner, ai);
}

// vftable 0x00C17F08: Rva0026118BFilter (allow 0x0026118B), out-of-line constructor copy at
// 0x00373C92 (13B).
class Rva0026118BFilter : public Rva000421C8
{
public:
	Rva0026118BFilter();
	virtual bool allow(Object *obj);
};

__declspec(noinline) inline Rva0026118BFilter::Rva0026118BFilter()
{
}

// ?bfmeAnchorRva00373C92 absent-from-retail
void *bfmeAnchorRva00373C92(void *where)
{
	return ::new (where) Rva0026118BFilter();
}

// vftable 0x00C1FE04: Rva0026144CFilter (allow 0x0026144C), out-of-line constructor copy at
// 0x003BA748 (22B).
class Rva0026144CFilter : public Rva000421C8
{
public:
	Rva0026144CFilter(bool match);
	virtual bool allow(Object *obj);
	bool m_match;
};

__declspec(noinline) inline Rva0026144CFilter::Rva0026144CFilter(bool match) : m_match(match)
{
}

// ?bfmeAnchorRva003BA748 absent-from-retail
void *bfmeAnchorRva003BA748(void *where, bool match)
{
	return ::new (where) Rva0026144CFilter(match);
}

// vftable 0x00C1FE10: Rva0026149CFilter (allow 0x0026149C), out-of-line constructor copy at
// 0x003BA75E (22B).
class Rva0026149CFilter : public Rva000421C8
{
public:
	Rva0026149CFilter(bool flag);
	virtual bool allow(Object *obj);
	bool m_flag;
};

__declspec(noinline) inline Rva0026149CFilter::Rva0026149CFilter(bool flag) : m_flag(flag)
{
}

// ?bfmeAnchorRva003BA75E absent-from-retail
void *bfmeAnchorRva003BA75E(void *where, bool flag)
{
	return ::new (where) Rva0026149CFilter(flag);
}

// vftable 0x00C1FE28: Rva00261C58Filter (allow 0x00261C58), out-of-line constructor copy at
// 0x003BA798 (22B).
class Rva00261C58Filter : public Rva000421C8
{
public:
	Rva00261C58Filter(bool match);
	virtual bool allow(Object *obj);
	bool m_match;
};

__declspec(noinline) inline Rva00261C58Filter::Rva00261C58Filter(bool match) : m_match(match)
{
}

// ?bfmeAnchorRva003BA798 absent-from-retail
void *bfmeAnchorRva003BA798(void *where, bool match)
{
	return ::new (where) Rva00261C58Filter(match);
}

// vftable 0x00C49E84: Rva00483C9FFilter (allow 0x00483C9F), out-of-line constructor copy at
// 0x00483C82 (29B).
class Rva00483C9FFilter : public Rva000421C8
{
public:
	Rva00483C9FFilter(int value, bool match);
	virtual bool allow(Object *obj);
	int m_value;
	bool m_match;
};

__declspec(noinline) inline Rva00483C9FFilter::Rva00483C9FFilter(int value, bool match) : m_value(value), m_match(match)
{
}

// ?bfmeAnchorRva00483C82 absent-from-retail
void *bfmeAnchorRva00483C82(void *where, int value, bool match)
{
	return ::new (where) Rva00483C9FFilter(value, match);
}

// vftable 0x00C51150: Rva00261130Filter (allow 0x00261130), out-of-line constructor copy at
// 0x0049C374 (22B).
class Rva00261130Filter : public Rva000421C8
{
public:
	Rva00261130Filter(const void * target);
	virtual bool allow(Object *obj);
	const void * m_target;
};

__declspec(noinline) inline Rva00261130Filter::Rva00261130Filter(const void * target) : m_target(target)
{
}

// ?bfmeAnchorRva0049C374 absent-from-retail
void *bfmeAnchorRva0049C374(void *where, const void * target)
{
	return ::new (where) Rva00261130Filter(target);
}

// vftable 0x00C53D18: Rva00261C72Filter (allow 0x00261C72), out-of-line constructor copy at
// 0x004A9312 (13B).
class Rva00261C72Filter : public Rva000421C8
{
public:
	Rva00261C72Filter();
	virtual bool allow(Object *obj);
};

__declspec(noinline) inline Rva00261C72Filter::Rva00261C72Filter()
{
}

// ?bfmeAnchorRva004A9312 absent-from-retail
void *bfmeAnchorRva004A9312(void *where)
{
	return ::new (where) Rva00261C72Filter();
}

// vftable 0x00C54EB4: Rva004ACDACFilter (allow 0x004ACDAC), out-of-line constructor copy at
// 0x004ACD4B (33B).
class Rva004ACDACFilter : public Rva000421C8
{
public:
	Rva004ACDACFilter(const Coord3D * centre, float radius);
	virtual bool allow(Object *obj);
	float m_radius;
	const Coord3D * m_centre;
};

__declspec(noinline) inline Rva004ACDACFilter::Rva004ACDACFilter(const Coord3D * centre, float radius) : m_radius(radius), m_centre(centre)
{
}

// ?bfmeAnchorRva004ACD4B absent-from-retail
void *bfmeAnchorRva004ACD4B(void *where, const Coord3D * centre, float radius)
{
	return ::new (where) Rva004ACDACFilter(centre, radius);
}

// vftable 0x00C5A99C: Rva00260E44Filter (allow 0x00260E44), out-of-line constructor copy at
// 0x004BD1CA (13B).
class Rva00260E44Filter : public Rva000421C8
{
public:
	Rva00260E44Filter();
	virtual bool allow(Object *obj);
};

__declspec(noinline) inline Rva00260E44Filter::Rva00260E44Filter()
{
}

// ?bfmeAnchorRva004BD1CA absent-from-retail
void *bfmeAnchorRva004BD1CA(void *where)
{
	return ::new (where) Rva00260E44Filter();
}

// vftable 0x00C600A0: Rva0026156C (allow 0x0026156C), out-of-line constructor copy at
// 0x004CE69D (29B).
class Rva0026156C : public Rva000421C8
{
public:
	Rva0026156C(Object * object, int value);
	virtual bool allow(Object *obj);
	Object * m_object;
	int m_value;
};

__declspec(noinline) inline Rva0026156C::Rva0026156C(Object * object, int value) : m_object(object), m_value(value)
{
}

// ?bfmeAnchorRva004CE69D absent-from-retail
void *bfmeAnchorRva004CE69D(void *where, Object * object, int value)
{
	return ::new (where) Rva0026156C(object, value);
}

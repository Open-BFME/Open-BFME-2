// cl: /O1 /G7 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii
//
// Partition filter allow slots (slot 1 of each filter vftable) that the
// matched filter users declare under their address-derived class names and
// reach only through those vftables. Each body is retail's own; the Zero
// Hour PartitionManager.cpp filter of the same shape is named beside it as
// donor evidence, not as a proven identity.
typedef bool Bool;

enum ObjectPrivateStatusBits
{
	EFFECTIVELY_DEAD = 0x01,
	OFF_MAP = 0x08
};

class Team;
class Player;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Team *getTeam() const { return m_team; }
	Player *getControllingPlayer() const;		// 0x0028AFA9
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	Bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }
	Bool isOffMap() const { return (m_privateStatus & OFF_MAP) != 0; }
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's isOffMap copy loses to the first-in-order copy (no
	// retail address); the call below inlines it but still emits the loser
	// COMDAT. Rebinding there emits only this unique (trivially kept) copy.
	// No flags touched.
	Bool bfme_is_off_map() const { return (m_privateStatus & OFF_MAP) != 0; }

private:
	unsigned char m_unmodelled_00[0x04];

public:
	const struct Rva00271B3COwner *m_04;		// +0x04 (read by 0x00271B3C)

private:
	unsigned char m_unmodelled_08[0x304 - 0x08];
	Team *m_team;								// +0x304
	unsigned char m_unmodelled_308[0x438 - 0x308];
	unsigned char m_privateStatus;				// +0x438
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;	// 0x002AD0C6
	Relationship getRelationship(const Object *that) const;	// 0x002AD11E
	int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unmodelled_00[0x54];
	int m_playerIndex;							// +0x54
};

class PlayerList
{
public:
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships,
		Bool match);							// 0x002A7C70
};

extern PlayerList *ThePlayerList;				// 0x00DFEEE8

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
// Its inline destructor resets the base vptr, so each derived filter's destructor
// is retail's shared seven-byte body (0x0049C38A, called by deleting dtor 0x00395A19).
class Rva000421C8
{
public:
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	__declspec(dllimport) __forceinline Rva000421C8() : m_next(0) {}
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, built inline by StructureCreep 0x005ABEA2: what is
// not effectively dead (Zero Hour's PartitionFilterAlive).
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
};

Bool Rva0026119DFilter::allow(Object *objOther)
{
	return !objOther->isEffectivelyDead();
}

// vftable 0x00C56930, built inline by EntEnragedUpdate 0x004B25C9: what
// is effectively dead.
class Rva002611AFFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
};

Bool Rva002611AFFilter::allow(Object *objOther)
{
	return objOther->isEffectivelyDead();
}

// vftable 0x00BFAD1C, built inline by Drawable 0x00272AD5: what is on the
// map (Zero Hour's PartitionFilterOnMap).
class Rva002611DDFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
};

Bool Rva002611DDFilter::allow(Object *objOther)
{
	return !objOther->bfme_is_off_map();
}

// vftable 0x00C004D8 (getPlayerMask 0x002613E1): the player's relationship
// to the object's team against the +0x10 flags; a flagged relationship
// answers +0x0C, any other its negation (Zero Hour's
// PartitionFilterPlayerAffiliation, with BFME2's flag bits).
enum
{
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};

class Rva00261409Filter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
	virtual int getPlayerMask();

private:
	const Player *m_player;						// +0x08
	Bool m_match;								// +0x0C
	int m_affiliation;							// +0x10
};

Bool Rva00261409Filter::allow(Object *objOther)
{
	switch (m_player->getRelationship(objOther->getTeam()))
	{
		case ENEMIES:
			if (m_affiliation & ALLOW_ENEMIES)
				return m_match;
			break;
		case NEUTRAL:
			if (m_affiliation & ALLOW_NEUTRAL)
				return m_match;
			break;
		case ALLIES:
			if (m_affiliation & ALLOW_ALLIES)
				return m_match;
			break;
	}
	return !m_match;
}

// The relationship masks both getPlayerMask slots select for
// PlayerList::getPlayersWithRelationship: allies 3, enemies 4, neutral 8.
#define RELATIONSHIP_MASK_FROM_FLAGS(relationships, flags) 	relationships = 0; 	if ((flags) & (1 << ALLIES)) 		relationships = 3; 	if ((flags) & (1 << ENEMIES)) 		relationships |= 4; 	if ((flags) & (1 << NEUTRAL)) 		relationships |= 8

// vftable 0x00BFBC90, built inline at 0x002FDBC4 and by 21 matched users:
// whether the relationship between the +0x08 object and the candidate is
// one of the +0x0C flags (1 << Relationship); +0x10 asks it from the
// candidate's side (Zero Hour's PartitionFilterRelationship, with BFME2's
// direction flag and player mask).
class Rva00260EB1Filter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);
	virtual int getPlayerMask();

private:
	const Object *m_obj;						// +0x08
	int m_flags;								// +0x0C
	Bool m_fromOther;							// +0x10
};

Bool Rva00260EB1Filter::allow(Object *objOther)
{
	Relationship relationship;
	if (!m_fromOther)
		relationship = m_obj->getRelationship(objOther);
	else
		relationship = objOther->getRelationship(m_obj);
	return (m_flags & (1 << relationship)) ? true : false;
}

int Rva00260EB1Filter::getPlayerMask()
{
	Player *player = m_obj->getControllingPlayer();
	if (player == 0)
		return -1;
	unsigned int relationships;
	RELATIONSHIP_MASK_FROM_FLAGS(relationships, m_flags);
	return ThePlayerList->getPlayersWithRelationship(player->getPlayerIndex(), relationships, m_fromOther);
}

// vftable 0x00C6E1B0, built inline by AITargetHeuristicBaseDefense
// 0x005737D6: whether the +0x08 player's relationship to the candidate is
// one of the +0x0C flags.
class Rva00260F1BFilter : public Rva000421C8
{
public:
	Rva00260F1BFilter(const Player *player, int flags);
	virtual Bool allow(Object *objOther);
	virtual int getPlayerMask();

private:
	const Player *m_player;						// +0x08
	int m_flags;								// +0x0C
};

Bool Rva00260F1BFilter::allow(Object *objOther)
{
	return (m_flags & (1 << m_player->getRelationship(objOther))) ? true : false;
}

// ?allow@Rva00261478Filter@@UAE_NPAVObject@@@Z, retail 0x00261478 (36B):
// garrison-permission filter: the candidate passes when the ActionManager's
// canPlayerGarrison answer for (+0x08 player, candidate, +0x10 source)
// equals the +0x0C expectation byte.
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class ActionManager
{
public:
	Bool canPlayerGarrison(const Player *player, const Object *obj, CommandSourceType commandSource);
};
extern ActionManager *TheActionManager;

class Rva00261478Filter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);

private:
	const Player *m_player;						// +0x08
	Bool m_match;								// +0x0C
	CommandSourceType m_source;					// +0x10
};

Bool Rva00261478Filter::allow(Object *objOther)
{
	return TheActionManager->canPlayerGarrison(m_player, objOther, m_source) == m_match;
}

// ??0Rva00260F1BFilter, retail 0x0057377E (29 B, RET 8): Zero Hour's
// PartitionFilterRelationship(obj, flags) shape on BFME2's player field; the
// base clears m_next. Its vftable 0x00C6E1B0 holds this class's allow and
// getPlayerMask slots; AITargetHeuristicBaseDefense builds the same filter
// inline at 0x00573876.
Rva00260F1BFilter::Rva00260F1BFilter(const Player *player, int flags) : m_player(player), m_flags(flags)
{
}

int Rva00260F1BFilter::getPlayerMask()
{
	if (m_player == 0)
		return -1;
	unsigned int relationships;
	RELATIONSHIP_MASK_FROM_FLAGS(relationships, m_flags);
	return ThePlayerList->getPlayersWithRelationship(m_player->getPlayerIndex(), relationships, false);
}

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Rva0026149CFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *objOther);

private:
	Bool m_match;								// +0x08
};

Bool Rva0026149CFilter::allow(Object *objOther)
{
	return m_match == TheScriptEngine->rva00357AF8(objOther);
}

// vftable 0x00BFAF88, slot 1 at VA 0x00BFAF8C (base getPlayerMask): what
// has a +0x04 owner whose +0x580 id equals the filter's +0x08 target.
// PartitionFilterCtorCopies.cpp declares the class (out-of-line ctor copy
// 0x00271B26) and reaches this body only through the vftable. Was rowed as
// the free-standing Rva00271B3C::rva00271B3C view in VslotSmallBodiesD.cpp.
struct Rva00271B3COwner
{
	unsigned char m_unmodelled_00[0x580];
	int m_580;									// +0x580
};

class Rva00271B3CFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *obj);

private:
	int m_target;								// +0x08
};

Bool Rva00271B3CFilter::allow(Object *obj)
{
	return obj->m_04 && obj->m_04->m_580 == m_target;
}

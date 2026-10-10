// cl: /O1 /G7 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
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

private:
	unsigned char m_unmodelled_00[0x304];
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
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
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
	return !objOther->isOffMap();
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
	Relationship r;
	if (!m_fromOther)
		r = m_obj->getRelationship(objOther);
	else
		r = objOther->getRelationship(m_obj);
	return (m_flags & (1 << r)) ? true : false;
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

int Rva00260F1BFilter::getPlayerMask()
{
	if (m_player == 0)
		return -1;
	unsigned int relationships;
	RELATIONSHIP_MASK_FROM_FLAGS(relationships, m_flags);
	return ThePlayerList->getPlayersWithRelationship(m_player->getPlayerIndex(), relationships, false);
}

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Team *getTeam() const { return m_team; }
	Bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }
	Bool isOffMap() const { return (m_privateStatus & OFF_MAP) != 0; }

private:
	unsigned char m_unmodelled_00[0x304];
	Team *m_team;								// +0x304
	unsigned char m_unmodelled_308[0x438 - 0x308];
	unsigned char m_privateStatus;				// +0x438
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;	// 0x002AD0C6
};

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

// cl: /DNDEBUG /MD /EHsc
//
// ?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z,
// retail 0x002A7A29, 22 bytes,
// ?getPlayerFromMask@PlayerList@@QAEPAVPlayer@@H@Z,
// retail 0x002A7B91, 56 bytes, and
// ?getEachPlayerFromMask@PlayerList@@QAEPAVPlayer@@AAH@Z,
// retail 0x002A7BC9, 66 bytes.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/PlayerList.cpp,
// PlayerList::getNthPlayer): bounds-checked indexed accessor over the player
// array. Battle for Middle-earth 2 caps the index at 20 (retail cmp eax,0x14;
// the five 0x2A7AB6-family loop bodies and the 0x2A79A9 init body all iterate
// the same 0x14 count, and the count lives at +0x14 over the inline player
// pointer array at +0x18 per the landed findPlayerWithNameKey row), where the
// reference uses 32. Leaf, no pins.
//
// getPlayerFromMask: BFME1 reference PlayerList::getPlayerFromMask, zero
// guard plus getNthPlayer loop over 20 slots comparing getPlayerMask.
//
// getEachPlayerFromMask: ZH donor GeneralsMD PlayerList.cpp. Target evidence:
// thiscall ret 4 taking the mask by reference; walks getNthPlayer over the 20
// slots, tests 1 << Player +0x54 (getPlayerMask) against the mask, clears
// that bit and returns the player, else zeroes the mask and returns null.
// Both loops keep a value in edx across the getNthPlayer call (the loop index
// in getPlayerFromMask, the mask pointer here), which cl only does when the
// callee was compiled earlier in the same TU, so the three bodies share this
// file as they shared retail's PlayerList.cpp.

typedef int Int;

typedef int PlayerMaskType;

#define NULL 0
#define MAX_PLAYER_COUNT 20
#define BitTest(x, i) (((x) & (i)) != 0)

class PlayerSub60
{
public:
	Int m_pad18[6]; // 0x18 bytes
	Int m_18; // +0x18 (Player+0x78)
	Int m_1C; // +0x1C (Player+0x7C)
};

class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum
{
	ALLOW_SAME_PLAYER = 0x01,
	ALLOW_ALLIES = 0x02,
	ALLOW_ENEMIES = 0x04,
	ALLOW_NEUTRAL = 0x08
};

class Player
{
public:
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }
	Relationship getRelationship(const Team *that) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }
	bool rva002AA245() const; // 0x002AA245

	unsigned char m_pad[0x54];
	Int m_playerIndex; // +0x54
	unsigned char m_pad58[0x60 - 0x58];
	PlayerSub60 m_60; // +0x60
	unsigned char m_pad80[0x2EC - 0x80];
	Team *m_defaultTeam; // +0x2EC
};

class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};

class ParticleSystem
{
public:
	bool isSaveable() const;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
	Player *getPlayerFromMask(PlayerMaskType mask);
	Player *getEachPlayerFromMask(PlayerMaskType &maskToAdjust);
	int rva002A7C0B(bool flag);
	int rva002A7D30();
	PlayerMaskType getPlayersWithRelationship(Int srcPlayerIndex, unsigned int allowedRelationships, bool reverse);

private:
	unsigned char m_pad[0x14];
	Int m_playerCount; // +0x14
	Player *m_players[1]; // +0x18
};

// ?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z
Player *PlayerList::getNthPlayer(Int i)
{
	if (i < 0 || i >= 20)
	{
		return NULL;
	}
	return m_players[i];
}

// ?getPlayerFromMask@PlayerList@@QAEPAVPlayer@@H@Z
Player *PlayerList::getPlayerFromMask(PlayerMaskType mask)
{
	if (mask == 0)
		return NULL;

	Player *player = NULL;
	Int i;

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		player = getNthPlayer(i);
		if (player && player->getPlayerMask() == mask)
			return player;
	}
	return NULL;
}

// ?getEachPlayerFromMask@PlayerList@@QAEPAVPlayer@@AAH@Z
Player *PlayerList::getEachPlayerFromMask(PlayerMaskType &maskToAdjust)
{
	Player *player = NULL;
	Int i;

	for (i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		player = getNthPlayer(i);
		if (player && BitTest(player->getPlayerMask(), maskToAdjust))
		{
			maskToAdjust &= (~player->getPlayerMask());
			return player;
		}
	}

	maskToAdjust = 0;
	return NULL;
}

int PlayerList::rva002A7C0B(bool flag)
{
	int count = 0;
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;
		if (!player->rva002AA245())
			continue;
		if (((Rva002AA22AByteField *)player)->get())
			continue;
		if (((ParticleSystem *)player)->isSaveable())
			continue;
		if (flag)
		{
			PlayerSub60 *s = &player->m_60;
			if (s)
				count += s->m_18 + s->m_1C;
		}
		count++;
	}
	return count;
}

int PlayerList::rva002A7D30()
{
	int mask = 0;
	for (int i = 0; i < m_playerCount; i++)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;
		mask |= player->getPlayerMask();
	}
	return mask;
}

// ?getPlayersWithRelationship@PlayerList@@QAEHHI_N@Z, retail 0x002A7C70
// (192B). Zero Hour's PlayerList::getPlayersWithRelationship with two BFME
// additions read from the target: a flag that asks each other player's view
// of the source instead of the source's view of them, and a relationship
// outside the three (default case) that counts only when every ALLOW_ bit
// (0xF) is requested.
PlayerMaskType PlayerList::getPlayersWithRelationship(Int srcPlayerIndex, unsigned int allowedRelationships, bool reverse)
{
	PlayerMaskType retVal = 0;

	if (allowedRelationships == 0)
		return retVal;

	Player *srcPlayer = getNthPlayer(srcPlayerIndex);
	if (!srcPlayer)
		return retVal;

	if (BitTest(allowedRelationships, ALLOW_SAME_PLAYER))
		retVal = srcPlayer->getPlayerMask();

	for (Int i = 0; i < m_playerCount; ++i)
	{
		Player *player = getNthPlayer(i);
		if (!player)
			continue;

		if (player == srcPlayer)
			continue;

		Relationship r = !reverse ? srcPlayer->getRelationship(player->getDefaultTeam())
			: player->getRelationship(srcPlayer->getDefaultTeam());
		switch (r)
		{
			case ENEMIES:
				if (BitTest(allowedRelationships, ALLOW_ENEMIES))
					retVal |= player->getPlayerMask();
				break;
			case NEUTRAL:
				if (BitTest(allowedRelationships, ALLOW_NEUTRAL))
					retVal |= player->getPlayerMask();
				break;
			case ALLIES:
				if (BitTest(allowedRelationships, ALLOW_ALLIES))
					retVal |= player->getPlayerMask();
				break;
			default:
				if (allowedRelationships == 0xF)
					retVal |= player->getPlayerMask();
				break;
		}
	}

	return retVal;
}

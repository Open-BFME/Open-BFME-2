// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?doFindCommandCenter@@YAHPAVObject@@PAX@Z @0x002AC5AC (94B): Zero Hour
// Player.cpp's doFindCommandCenter, the iterateObjects callback that the
// matched Player::findNaturalCommandCenter (0x002AC60A, PlayerO1Shard.cpp)
// pushes as `push 0x6AC5AC`. Same test order as ZH: no result yet, the
// template's KINDOF_COMMANDCENTER bit (template +0x10A bit 0x02), the template
// default owning side (+0x6C) equal to the player's side (+0x58) through the
// rowed StringBase compare 0x000069D6, then not OBJECT_STATUS_UNDER_CONSTRUCTION
// (2) nor OBJECT_STATUS_SOLD (0x13) through the rowed Object::testStatus
// 0x0004E536. BFME's iterator callbacks return int: 0 stops the walk once the
// centre is found, 1 keeps walking (also for a null object), as doPowerDisable.
// The finder's two-field info block is the player and the result.

#include "ascii_string.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13
};

class ThingTemplate
{
public:
	bool isKindOfCommandCenter() const { return (m_kindOf10A & 2) != 0; }
	const AsciiString &getDefaultOwningSide() const { return m_defaultOwningSide; }

private:
	char m_pad[0x6C];
	AsciiString m_defaultOwningSide;	// +0x6C
	char m_pad2[0x10A - 0x70];
	unsigned char m_kindOf10A;			// KINDOF_COMMANDCENTER is bit 0x02
};

class Player
{
public:
	const AsciiString &getSide() const { return m_side; }

private:
	char m_pad[0x58];
	AsciiString m_side;					// +0x58
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	bool isKindOfCommandCenter() const { return getTemplate()->isKindOfCommandCenter(); }

private:
	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
};


struct PlayerObjectFindInfo
{
	Player *player;
	Object *obj;
};

int doFindCommandCenter(Object *obj, void *userData)
{
	if (!obj)
		return 1;

	PlayerObjectFindInfo *info = (PlayerObjectFindInfo *)userData;

	if (info->obj == 0
			&& obj->isKindOfCommandCenter()
			&& obj->getTemplate()->getDefaultOwningSide() == info->player->getSide()
			&& !obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION)
			&& !obj->testStatus(OBJECT_STATUS_SOLD))
	{
		info->obj = obj;
		return 0;
	}
	return 1;
}

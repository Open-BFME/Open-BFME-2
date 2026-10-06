// ?rva002CC4DD@Weapon@@QAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva002CC4DD@Weapon@@QAEXXZ 0x002CC4DD 155B
// Evidence: linkbody 3 files 93B; calls isEmpty 0x1E2F then findObjectByID 0x49DC5 twice then rva002D06CA 0x2D06CA then memset import then getControllingPlayer 0x28AFA9 then newObject pin 0x2D0A23; prev 0x2CC422 computeStatus next 0x2CC578 getRemainingAmmo same Weapon +0x04 template +0x08 owner +0x5C spawned.
#include "ascii_string.h"
#pragma function(memset)
extern "C" void *memset(void *dst, int value, unsigned int size);

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class ThingTemplate;
class Team;
struct CreateMask
{
	unsigned char data[0x10];
};
class Object;
class Player;
class GameLogic;

class WeaponTemplate
{
public:
	char m_pad00[0x178];
	AsciiString m_name178;
};

class Weapon
{
public:
	void rva002CC4DD();
private:
	char m_pad00[4];
	WeaponTemplate *m_template;
	ObjectID m_owner08;
	char m_pad0C[0x5C - 0x0C];
	ObjectID m_spawned5C;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[0x74];
	ObjectID m_id74;
};

class Player
{
public:
	char m_pad00[0x2EC];
	Team *m_team2EC;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern Rva002D06CA *g_009FF000;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};

// ?rva002CC4DD@Weapon@@QAEXXZ present-unmatched
void Weapon::rva002CC4DD()
{
	const AsciiString *tmplName = &m_template->m_name178;
	if (((const StringBase<char> *)tmplName)->isEmpty())
		return;
	GameLogic *logic = TheGameLogic;
	Object *owner = logic->findObjectByID(m_owner08);
	if (!owner)
	{
		m_spawned5C = INVALID_OBJECT_ID;
		return;
	}
	Object *spawned = logic->findObjectByID(m_spawned5C);
	if (spawned)
		return;
	m_spawned5C = INVALID_OBJECT_ID;
	void *tmpl = g_009FF000->rva002D06CA(tmplName);
	CreateMask mask;
	memset(&mask, 0, 0x10);
	Player *player = owner->getControllingPlayer();
	Team *team = player->m_team2EC;
	Object *created = ((ThingFactory *)g_009FF000)->newObject((const ThingTemplate *)tmpl, team, &mask, false);
	if (!created)
		return;
	m_spawned5C = created->m_id74;
}

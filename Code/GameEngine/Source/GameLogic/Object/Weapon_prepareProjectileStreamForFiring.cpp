// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /I.
// Weapon::prepareProjectileStreamForFiring (retail 0x002CC4DD, 155 B): spawns the weapon template's named object for the owner's
// player when none is alive (name at WeaponTemplate+0x178, owner id +0x08, spawned id +0x5C).
// Offsets are target facts; the equal-arms on the template name test and the stale-id lookup
// barrier are scheduling levers found by sweepeq4/chain.py.
// stlport
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <string.h>
#pragma function(memset)

class ThingTemplate;
class Team;
struct CreateMask
{
	unsigned char data[0x10];
};
class Object;
class Player;

#include "../../../Include/GameLogic/WeaponTemplate.h"

#include "../../../Include/GameLogic/Weapon.h"

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad00[0x74];
	ObjectID m_id74;
};

#include "../../../Include/Common/Player.h"

extern GameLogic *TheGameLogic;

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;

// WorldBuilder Weapon::prepareProjectileStreamForFiring, WB VA 0x00BBA3B0 (callgraph lead, score 2; no args).
void Weapon::prepareProjectileStreamForFiring()
{
	// The header keeps the +0x178 projectile-stream name as opaque storage.
	const AsciiString &asciiString = *(const AsciiString *)&(m_template ? m_template : m_template)->m_field178;
	if ((m_template ? (((const StringBase<char> *)&asciiString)->isEmpty()) : (((const StringBase<char> *)&asciiString)->isEmpty())))
		return;
	Object *owner;
	GameLogic *logic = TheGameLogic;
	owner = logic->findObjectByID((ObjectID)m_ownerID);
	if (!owner)
	{
		m_extra5C = INVALID_OBJECT_ID;
		return;
	}
	Object *spawned = logic->findObjectByID((ObjectID)m_extra5C);
	_ReadWriteBarrier();
	if (spawned)
		return;
	m_extra5C = INVALID_OBJECT_ID;
	void *tmpl = (void *)TheThingFactory->findTemplate(asciiString);
	CreateMask mask;
	memset(&mask, 0, 0x10);
	Player *player = owner->getControllingPlayer();
	Team *team = player->m_defaultTeam;
	Object *created = TheThingFactory->newObject((const ThingTemplate *)tmpl, team, &mask, (ObjectID)0);
	if (!created)
		return;
	m_extra5C = created->m_id74;
}

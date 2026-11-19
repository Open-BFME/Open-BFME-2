// cl: /DNDEBUG /MD /EHsc
// ?processRequestAssistance@Weapon@@IAEXPBVObject@@PAV2@@Z
// Zero Hour's Weapon::processRequestAssistance, also BFME1's (0x001E4BF0, same
// size and callees in order); privateFireWeapon calls it as Zero Hour does.
//
// retail 0x002C9DF5 (83 bytes). Unlock: Player iterate with template+0x28 squared range.
// Controlling player via Object getControllingPlayer (rowed 0x0028AFA9); if null return;
// else iterateObjects (pinned 0x002AB08B) with callback 0x006C9D47 and 12B userdata
// {source, other, squared range}. Evidence: [ecx+4] WeaponTemplate, +0x28 float;
// callers 0x002CE363; neighbours WeaponIsWithinTargetPitch.cpp.
//
// The callback is Zero Hour's makeAssistanceRequest (Weapon.cpp), retail
// 0x002C9D47 (174 bytes) just ahead of this body: same object refused, same
// ThingTemplate::isEquivalentTo test, the partition-manager 2D distance done
// as the rowed 0x002615E3 view (this object's +0x38 position against the
// requester's), the NAMEKEY-cached AssistedTargetingUpdate lookup through
// Object::findModule, then isFreeToAssist / assistAttack. BFME's iterate
// callbacks return int; this one always returns 1. It needs an EH frame for
// the static key initialiser, so the unit is built /EHsc (the method below
// has nothing to unwind and is unchanged by it).

#include "../../Common/RTS/XYDistanceCallView.h"

class Object;
class Player;
class Module;

typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/NameKeyType.h"




#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/Common/Rva000CBA20Point.h"

int __cdecl makeAssistanceRequest(Object *requestOf, void *userData);

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const { return *(const ThingTemplate *volatile *)&m_template; }
	const Rva000CBA20Point *getPosition2D() const { return reinterpret_cast<const Rva000CBA20Point *>(&m_cachedPos); }

protected:
	Module *findModule(NameKeyType key) const;

private:
	friend int __cdecl makeAssistanceRequest(Object *requestOf, void *userData);
};

#include "../../../Include/Common/AssistedTargetingUpdate.h"

#include "../../../Include/Common/Player.h"

struct WeaponTemplateRange
{
	char m_pad00[0x28];
	float m_range; // +0x28
};

struct IterateData
{
	const Object *m_source; // +0
	const void *m_other; // +4
	float m_rangeSqr; // +8
};


#include "../../../Include/GameLogic/Weapon.h"

void Weapon::processRequestAssistance(const Object *source, Object *other)
{
	Player *player = source->getControllingPlayer();
	if (player == 0)
		return;
	IterateData data;
	data.m_source = source;
	data.m_other = other;
	data.m_rangeSqr = 0.0f;
	float range = ((const WeaponTemplateRange *)m_template)->m_range;
	data.m_rangeSqr = range * range;
	player->iterateObjects(makeAssistanceRequest, &data);
}

int __cdecl makeAssistanceRequest(Object *requestOf, void *userData)
{
	IterateData *requestData = (IterateData *)userData;

	if (requestOf == requestData->m_source)
		return 1;

	if (!requestOf->getTemplate()->isEquivalentTo(requestData->m_source->getTemplate()))
		return 1;

	float distSq = ((Rva000CBA20 *)requestOf)->distSq(requestData->m_source->getPosition2D());
	if (distSq > requestData->m_rangeSqr)
		return 1;

	static const NameKeyType key_assistUpdate = TheNameKeyGenerator->nameToKey("AssistedTargetingUpdate");
	AssistedTargetingUpdate *assistModule = (AssistedTargetingUpdate *)requestOf->findModule(key_assistUpdate);
	if (assistModule == 0)
		return 1;

	if (!assistModule->isFreeToAssist())
		return 1;

	assistModule->assistAttack(requestData->m_source, (Object *)requestData->m_other);
	return 1;
}

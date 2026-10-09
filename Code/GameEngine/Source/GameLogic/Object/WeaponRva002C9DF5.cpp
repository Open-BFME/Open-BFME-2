// cl: /DNDEBUG /MD /EHsc
// ?rva002C9DF5@Weapon@@QBEXPBVObject@@PBX@Z
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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tmplate) const;
};

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

int __cdecl makeAssistanceRequest(Object *requestOf, void *userData);

class Object
{
public:
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	const Rva000CBA20Point *getPosition2D() const { return &m_position; }

protected:
	Module *findModule(NameKeyType key) const;

private:
	friend int __cdecl makeAssistanceRequest(Object *requestOf, void *userData);

	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Rva000CBA20Point m_position;		// +0x38
};

class AssistedTargetingUpdate
{
public:
	bool isFreeToAssist() const;
	void assistAttack(const Object *requestingObject, Object *victimObject);
};

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
};

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


class Weapon
{
public:
	void rva002C9DF5(const Object *source, const void *other) const;

private:
	char m_pad00[4];
	const WeaponTemplateRange *m_template; // +4
};

void Weapon::rva002C9DF5(const Object *source, const void *other) const
{
	Player *player = source->getControllingPlayer();
	if (player == 0)
		return;
	IterateData data;
	data.m_source = source;
	data.m_other = other;
	data.m_rangeSqr = 0.0f;
	float range = m_template->m_range;
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

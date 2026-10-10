// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002931F5@Object@@QAEPAV1@_N@Z, retail 0x002931F5, 84 bytes.
// Object helper: if own template dword +0x114 carries 0x2000 return this;
// else if containedBy (+0x274) template carries it return containedBy;
// else if bool arg set look up producerID (+0x78) via TheGameLogic
// findObjectByID (rowed 0x00049DC5) and return producer if its template
// carries it, else null. Evidence: Object offsets template +0x04
// (Object_isAbleToAttack/ObjectScriptStatus), producer +0x78
// (ObjectSetProducer), containedBy +0x274 (Object_isAbleToAttack),
// TheGameLogic at 0x00DFE78C; callers 0x002933CD (chain + testStatus
// 0x5F/0x60) and 0x00293926 (isKindOf gate) prove Object owner.

typedef bool Bool;


#include "../../Common/GameLogicObjectLookupView.h"


enum KindOfType
{
	KINDOF_DUMMY = 0
};

enum ObjectStatusTypes
{
	STATUS_5F = 0x5F,
	STATUS_60 = 0x60
};

struct ThingTemplate
{
	unsigned char m_pad[0x114];
	unsigned int m_flags114;
};

class Object;

extern GameLogic *TheGameLogic;

class SpawnBehaviorInterface { public: virtual void v0(); virtual void onSpawnDeath(ObjectID id, void *arg); };
class Rva002930A9Child { public: virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void slot13(Object *object); };
class Rva002930A9Holder { public: virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual Rva002930A9Child *child(); };
class Rva002CA9CA { public: bool rva002CAD8B(); };
class Weapon { public: char pad[4]; Rva002CA9CA *template4; };
enum WeaponSlotType { SLOT_ZERO=0 };
class WeaponSet { public: Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const; };
class Object
{
public:
	Object *rva002931F5(Bool checkProducer);
	bool rva00293408();
	bool rva0028C4ED() const;
	ObjectID rva0028C513() const;
	Bool rva00293926(KindOfType kind);
	void rva002930A9(void *arg);
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	int rva002933CD();
	void *rva0029439D();
	Bool isKindOf(KindOfType kind) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028C197() const;

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id74;
	ObjectID m_producerID;
	unsigned char m_pad7C[0x250 - 0x7C];
	Rva002930A9Holder *m_holder250;
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy;
	char pad278[0x330-0x278]; WeaponSet m_weapons;
};

Object *Object::rva002931F5(Bool checkProducer)
{
	if ((m_template->m_flags114 & 0x2000) != 0)
		return this;
	Object *contained = m_containedBy;
	if (contained != 0 && (contained->m_template->m_flags114 & 0x2000) != 0)
		return contained;
	if (checkProducer)
	{
		Object *producer = TheGameLogic->findObjectByID(m_producerID);
		if (producer != 0 && (producer->m_template->m_flags114 & 0x2000) != 0)
			return producer;
	}
	return 0;
}

Bool Object::rva00293926(KindOfType kind)
{
	if (isKindOf(kind))
		return true;
	Object *related = rva002931F5(false);
	if (related != 0)
		return related->isKindOf(kind);
	return false;
}

int Object::rva002933CD()
{
	Object *cur = this;
	for (;;)
	{
		Object *next = cur->rva002931F5(false);
		if (next == 0)
			break;
		if (next == cur)
			break;
		cur = next;
	}
	if (cur->testStatus(STATUS_60) || cur->testStatus(STATUS_5F))
		return 1;
	return 0;
}

// ?rva0029439D@Object@@QAEPAXXZ, retail 0x0029439D, 21 bytes.
// Object helper: related via rva002931F5(false); if non-null tail to
// rva0028C197 else null. Evidence: thiscall with no args proven by callers
// 0x002946AB (mov esi ecx then call) and 0x002957FC (mov ecx esi then call);
// callees rowed 0x002931F5 and 0x0028C197; sits after 0x00293926 in this TU.
void *Object::rva0029439D()
{
	Object *related = rva002931F5(false);
	if (related != 0)
		return related->rva0028C197();
	return 0;
}

// Native89 Object predicate: owner relation lookup and six WeaponSet entries330.
// Native templates call the already owned opaque nugget-query2CAD8B; public purpose unresolved.
bool Object::rva00293408()
{
    if (rva0028C4ED()) {
        ObjectID id = rva0028C513();
        if (TheGameLogic->findObjectByID(id)) {
            int slot=0;
            WeaponSet *weapons = &m_weapons;
            do {
                Weapon *weapon = weapons->getWeaponInWeaponSlot((WeaponSlotType)slot);
                if (weapon && weapon->template4 && weapon->template4->rva002CAD8B()) return true;
            } while (++slot<6);
        }
    }
    return false;
}

// ?rva002930A9@Object@@QAEXPAX@Z, retail 0x002930A9, 92 bytes, ret 4.
// Tells the producing object (producerID +0x78 through the rowed findObjectByID) about this
// object: through its spawn behavior interface (slot 1 with this object's id at +0x74 and the
// argument) when it has one, otherwise through the child of the holder at producer +0x250
// (virtual slot 31, then that child's slot 13 with this object) when both exist.
// Evidence: target bytes and the rowed callees; the interface and holder names are neutral.
void Object::rva002930A9(void *arg)
{
	Object *producer = TheGameLogic->findObjectByID(m_producerID);
	if (producer == 0)
		return;
	SpawnBehaviorInterface *spawn = producer->getSpawnBehaviorInterface();
	if (spawn != 0)
	{
		spawn->onSpawnDeath(m_id74, arg);
		return;
	}
	Rva002930A9Holder **holder = &producer->m_holder250;
	if (*holder != 0 && (*holder)->child() != 0)
		(*holder)->child()->slot13(this);
}

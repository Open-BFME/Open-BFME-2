// cl: /DNDEBUG /MD /EHs-c-
// ?createAndFireTempWeapon@WeaponStore@@QAEXPBVWeaponTemplate@@PBVObject@@PBUCoord3D@@@Z @0x002CE904 96B
// Donor: ZH Weapon.h WeaponStore::createAndFireTempWeapon plus BFME1 Weapon.cpp
//   (allocate plus loadAmmoNow plus fireWeapon plus deleteInstance). Target adds
//   ownerID at +8 from Object+0x74 and frame+1 at +0x50 from TheGameLogic+0x40.
//   Callers 0x0033541C (lua template plus object plus +0x38 pos) 0x00495A2B and
//   0x001F0188 prove (template object pos); sibling 0x002CE964 is the target
//   overload firing at an object. Virtual deleteInstance(0) fed to operator
//   delete follows FireWeaponWhenDamagedBehaviorDtor.
struct Coord3D { float x, y, z; };

class Object
{
public:
	char m_pad00[0x38]; // +0x00..0x38
	Coord3D m_position; // +0x38
	char m_pad44[0x30]; // +0x44..0x74
	int m_id; // +0x74
};

class WeaponTemplate
{
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

class Weapon
{
public:
	virtual void *deleteInstance(int flags);
	void loadAmmoNow(const Object *source);
	bool fireWeapon(const Object *source, const Coord3D *pos, int *projectileID);
	bool rva002CE72B(const Object *source, const Coord3D *pos1, const Coord3D *pos2, int x);
	bool rva002CE6C5(const Object *source, int targetID, const Object *target, int *projectileID);
	const WeaponTemplate *m_template; // +4
	unsigned int m_ownerID; // +8
	char m_pad0C[0x50 - 0x0C]; // +0x0C..0x50
	unsigned int m_50; // +0x50
};

class GameLogic
{
public:
	char m_pad00[0x40]; // +0x00..0x40
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;


class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
	void rva002CE8AA(const WeaponTemplate *wt, const Coord3D *pos1, const Object *source, const Coord3D *pos2, int x);
	void rva002CE964(const WeaponTemplate *wt, const Object *source, const Object *victim);
};
extern WeaponStore *TheWeaponStore;


void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos)
{
	if (wt == 0)
		return;
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, WEAPON_SLOT_PRIMARY);
	if (source != 0)
		w->m_ownerID = (unsigned int)source->m_id;
	w->loadAmmoNow(source);
	w->m_50 = TheGameLogic->m_frame + 1;
	w->fireWeapon(source, pos, 0);
	::operator delete(w->deleteInstance(0));
}

// 0x002CE8AA 90B: same allocate plus loadAmmoNow plus deleteInstance family as
// the pos sibling above, but firing via rowed 0x002CE72B with an explicit
// source position plus target position plus int, and with no wt null check
// and no frame+1 store. Caller at 0x0045C833 sets ecx to TheWeaponStore and
// pushes template plus source-pos plus source plus target-pos plus int, which
// proves the WeaponStore thiscall class and the 5-arg order.
void WeaponStore::rva002CE8AA(const WeaponTemplate *wt, const Coord3D *pos1, const Object *source, const Coord3D *pos2, int x)
{
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, WEAPON_SLOT_PRIMARY);
	if (source != 0)
		w->m_ownerID = (unsigned int)source->m_id;
	w->loadAmmoNow(source);
	w->rva002CE72B(source, pos1, pos2, x);
	::operator delete(w != 0 ? w->deleteInstance(0) : 0);
}

// 0x002CE964: victim-target overload of the same family: wt null check, ownerID
// from source+0x74, loadAmmoNow, frame+1 at +0x50, fire via rowed 0x002CE6C5
// with victim ID plus victim, then unconditional virtual deleteInstance(0) fed
// to operator delete. Caller at 0x004C2224 sets ecx to TheWeaponStore and
// pushes template plus source plus victim from findObjectByID, which proves
// the WeaponStore thiscall class and the 3-arg order.
void WeaponStore::rva002CE964(const WeaponTemplate *wt, const Object *source, const Object *victim)
{
	if (wt == 0)
		return;
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, WEAPON_SLOT_PRIMARY);
	if (source != 0)
		w->m_ownerID = (unsigned int)source->m_id;
	w->loadAmmoNow(source);
	w->m_50 = TheGameLogic->m_frame + 1;
	w->rva002CE6C5(source, victim->m_id, victim, 0);
	::operator delete(w->deleteInstance(0));
}

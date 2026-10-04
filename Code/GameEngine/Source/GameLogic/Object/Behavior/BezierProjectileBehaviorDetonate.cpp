// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// BezierProjectileBehavior's detonation 0x0045C026 (called from its update
// 0x0045C226, its +0x20 slot 3 0x0045CD6E and 0x004A7580). Zero Hour's and
// BFME1's DumbProjectileBehavior::detonate with a BFME2 prologue: once only
// (+0x80); first, with module data +0xBC not -1, +0xB8 set and the victim
// (+0x38) still there, every alive object other than the launcher (+0x28)
// that the 0x00260EB1 filter accepts for the launcher with flags 7, within
// the data's +0xC0 of the victim (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents), gets 0x0028EC68 with (+0xBC, the
// launcher, +0xB8). Then the detonation weapon (+0x40) fires through the
// weapon store for the projectile's producer (its +0x78 object, else the
// projectile itself, kept in the global 0x00DFEFD8 meanwhile) - at the
// victim when the weapon's +0x131 flag says so, else at the projectile's
// position with the +0x2C launch position and the +0x74 bonus - and the
// projectile is killed (8, 10) when the data's +0x4A says so, else
// destroyed; without a weapon it is killed. The drawable is hidden and the
// object gets status 4.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

enum DamageType
{
	DAMAGE_RVA0045C026_8 = 8
};

enum DeathType
{
	DEATH_RVA0045C026_10 = 10
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0045C026_4 = 4
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);	// 0x00271601
};

class Object
{
public:
	void bfmeApplySpecialModelCondition(int what, const void *source, int value);	// 0x0028EC68
	void kill(DamageType damageType, DeathType deathType);	// 0x002984D4
	Drawable *getDrawable() const;	// 0x005508E2
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x78 - 0x44];
	ObjectID m_producerID;	// +0x78
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
	void destroyObject(Object *obj);	// 0x00242C09
};
extern GameLogic *TheGameLogic;

extern int g_Va00DFEFD8;

class WeaponTemplate
{
public:
	char m_pad000[0x131];
	bool m_131;	// +0x131 fire at the victim
};

class WeaponStore
{
public:
	void rva002CE8AA(const WeaponTemplate *tmpl, const Coord3D *launchPos, const Object *source,
		const Coord3D *pos, int bonus);	// 0x002CE8AA
	void rva002CE964(const WeaponTemplate *tmpl, const Object *source, const Object *victim);	// 0x002CE964
};
extern WeaponStore *TheWeaponStore;

struct BezierProjectileBehaviorModuleData
{
	char m_pad00[0x4A];
	bool m_detonateCallsKill;	// +0x4A
	char m_pad4B[0xB8 - 0x4B];
	int m_B8;			// +0xB8
	int m_BC;			// +0xBC (-1 for none)
	float m_C0;			// +0xC0 the radius
};

class BezierProjectileBehavior
{
public:
	void rva0045C026();
private:
	void *m_vtable;
	const BezierProjectileBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x28 - 0x0C];
	ObjectID m_launcherID;		// +0x28
	Coord3D m_launchPos;		// +0x2C
	ObjectID m_victimID;		// +0x38
	char m_pad3C[0x40 - 0x3C];
	const WeaponTemplate *m_detonationWeaponTmpl;	// +0x40
	char m_pad44[0x74 - 0x44];
	int m_extraBonusFlags;		// +0x74
	char m_pad78[0x80 - 0x78];
	bool m_hasDetonated;		// +0x80
};

void BezierProjectileBehavior::rva0045C026()
{
	if (m_hasDetonated)
		return;
	GameLogic *logic = TheGameLogic;
	Object *victim = logic->findObjectByID(m_victimID);
	const BezierProjectileBehaviorModuleData *d = m_moduleData;
	if (d && d->m_BC != -1 && d->m_B8 && victim) {
		Object *launcher = logic->findObjectByID(m_launcherID);
		if (launcher) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(victim->getPosition(), d->m_C0, 1,
				Rva00260EB1Filter(launcher, 7, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(launcher))), 1);
			Object *other;
			while ((other = hits.next()) != 0) {
				if (other == launcher)
					continue;
				other->bfmeApplySpecialModelCondition(d->m_BC, launcher, d->m_B8);
			}
		}
	}
	Object *obj = m_object;
	if (m_detonationWeaponTmpl) {
		ObjectID producerID = obj->m_producerID;
		Object *source = obj;
		g_Va00DFEFD8 = producerID;
		Object *producer = TheGameLogic->findObjectByID(producerID);
		if (producer)
			source = producer;
		if (victim && m_detonationWeaponTmpl->m_131)
			TheWeaponStore->rva002CE964(m_detonationWeaponTmpl, source, victim);
		else
			TheWeaponStore->rva002CE8AA(m_detonationWeaponTmpl, &m_launchPos, source, obj->getPosition(),
				m_extraBonusFlags);
		if (m_moduleData->m_detonateCallsKill)
			obj->kill(DAMAGE_RVA0045C026_8, DEATH_RVA0045C026_10);
		else
			TheGameLogic->destroyObject(obj);
		g_Va00DFEFD8 = 0;
	} else {
		obj->kill(DAMAGE_RVA0045C026_8, DEATH_RVA0045C026_10);
	}
	if (obj->getDrawable())
		obj->getDrawable()->setDrawableHidden(true);
	m_hasDetonated = true;
	obj->setStatus(OBJECT_STATUS_RVA0045C026_4, true);
}

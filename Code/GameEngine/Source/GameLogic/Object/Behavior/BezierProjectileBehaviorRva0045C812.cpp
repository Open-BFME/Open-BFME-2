// cl: /DNDEBUG /MD
//
// ?rva0045C812@BezierProjectileBehavior@@QAEXPBVObject@@@Z @0x0045C812 62B
// Bezier fire-temp-weapon plus list push calling rowed WeaponStore::handleProjectileDetonation 0x002CE8AA and pinned push_back 0x002A1B6F
// Evidence: unlock packet 0x0045C812 between PoolKey 0x0045BFD9 and dtor 0x0045C959; Bezier offsets 0x2C 0x40 0x74 0x7C from xfer 0x0045CA8E; Object +0x38 +0x74 from WeaponStoreCreateAndFireTempWeapon; caller 0x0045CDCB
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x30];
	ObjectID m_id;
};

class WeaponTemplate
{
};

class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &id);
};

class WeaponStore
{
public:
	void handleProjectileDetonation(const WeaponTemplate *wt, const Coord3D *pos1, const Object *source, const Coord3D *pos2, int x);
};

extern WeaponStore *TheWeaponStore;

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class Rva0024A797 : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	virtual ~Rva0024A797();
};

class BezierProjectileBehaviorSecondaryBase0
{
public:
	virtual void slot();
};

class BezierProjectileBehaviorSecondaryBase1
{
public:
	virtual void slot();
};

class BezierProjectileBehavior : public Rva0024A797, public BezierProjectileBehaviorSecondaryBase0, public BezierProjectileBehaviorSecondaryBase1
{
public:
	void rva0045C812(const Object *obj);
private:
	unsigned char m_pad28[0x2C - 0x28];
	Coord3D m_coord2C;
	unsigned char m_pad38[0x40 - 0x38];
	const WeaponTemplate *m_weapon40;
	unsigned char m_pad44[0x74 - 0x44];
	int m_int74;
	unsigned char m_pad78[0x7C - 0x78];
	BridgeBehaviorObjectIDList m_list7C;
};

void BezierProjectileBehavior::rva0045C812(const Object *obj)
{
	TheWeaponStore->handleProjectileDetonation(m_weapon40, &m_coord2C, (const Object *)*(void **)((char *)this + 8), &obj->m_position, m_int74);
	ObjectID id = obj->m_id;
	m_list7C.push_back(id);
}

// ?rva0045C975@BezierProjectileBehavior@@QAEXH@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
//
// ?rva0045C975@BezierProjectileBehavior@@QAEXH@Z @0x0045C975 (281B).
// BezierProjectileBehavior impact/detonate: layer resolve plus terrain pass check
// plus position set plus trail clear plus reset plus kill plus AI notify.
// Evidence: neighbours ??_GBezierProjectileBehavior 0x0045C959 and
// ?xfer@BezierProjectileBehavior 0x0045CA8E prove BezierProjectileBehavior TU;
// offsets +0x44 vector erase plus +0x7C reset plus +0x28/+0x70/+0x78 clears plus
// +0x38 target id match Xfer layout; callees rowed setPosition kill setStatus
// rva0028B4CE rva0028AE6D erase reset rva001E4912 rva001E42F2 rva0045003E aiIdle
// plus pinned getLayerForDestination plus TerrainLogic vslot 0x1C plus globals
// TheTerrainLogic and g_Va00BC2428; ret 4 unused int param.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = -1
};

enum DamageType
{
	DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	DEATH_TYPE_0 = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_5 = 5
};

enum CommandSourceType
{
	COMMAND_SOURCE_2 = 2
};

class Object;
class Thing;
class ModuleData;

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *coord);
};

extern TerrainLogic *TheTerrainLogic;
extern float g_Va00BC2428;

class Object
{
public:
	void rva0028B4CE(PathfindLayerEnum layer);
	void rva0028AE6D();
	void kill(DamageType damage, DeathType death);
	void setStatus(ObjectStatusTypes status, bool flag);

public:
	char m_pad0[0x38];
	Coord3D m_pos38;
	char m_pad44[0x118 - 0x44];
	int m_flags118;
	char m_pad11C[0x258 - 0x11C];
	void *m_ptr258;
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

struct Gen_p12pod
{
	int a[3];
};

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	T *erase(T *first, T *last);
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva0029FB3BMember
{
public:
	void reset();

private:
	void *m_head;
};

class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned m_bits[19];
};

class Rva001E42F2
{
public:
	void rva001E42F2(const int *p);
};

class AICommandInterface
{
public:
	void rva0045003E(int v, CommandSourceType src);
	void aiIdle(CommandSourceType src);
};

struct ObjectAI
{
	char m_pad[0x20];
	AICommandInterface m_ai;
};

struct BezierModuleData
{
	char m_pad[0x19];
	unsigned char m_flag19;
	char m_pad1A[0x38 - 0x1A];
	int m_val38;
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
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
	void rva0045C975(int unused);

private:
	int m_id28;
	char m_pad2C[0x44 - 0x2C];
	_STL::vector<Gen_p12pod> m_vec44;
	char m_pad50[0x70 - 0x50];
	int m_int70;
	int m_pad74;
	int m_int78;
	Rva0029FB3BMember m_list7C;
};

// ?rva0045C975@BezierProjectileBehavior@@QAEXH@Z present-unmatched
void BezierProjectileBehavior::rva0045C975(int unused)
{
	Object *obj = *(Object **)((char *)this + 8);
	Coord3D pos;
	pos.x = obj->m_pos38.x;
	pos.y = obj->m_pos38.y;
	pos.z = obj->m_pos38.z + g_Va00BC2428;
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &pos);
	obj->rva0028B4CE(layer);
	float h = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
	pos.z = h;
	((Thing *)obj)->setPosition(&pos);
	_STL::vector<Gen_p12pod> &vec = this->m_vec44;
	vec.erase(vec.begin(), vec.end());
	this->m_int70 = 0;
	this->m_int78 = 0;
	this->m_id28 = 0;
	this->m_list7C.reset();
	Rva001E4912 bits;
	((Rva001E42F2 *)obj)->rva001E42F2((const int *)bits.rva001E4912(0, 0x9a, 0x9b));
	const BezierModuleData *d = (const BezierModuleData *)this->m_moduleData;
	if (d->m_flag19 != 0) {
		if ((obj->m_flags118 & 0x4000000) == 0) {
			obj->m_flags118 |= 0x4000000;
			obj->rva0028AE6D();
		}
		obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
	}
	obj->setStatus(OBJECT_STATUS_5, false);
	int v38 = d->m_val38;
	ObjectAI *aiobj = (ObjectAI *)obj->m_ptr258;
	if ((unsigned int)v38 > 0u) {
		if (aiobj == 0)
			return;
		aiobj->m_ai.rva0045003E(v38, COMMAND_SOURCE_2);
	} else {
		if (aiobj == 0)
			return;
		aiobj->m_ai.aiIdle(COMMAND_SOURCE_2);
	}
}

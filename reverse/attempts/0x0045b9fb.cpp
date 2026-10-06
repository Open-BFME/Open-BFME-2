// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z
// partial score=0.3709 date=2026-10-05
// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z @0x0045B9FB 336B
// Bezier projectile path-step collision: min((end-begin)/12-1, m_70)-1 clamped,
// dir=(point-objPos)*INV, 13 steps calling GeometryInfo::bfmeIntersects,
// then Thing::setPosition to last free. Evidence: same +0x44/+0x48/+0x70
// layout as BezierProjectileBehaviorSlots TU; same +0x38/+0x44/+0xa8 Object
// layout as ObjectRva0028B35B TU; rowed setPosition 0x0030AA80; pin-only
// bfmeIntersects 0x006BEB80; global INV (_INV) at VA 0xbc2424; caller 0x0045CD6E.
#include <stddef.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	bool bfmeIntersects(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
};

extern "C" float INV;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object
{
public:
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
	char m_pad1[0xa8 - 0x48];
	GeometryInfo m_geometryInfo; // +0xa8
};

class ModuleData;

enum ObjectID
{
	INVALID_ID = 0
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void gap1();
	virtual void gap2();
	virtual void gap3();
	virtual void gap4();
	virtual void gap5();
	virtual void gap6();
	virtual void gap7();
	virtual void gap8();
	virtual void gap9();
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void rva0045BB8A(Object *victim, const Coord3D *victimPos) = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva0045BF06Iface
{
public:
	virtual void rva0045B936(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const void *arg6, void *helper, const void *mtx) = 0;
	virtual void gap1() = 0;
	virtual ObjectID getLauncherID() const = 0;
	virtual bool rva0045CD6E(Object *victim) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
	virtual void rva0045B4E2(int unused) = 0;
};

class Rva0045B4C0Iface
{
public:
	virtual void rva0045B4C0(Object *victim, int a2, int a3) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
};

struct BezierPathPoint
{
	float x;
	float y;
	float z;
};

class BezierProjectileBehavior : public UpdateModule, public Rva0045BF06Iface, public Rva0045B4C0Iface
{
public:
	void rva0045B9FB(Object *other);
private:
	ObjectID m_28; // +0x28
	Coord3D m_2C; // +0x2C
	ObjectID m_38; // +0x38
	int m_3C;
	void *m_helper; // +0x40
	BezierPathPoint *m_pathBegin; // +0x44
	BezierPathPoint *m_pathEnd; // +0x48
	void *m_pathCap;
	char m_pad4C[0x70 - 0x50];
	int m_70; // +0x70
	int m_74;
};

// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z present-unmatched
void BezierProjectileBehavior::rva0045B9FB(Object *other)
{
	if (other == 0)
		return;
	int n = (m_pathEnd - m_pathBegin) - 1;
	int idx;
	if ((unsigned int)n >= (unsigned int)m_70)
		idx = m_70;
	else
		idx = (m_pathEnd - m_pathBegin) - 1;
	idx--;
	if (idx < 0)
		idx = 0;
	BezierPathPoint *p = m_pathBegin + idx;
	Object *obj = m_object;
	float objAngle = obj->m_orientation;
	float dx = (p->x - obj->m_position.x) * INV;
	float dy = (p->y - obj->m_position.y) * INV;
	float dz = (p->z - obj->m_position.z) * INV;
	Coord3D cur;
	cur.x = obj->m_position.x;
	cur.y = obj->m_position.y;
	cur.z = obj->m_position.z;
	for (int i = 0; i <= 12; i++)
	{
		cur.x += dx;
		cur.y += dy;
		cur.z += dz;
		if (!obj->m_geometryInfo.bfmeIntersects(cur, objAngle, other->m_geometryInfo, other->m_position, other->m_orientation))
			break;
	}
	cur.x -= dx;
	cur.y -= dy;
	cur.z -= dz;
	((Thing *)obj)->setPosition(&cur);
}

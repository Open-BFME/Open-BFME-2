// cl: /MD /EHsc
// ??1MissileUpdate@@MAE@XZ @0x004A76DE 84B: restores five vtables then clear 0x4A7512 then pinned base 0x45BF6E; caller 0x4A789C deleting dtor; then 0x4A789C
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Thing;
class ModuleData;
enum ObjectStatusTypes { OBJECT_STATUS_NONE=0 };
class Object
{
public:
	unsigned char m_pad[0x38];
	Coord3D m_pos;
	unsigned char m_pad44[0x74-0x44];
	ObjectID m_id;
	void setStatus(ObjectStatusTypes,bool);
};
class Rva004A76DEBase0 { public: virtual ~Rva004A76DEBase0(); const ModuleData *m_moduleData; Object *m_object; };
class Rva004A76DEBase1 { public: virtual ~Rva004A76DEBase1(); };
class Rva004A76DEBase2 { public: virtual ~Rva004A76DEBase2(); unsigned char m_pad[12]; };
// Native +0x20/C53548 and +0x24/C53530 are six-slot projectile
// interfaces, not destructor interfaces. Preserve their existing view names
// while describing every populated slot. Existing providers and exact folded
// companions supply these entries; no original meaning is claimed for the
// four ordinal zero-argument callbacks in the +0x24 table.
struct Rva0045B936Arg;
class Rva002CBA7C;
class Matrix3D;
class Rva004A76DEBase3 {
public:
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *) = 0;
 virtual unsigned char rva004A768A() const = 0;
 virtual int getLauncherID() const = 0;
 virtual bool rva0045CD6E(Object *) = 0;
 virtual bool rva0045BF06(Object *) = 0;
 virtual void rva0045B4E2(int) = 0;
};
class Rva004A76DEBase4 {
public:
 virtual void rva0045B4C0(Object *, int, int) = 0;
 virtual bool rva0045BF06(Object *) = 0;
 virtual bool rva0047A699_2() = 0; virtual bool rva0047A699_3() = 0;
 virtual bool rva0047A699_4() = 0; virtual bool rva0047A699_5() = 0;
};
class BezierProjectileBehavior : public Rva004A76DEBase0, public Rva004A76DEBase1, public Rva004A76DEBase2, public Rva004A76DEBase3, public Rva004A76DEBase4
{
public:
	virtual ~BezierProjectileBehavior();
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *);
 virtual bool rva0045CD6E(Object *);
 virtual void rva0045B4C0(Object *, int, int);
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
protected:
	unsigned char m_pad28[0x88 - 0x28];
};
class MissileUpdate : public BezierProjectileBehavior
{
public:
 virtual void projectileLaunchAtObjectOrPosition(Object *, const Coord3D *, Object *, int, int, const Rva0045B936Arg *, Rva002CBA7C *, const Matrix3D *);
 virtual unsigned char rva004A768A() const;
 virtual int getLauncherID() const;
 virtual bool rva0045CD6E(Object *);
 virtual bool rva0045BF06(Object *);
 virtual void rva0045B4E2(int);
 virtual bool rva0047A699_2(); virtual bool rva0047A699_3();
 virtual bool rva0047A699_4(); virtual bool rva0047A699_5();
protected:
	virtual ~MissileUpdate();
public:
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
	void Rva004A7512Clear();
	void Rva004A7530Set(int val);
private:
	int m_88;
	unsigned int m_frame;
	ObjectID m_90; // +0x90 (launcher)
	ObjectID m_94; // +0x94 (victim)
	unsigned int m_98;
	float m_9C;
	Coord3D m_velA; // +0xA0
	Coord3D m_prevPos; // +0xAC
	Coord3D m_velB; // +0xB8
	unsigned int m_C4;
	int m_C8;
	bool m_CC;
	bool m_CD;
	bool m_CE;
};
MissileUpdate::~MissileUpdate()
{
	Rva004A7512Clear();
}
void MissileUpdate::projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos)
{
	BezierProjectileBehavior::projectileFireAtObjectOrPosition(victim, victimPos);
	Rva004A7530Set(1);
	m_CC = false;
	m_prevPos = m_object->m_pos;
}


void MissileUpdate::projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *pos, Object *launcher, int wslot, int barrel, const Rva0045B936Arg *arg, Rva002CBA7C *helper, const Matrix3D *matrix)
{
 if (victim) m_94 = victim->m_id;
 BezierProjectileBehavior::projectileLaunchAtObjectOrPosition(victim,pos,launcher,wslot,barrel,arg,helper,matrix);
}
unsigned char MissileUpdate::rva004A768A() const { return m_CD; }
int MissileUpdate::getLauncherID() const { return m_90; }
bool MissileUpdate::rva0045CD6E(Object *victim) {
 if (rva004A768A()) {
  BezierProjectileBehavior::rva0045CD6E(victim);
  m_object->setStatus((ObjectStatusTypes)4,true);
 }
 return true;
}
// The same callback occurs in both projectile interfaces. MSVC emits the
// native this-4 adjustor 0x004A7691 for +0x24; the primary implementation
// uses the +0x20 receiver and folds to the complete false/RET4 at 0x005CB9FF.
bool MissileUpdate::rva0045BF06(Object *) { return false; }
// Native +0x20 slot5 is the complete empty one-word callback
// at 0x0047A69C; retain its otherwise unknown argument meaning.
void MissileUpdate::rva0045B4E2(int) { }
// Native +0x24 slots2..5 each point to the whole false/RET0 at 0x0047A699.
// Their original names and semantic roles remain unknown.
bool MissileUpdate::rva0047A699_2() { return false; }
bool MissileUpdate::rva0047A699_3() { return false; }
bool MissileUpdate::rva0047A699_4() { return false; }
bool MissileUpdate::rva0047A699_5() { return false; }

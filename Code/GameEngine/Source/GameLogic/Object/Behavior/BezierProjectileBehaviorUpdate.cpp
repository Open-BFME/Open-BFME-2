// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
// cl: /I. /O1 /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Recovered native update at RVA 0x0045C226; the aim output and following
// delta share one Coord3D buffer. That storage reuse restores the native
// 0x70 frame and all 1516 body bytes with the scalar-copy BezCoord view.
// Donor BFME1 cee35b7d8 supplies related projectile semantics; target bytes
// and WB supply the actual identity and offsets. The original local types
// and spelling of the storage reuse remain unknown.
// WorldBuilder 1181E80 names BezierProjectileBehavior::update; native
// 45C226..45C812. ZH DumbProjectileBehavior::update supplies path retargeting,
// orientation and bridge transitions. BFME1 BezierProjectileBehavior path
// helpers supply the related subsystem semantics; offsets below are BFME2
// ctor/xfer and native access facts, not carried BFME1 layout.
#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include <vector>
#include <bitset>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
struct BezCoord : Coord3D {
 BezCoord() {}
 BezCoord(const Coord3D &sourcePosition) { x=sourcePosition.x; y=sourcePosition.y; z=sourcePosition.z; }
 BezCoord &operator=(const Coord3D &p) { Coord3D::operator=(p); return *this; }
 ~BezCoord() {}
};
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float);
};
class Vector3 { public:
 float X,Y,Z;
 Vector3(float x,float y,float z) { X=x; Y=y; Z=z; }
 __forceinline float Length2() const { return X*X+Y*Y+Z*Z; }
 __forceinline void Normalize() { float len2=Length2(); if(len2!=0.0f) { float oolen=WWMath::Inv_Sqrt(len2); X*=oolen; Y*=oolen; Z*=oolen; } }
};
class Matrix3D { public: void buildTransformMatrix(const Vector3&,const Vector3&); float m[3][4]; };
// This partial geometry view reads +0x10 inline in the retail update. Keep
// its helper distinct from the generic accessor emitted by +0x18 views.
class GeometryInfo { public: float getMaxHeightAbovePosition() const; float projectileCollisionRadius() const { return radius; } char pad[0x10]; float radius; };
class Thing { public: void setPosition(const Coord3D*); void setTransformMatrix(const Matrix3D*); };
struct BezierModelFlags { unsigned words[19];
 __forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}
 __forceinline void set(int i){words[i>>5]|=1u<<(i&31);}
};
enum PathfindLayerEnum { LAYER_GROUND=1 };
class Object : public Thing {
public:
 void rva0028AE6D(); void rva0028EC68(int,void*,int);
 int rva0028B511() const; void setLayer(PathfindLayerEnum);
 char p00[0x38]; Coord3D pos; char p44[0xA8-0x44]; GeometryInfo geometry;
 char pBC[0x10C-0xBC]; BezierModelFlags flags;
 char p158[0x198-0x158]; Coord3D nextPos; char p1A4[2]; bool nextValid;
 __forceinline void setNextPosition(const Coord3D *p) { nextValid=true; nextPos=*p; }
 __forceinline void setCondition(int bit) { if (!flags.test(bit)) { flags.set(bit); rva0028AE6D(); } }
};
struct TargetCoord;
class WeaponTemplate { public: TargetCoord adjustTargetPositionOnVictim(Object *, Object *, bool); };
// The rowed value return uses the same first stack argument as the native output pointer.
typedef Coord3D *(WeaponTemplate::*AimPositionCall)(Coord3D *, const Object *, const Object *, int);
class TerrainLogic {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();
 virtual float getGroundHeight(float,float,Coord3D*);
 virtual float getLayerHeight(float,float,int,Coord3D*,bool);
 PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);
};
extern TerrainLogic *TheTerrainLogic;
class BezierDebugDisplay { public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();
 virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();
 virtual void drawCircle(const Coord3D*,float,unsigned);
};
class View;
// Native DIR32 at VA 0x00DFEA3C is the canonical View singleton.
extern View *TheTacticalView;
struct BezierGlobalData { char pad[0xE9C]; bool debug; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next; // +0x04
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj; // +0x08
};
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
	: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj; // +0x08
	int m_flags; // +0x0C
	bool m_match; // +0x10
	char m_pad11[0x3];
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
struct BezierProjectileBehaviorModuleData {
 char p00[0x3C]; int nearEndFrames; char p40[8];bool tumble;bool orient;
 char p4A[0x8C-0x4A];float adjustDistance;char p90[0xAC-0x90];int effect;
 float effectRadius;bool includeAllies;
};
class BehaviorBase { public:virtual ~BehaviorBase(); const BezierProjectileBehaviorModuleData *data;Object*object; };
struct BehaviorInterface { virtual void s0(); };
struct UpdateModuleInterface { virtual UpdateSleepTime update()=0; };
struct BezierProjectileInterface { virtual void s0();virtual void s1();virtual void s2();virtual void hit(Object*)=0; };
struct BezierSecondInterface { virtual void s0(); };
class BezierUpdateBase:public BehaviorBase,public BehaviorInterface,public UpdateModuleInterface { char storage[12]; };
class BezierProjectileBehavior:public BezierUpdateBase,public BezierProjectileInterface,public BezierSecondInterface {
public:
 virtual UpdateSleepTime update();
 int bfmeCost() const; // sleep time: awake while the path has points
private: bool calcFlightPath(bool);
public: void rva0045C026();
 ObjectID launcher;Coord3D launchPos;ObjectID victim;WeaponTemplate*weapon;int v40;
 _STL::vector<Coord3D> path;char p50[12];Coord3D end;float collisionRadius;int p6c;int step;
 int bonus;int packets;void*list;bool detonated;char p81[3];float scale;
};
UpdateSleepTime BezierProjectileBehavior::update()
{
	const BezierProjectileBehaviorModuleData *bezierProjectileBehaviorModuleData = data;
	Object *obj = object;
	if (bezierProjectileBehaviorModuleData == 0 || obj == 0)
		return UPDATE_SLEEP_FOREVER;

	int count = path.size();
	if (step >= count)
	{
		hit(0);
		return (UpdateSleepTime)bfmeCost();
	}

	if (bezierProjectileBehaviorModuleData->nearEndFrames && step == count - bezierProjectileBehaviorModuleData->nearEndFrames)
	{
		obj->setCondition(155);
		if (bezierProjectileBehaviorModuleData->effect != -1)
		{
			int relation = 2;
			if (bezierProjectileBehaviorModuleData->includeAllies)
				relation = 6;
			relation |= 1;
			if (((BezierGlobalData *)TheWritableGlobalData)->debug)
			{
				BezCoord pos(end);
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
				((BezierDebugDisplay *)TheTacticalView)->drawCircle(&pos, bezierProjectileBehaviorModuleData->effectRadius, 0xffff00ff);
			}
			BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(&end, bezierProjectileBehaviorModuleData->effectRadius, 1,
				Rva00260EB1Filter(obj, relation, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 1);
			Object *other;
			while ((other = iter.next()) != 0)
			{
				if (other != obj)
					other->rva0028EC68(bezierProjectileBehaviorModuleData->effect, obj, 1);
			}
		}
	}

	if (victim != 0 && bezierProjectileBehaviorModuleData->adjustDistance > 0.0f)
	{
		Object *target = TheGameLogic->findObjectByID(victim);
		if (target)
		{
			BezCoord newPos;
			Coord3D delta;
			newPos = *(weapon->*reinterpret_cast<AimPositionCall>(&WeaponTemplate::adjustTargetPositionOnVictim))(&delta, obj, target, 1);
			delta.x = newPos.x - end.x;
			delta.y = newPos.y - end.y;
			delta.z = newPos.z - end.z;
			float distSqr = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
			if (distSqr > 0.1f)
			{
				float dist = (float)sqrt(distSqr);
				if (dist > bezierProjectileBehaviorModuleData->adjustDistance)
					dist = bezierProjectileBehaviorModuleData->adjustDistance;
				delta.normalize();
				end.x += dist * delta.x;
				end.y += dist * delta.y;
				end.z += dist * delta.z;
				if (!calcFlightPath(false))
				{
					rva0045C026();
					return (UpdateSleepTime)bfmeCost();
				}
			}
		}
	}

	const Coord3D *flightPos = &path[step];
	if (bezierProjectileBehaviorModuleData->orient && !bezierProjectileBehaviorModuleData->tumble)
	{
		float length = scale * 20.0f;
		Coord3D prevPos;
		if (step > 0)
			prevPos = path[step - 1];
		else
		{
			prevPos = path[step];
			prevPos.z -= length;
		}
		Coord3D nextPos;
		if (step < count - 1)
			nextPos = path[step + 1];
		else
		{
			nextPos = path[step];
			nextPos.z -= length;
		}
		Vector3 dir(nextPos.x - prevPos.x, nextPos.y - prevPos.y, nextPos.z - prevPos.z);
		dir.Normalize();
		Matrix3D mtx;
		mtx.buildTransformMatrix(Vector3(flightPos->x, flightPos->y, flightPos->z), dir);
		obj->setTransformMatrix(&mtx);
	}
	else
		obj->setPosition(flightPos);

	if (step < count - 1)
		obj->setNextPosition(&path[step + 1]);
	else
	{
		BezCoord cur(obj->pos);
		BezCoord next(*flightPos);
		next.x *= 2.0f;
		next.y *= 2.0f;
		next.z *= 2.0f;
		next.x -= cur.x;
		next.y -= cur.y;
		next.z -= cur.z;
		obj->setNextPosition(&next);
	}

	if (victim != 0)
	{
		Object *target = TheGameLogic->findObjectByID(victim);
		if (target)
		{
			BezCoord targetPos(target->pos);
			targetPos.z += target->geometry.getMaxHeightAbovePosition() * 0.5f;
			float radius = target->geometry.projectileCollisionRadius();
			if (targetPos.length() < radius + collisionRadius)
				hit(target);
		}
	}

	int oldLayer = obj->rva0028B511();
	int newLayer = TheTerrainLogic->getHighestLayerForDestination(&obj->pos, false);
	obj->setLayer((PathfindLayerEnum)newLayer);
	if (oldLayer != LAYER_GROUND && newLayer == LAYER_GROUND)
	{
		BezCoord pos(obj->pos);
		pos.z = 9999.0f;
		int testLayer = TheTerrainLogic->getHighestLayerForDestination(&pos, false);
		if (testLayer == oldLayer)
		{
			float offset = 2.0f;
			pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, testLayer, 0, true) + offset;
			obj->setPosition(&pos);
			rva0045C026();
			return (UpdateSleepTime)bfmeCost();
		}
	}

	++step;
	return (UpdateSleepTime)bfmeCost();
}

// cl: /O1 /G7 /arch:SSE /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /MD /EHsc
// Split from BezierProjectileBehaviorXfer.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// ?xfer@BezierProjectileBehavior@@MAEXPAVXfer@@@Z @0x0045CA8E 483B
// BezierProjectileBehavior::xfer snapshot slot 3 of vtable 0x00841E04 calling rowed UpdateModule::xfer 0x0044DF9F
// Evidence: named pin; vtable slot 3; donor BFME1 BezierProjectileBehavior_xfer.cpp; member offsets from retail loads; callers MissileUpdate::xfer 0x004A798C
#include "ascii_string.h"
#include <vector>
#include "Lib/Coord3D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char version, unsigned char current)
		: m_version(version), m_current(current) {}

	unsigned char m_version;
	unsigned char m_current;
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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
 friend class BezierProjectileBehavior;
 void setWakeFrame(Object *,unsigned);
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

struct BezierPathRecord {float x,y,z;};
struct AICommandCoordVector
{
	void *m_start;
	void *m_finish;
	void *m_end;
 int size() const {return (BezierPathRecord *)m_finish-(BezierPathRecord *)m_start;}
};

Xfer *Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec);

class BridgeBehaviorObjectIDList
{
private:
	void *m_head; // +0x00
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class WeaponTemplate
{
public:
	char m_pad[8];
	AsciiString m_name;
	const AsciiString &getName() const { return m_name; }
};

struct Coord3D;
class WeaponStore
{
public:
	void handleProjectileDetonation(const WeaponTemplate *tmpl, const Coord3D *launchPos, const Object *source, const Coord3D *pos, int bonus); // 0x002CE8AA
	void rva002CE964(const WeaponTemplate *tmpl, const Object *source, const Object *victim); // 0x002CE964
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	void createAndFireTempWeapon(const WeaponTemplate *tmpl, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

extern "C" void *__cdecl bfmeFormatText(void *dst, int v, const char *fmt, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const struct _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

struct BezierError
{
	char *text;
	int tag;
};

class BezierProjectileBehavior : public Rva0024A797, public BezierProjectileBehaviorSecondaryBase0, public BezierProjectileBehaviorSecondaryBase1
{
public:
 void rva0045CC72(int);
 void rva0045C975(int);
protected:
	virtual void xfer(Xfer *xfer);
	virtual void v00();
	virtual void v01();
	virtual void v02();

private:
	ObjectID m_id28;
	Coord3DBase m_coord2C;
	ObjectID m_id38;
	const WeaponTemplate *m_weapon3C;
	const WeaponTemplate *m_weapon40;
	AICommandCoordVector m_vec44;
	Coord3DBase m_coord50;
	Coord3DBase m_coord5C;
	float m_float68;
	int m_int6C;
	int m_int70;
	unsigned int m_uint74;
	int m_int78;
	BridgeBehaviorObjectIDList m_list7C;
	bool m_bool80;
	char m_pad81[3];
	float m_float84;
};


// Reference: BFME1 9e3be919b10a BezierProjectileBehavior_rva001F1B90.cpp.
// Native45CC72..45CD6E is the complete252B RET4 primary update; the old
// no-boundary log was contradicted by its actual push-ebp entry. Target
// data19 / scale20, Object position38, path44/48 stride12, counter78,
// terrain vslot18 and primary vslot34 reconcile the donor's layout and ABI.
// The original method spelling remains unknown; retain its existing pin.
struct BezierPathDataView {char unknown[0x19];unsigned char flag;char gap[6];float scale;};
struct BezierPositionView {char unknown[0x38];Coord3D position;};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class BezierTerrainView {public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();virtual void slot10();virtual void slot14();
 virtual float height(float,float,Coord3D *);
};
class BezierFlightView {public:
#define S(N) virtual void slot##N();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12)
#undef S
 virtual void fire(Object *,const Coord3D *);
};
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float);
};
void BezierProjectileBehavior::rva0045CC72(int flag) {
 Object *object=m_object;
 const BezierPathDataView *data=(const BezierPathDataView *)m_moduleData;
 if(!data->flag && !(unsigned char)flag)((UpdateModule *)this)->setWakeFrame(object,1);
 ++m_int78;
 int count=m_vec44.size();
 if(count<2){rva0045C975(flag);return;}
 BezierPathRecord *path=(BezierPathRecord *)m_vec44.m_start;
 Coord3D delta;
 delta.x=path[count-1].x-path[count-2].x;
 delta.y=path[count-1].y-path[count-2].y;
 delta.z=0;
 float lengthSquared=delta.x*delta.x+delta.y*delta.y;
 if(lengthSquared!=0.0f) {
  float inverseLength=WWMath::Inv_Sqrt(lengthSquared);
  delta.x*=inverseLength;
  delta.y*=inverseLength;
 }
 Coord3D position;
 position.x=((BezierPositionView *)object)->position.x+delta.x*data->scale;
 position.y=((BezierPositionView *)object)->position.y+delta.y*data->scale;
 position.z=((BezierTerrainView *)TheTerrainLogic)->height(position.x,position.y,0);
 ((BezierFlightView *)this)->fire(0,&position);
}

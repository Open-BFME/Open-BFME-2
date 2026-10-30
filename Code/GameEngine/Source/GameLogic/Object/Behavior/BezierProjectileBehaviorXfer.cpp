// cl: /O1 /G7 /arch:SSE /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /MD /EHsc
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


// Retail ThrowInfo identifies the 8-byte XferException class and its
// established constructor, copy constructor and destructor providers.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

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

void BezierProjectileBehavior::xfer(Xfer *xfer)
{
	((UpdateModule *)this)->xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	XferObjectID(xfer, &m_id28);
	XferObjectID(xfer, &m_id38);
	*xfer == m_int6C;
	*xfer == m_float68;
	*xfer == m_coord50;
	*xfer == m_coord5C;
	*xfer == m_bool80;
	xferSTLObjectIDList(xfer, &m_list7C);
	*xfer == m_coord2C;
	Rva00390911XferCoordVector(xfer, &m_vec44);
	if (version.m_current >= 2)
		*xfer == m_float84;
	AsciiString name(AsciiString::TheEmptyString);
	if (m_weapon40)
		((StringBase<char> *)&name)->set(*(const StringBase<char> *)&m_weapon40->getName());
	*xfer == name;
	if (xfer->IsLoading()) {
		if (name.compare(AsciiString::TheEmptyString) == 0)
			m_weapon40 = 0;
		else {
			m_weapon40 = TheWeaponStore->findWeaponTemplate(name);
			if (!m_weapon40) {
				throw XferException(5, 0);
			}
		}
	}
	((StringBase<char> *)&name)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
	if (m_weapon3C)
		((StringBase<char> *)&name)->set(*(const StringBase<char> *)&m_weapon3C->getName());
	*xfer == name;
	if (xfer->IsLoading()) {
		if (name.compare(AsciiString::TheEmptyString) == 0)
			m_weapon3C = 0;
		else {
			m_weapon3C = TheWeaponStore->findWeaponTemplate(name);
			if (!m_weapon3C) {
				throw XferException(5, 0);
			}
		}
	}
	*xfer == m_int78;
	*xfer == m_int70;
	*xfer == m_uint74;
}

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

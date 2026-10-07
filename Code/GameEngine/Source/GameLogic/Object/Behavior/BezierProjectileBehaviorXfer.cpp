// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?xfer@BezierProjectileBehavior@@MAEXPAVXfer@@@Z @0x0045CA8E 483B
// BezierProjectileBehavior::xfer snapshot slot 3 of vtable 0x00841E04 calling rowed UpdateModule::xfer 0x0044DF9F
// Evidence: named pin; vtable slot 3; donor BFME1 BezierProjectileBehavior_xfer.cpp; member offsets from retail loads; callers MissileUpdate::xfer 0x004A798C
#include "ascii_string.h"
#include <vector>

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

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

struct AICommandCoordVector
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

Xfer *Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec);

class BridgeBehaviorObjectIDList
{
	void *m_head;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class WeaponTemplate
{
public:
	char m_pad[8];
	AsciiString m_name;
	const AsciiString &getName() const { return m_name; }
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
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
				BezierError error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (const struct _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
				__assume(0);
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
				BezierError error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (const struct _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
				__assume(0);
			}
		}
	}
	*xfer == m_int78;
	*xfer == m_int70;
	*xfer == m_uint74;
}

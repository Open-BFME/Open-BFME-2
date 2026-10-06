// cl: /MD
// stlport
// ?xfer@ProjectileStreamUpdate@@MAEXPAVXfer@@@Z @0x0033EF8E 137B: slot 3 xfer via base UpdateModule plus Version(1 2) plus 20 ObjectIDs plus 2 ints plus owning plus version-gated target plus Coord3D. Evidence: vtable 0x00810DA8 slot 3; ctor 0x0033EE25 layout +0x20 IDs +0x70 +0x74 +0x78 +0x7C +0x80; callees rowed base 0x0044DF9F plus XferObjectID 0x003060B2.
#include <hash_map>

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
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Thing;
class ModuleData;
class Object;

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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};

enum ObjectID
{
	OBJECTID_INVALID = 0
};
typedef int Int;

enum
{
	INVALID_ID = 0,
	MAX_PROJECTILE_STREAM = 20
};

struct Coord3DBase
{
	float m_x;
	float m_y;
	float m_z;
};

void __cdecl XferObjectID(Xfer *xfer, ObjectID *value);

class ProjectileStreamUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_projectileIDs[MAX_PROJECTILE_STREAM]; // +0x20
	Int m_nextFreeIndex; // +0x70
	Int m_firstValidIndex; // +0x74
	ObjectID m_owningObject; // +0x78
	ObjectID m_targetObject; // +0x7C
	Coord3DBase m_targetPosition; // +0x80
};

void ProjectileStreamUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	Xfer::Version version(1, 2);
	*xfer == version;
	ObjectID *id = m_projectileIDs;
	for (int n = MAX_PROJECTILE_STREAM; n > 0; --n, ++id)
		XferObjectID(xfer, id);
	*xfer == m_nextFreeIndex;
	*xfer == m_firstValidIndex;
	XferObjectID(xfer, &m_owningObject);
	if (version.m_minimum >= 2)
	{
		XferObjectID(xfer, &m_targetObject);
		*xfer == m_targetPosition;
	}
}

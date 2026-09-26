// cl: /O1 /DNDEBUG /MD
//
// ?xfer@BloodthirstyUpdate@@MAEXPAVXfer@@@Z, retail 0x0044E006, 78 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083F0B4 (class of rowed dtor
// ??1BloodthirstyUpdate@@MAE@XZ in BloodthirstyUpdateDtor.cpp, same primary
// as rowed ctor 0x0044E0AA and poolkey 0x0044E054). Base UpdateModule xfer
// via rowed 0x0044DF9F, Version(1,1) via Xfer slot 0x28 before the base,
// then ObjectID at +0x24 and ObjectID at +0x28 via rowed XferObjectID
// 0x003060B2 plus uint at +0x2C via Xfer slot 0x78. Layout is the rowed
// 0x30-byte class (UpdateModule base 0x20 plus trailing vptr at +0x20 giving
// +0x24 start plus two IDs plus frame); member names follow the BFME1
// BloodthirstyUpdate donor (m_bestTargetID at +0x24, m_nextScanFrames at
// +0x2C) with a neutral m_28 for the second ID where the donor uint name
// does not fit the retail ObjectID transfer. Recipe is the
// EvaAnnounceClientCreateXfer Version-first slot-3 pattern.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class BloodthirstyTrailing { public: virtual void trailingSlot(); };

class BloodthirstyUpdate : public UpdateModule, public BloodthirstyTrailing
{
public:
	BloodthirstyUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_bestTargetID;
	ObjectID m_28;
	unsigned int m_nextScanFrames;
};

void BloodthirstyUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_bestTargetID);
	XferObjectID(xfer, &m_28);
	*xfer == m_nextScanFrames;
}
